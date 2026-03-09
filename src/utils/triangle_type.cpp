#include "sparrow_rasterizer/utils/triangle_type.hpp"
#include "sparrow_rasterizer/pipeline/fragment_stage.hpp"
#include "sparrow_rasterizer/utils/depth_buffer.hpp"
#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include "sparrow_rasterizer/utils/vertex_type.hpp"
#include <algorithm>
#include <glm/fwd.hpp>

namespace sparrow_rasterizer {
Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : a(a), b(b), c(c) {};

float Triangle::edge_function(const glm::vec3 &a, const glm::vec3 &v0,
                              const glm::vec3 &v1) {
  return (a.x - v0.x) * (v1.y - v0.y) - (a.y - v0.y) * (v1.x - v0.x);
}

float Triangle::edge_function(const glm::vec2 &p, const glm::vec3 &v0,
                              const glm::vec3 &v1) {
  return (p.x - v0.x) * (v1.y - v0.y) - (p.y - v0.y) * (v1.x - v0.x);
}

bool Triangle::contains_pixel(const glm::vec3 &weights) {
  return weights.x >= 0.0f && weights.y >= 0.0f && weights.z >= 0.0f;
}

float Triangle::get_area(const glm::vec3 &a, const glm::vec3 &b,
                         const glm::vec3 &c) {
  return edge_function(a, b, c);
}

glm::vec3 Triangle::get_weights(const glm::vec2 &p, const glm::vec3 &a,
                                const glm::vec3 &b, const glm::vec3 &c,
                                float area) {
  if (area >= 0) {
    return glm::vec3(-1.0f, -1.0f, -1.0f);
  }
  area = 1.0f / area;

  float weight_a = edge_function(p, b, c) * area;
  float weight_b = edge_function(p, c, a) * area;
  float weight_c = 1.0f - (weight_a + weight_b);

  return glm::vec3(weight_a, weight_b, weight_c);
}

void Triangle::draw(Buffer &pixel_buffer, DepthBuffer &depth_buffer, int width,
                    int height, int triangle_id) {
  glm::vec3 a_coords = a.ndc_to_screen(width, height);
  glm::vec3 b_coords = b.ndc_to_screen(width, height);
  glm::vec3 c_coords = c.ndc_to_screen(width, height);

  float area = this->get_area(a_coords, b_coords, c_coords);

  // Degenerate triangle - discard it
  if (area >= 0) {
    return;
  }

  int min_x = std::min({a_coords.x, b_coords.x, c_coords.x});
  int max_x = std::max({a_coords.x, b_coords.x, c_coords.x});
  int min_y = std::min({a_coords.y, b_coords.y, c_coords.y});
  int max_y = std::max({a_coords.y, b_coords.y, c_coords.y});
  min_x = std::max(min_x, 0);
  max_x = std::min(max_x, width - 1);
  min_y = std::max(min_y, 0);
  max_y = std::min(max_y, height - 1);

  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {
      glm::vec3 weights = this->get_weights(glm::vec2(x + 0.5f, y + 0.5f),
                                            a_coords, b_coords, c_coords, area);
      if (!this->contains_pixel(weights)) {
        continue;
      }

      float current_screen_depth = depth_buffer.get_depth(x, y);
      float pixel_new_depth = weights.x * a_coords.z + weights.y * b_coords.z +
                              weights.z * c_coords.z;

      if ((pixel_new_depth < current_screen_depth)) {
        depth_buffer.set_depth(x, y, pixel_new_depth);
        pixel_buffer.set_pixel(x, y,
                               FragmentStage::render(triangle_id, weights));
      }
    }
  }
}
} // namespace sparrow_rasterizer
