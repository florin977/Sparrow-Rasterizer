#pragma once

#include "sparrow_rasterizer/utils/depth_buffer.hpp"
#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include "sparrow_rasterizer/utils/pixel_type.hpp"
#include <glm/fwd.hpp>
#include <sparrow_rasterizer/utils/vertex_type.hpp>

namespace sparrow_rasterizer {
class Triangle {
public:
  const Vertex &a, &b, &c;
  Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

  // Cross product -> 2 * Area
  float edge_function(const glm::vec3 &p, const glm::vec3 &v0,
                      const glm::vec3 &v1);

  float edge_function(const glm::vec2 &p, const glm::vec3 &v0,
                      const glm::vec3 &v1);

  bool contains_pixel(const glm::vec3 &weights);
  // Actually 2 * Area, since the actual area is not needed for rasterization
  float get_area(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

  glm::vec3 get_weights(const glm::vec2 &p, const glm::vec3 &a,
                        const glm::vec3 &b, const glm::vec3 &c, float area);

  void draw(Buffer &pixel, DepthBuffer &depth_buffer, int width, int height,
            int triangle_id);
};
} // namespace sparrow_rasterizer
