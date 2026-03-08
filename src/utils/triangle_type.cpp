#include "sparrow_rasterizer/utils/triangle_type.hpp"
#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include "sparrow_rasterizer/utils/pixel_type.hpp"
#include "sparrow_rasterizer/utils/vertex_type.hpp"
#include <algorithm>
#include <glm/fwd.hpp>

namespace sparrow_rasterizer {
Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : a(a), b(b), c(c) {};

float Triangle::edge_function(const glm::ivec2 &a, const glm::ivec2 &v0,
                              const glm::ivec2 &v1) {
  return (a.x - v0.x) * (v1.y - v0.y) - (a.y - v0.y) * (v1.x - v0.x);
}

float Triangle::edge_function(const Pixel &p, const glm::ivec2 &v0,
                              const glm::ivec2 &v1) {
  return (p.x - v0.x) * (v1.y - v0.y) - (p.y - v0.y) * (v1.x - v0.x);
}

bool Triangle::contains_pixel(const glm::vec3 &weights) {
  return weights.x >= 0 && weights.y >= 0 && weights.z >= 0;
}

float Triangle::get_area(const glm::ivec2 &a, const glm::ivec2 &b,
                         const glm::ivec2 &c) {
  return edge_function(a, b, c);
}

glm::vec3 Triangle::get_weights(const Pixel &p, const glm::ivec2 &a,
                                const glm::ivec2 &b, const glm::ivec2 &c,
                                float area) {
  if (area <= 0) {
    return glm::vec3(0.0f, 0.0f, 0.0f);
  }
  area = 1.0f / area;

  float weight_a = edge_function(p, b, c) * area;
  float weight_b = edge_function(p, c, a) * area;
  float weight_c = 1.0f - (weight_a + weight_b);

  return glm::vec3(weight_a, weight_b, weight_c);
}

void Triangle::draw(Buffer &pixel_buffer, int width, int height) {
  glm::ivec2 a_coords = a.ndc_to_screen(width, height);
  glm::ivec2 b_coords = b.ndc_to_screen(width, height);
  glm::ivec2 c_coords = c.ndc_to_screen(width, height);

  float area = this->get_area(a_coords, b_coords, c_coords);

  // Degenerate triangle - discard it
  if (area <= 0) {
    return;
  }

  int min_x = std::min({a_coords.x, b_coords.x, c_coords.x});
  int max_x = std::max({a_coords.x, b_coords.x, c_coords.x});
  int min_y = std::min({a_coords.y, b_coords.y, c_coords.y});
  int max_y = std::max({a_coords.y, b_coords.y, c_coords.y});
  min_x = std::max(min_x, 0);
  max_x = std::min(max_x, width);
  min_y = std::max(min_y, 0);
  max_y = std::min(max_y, height);

  for (int x = min_x; x < max_x; x++) {
    for (int y = min_y; y < max_y; y++) {
      glm::vec3 weights =
          this->get_weights(Pixel(x, y), a_coords, b_coords, c_coords, area);
      if (!this->contains_pixel(weights)) {
        continue;
      }
      pixel_buffer.set_pixel(x, y, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }
  }
}
} // namespace sparrow_rasterizer
