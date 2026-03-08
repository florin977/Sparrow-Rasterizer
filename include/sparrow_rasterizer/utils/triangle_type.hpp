#pragma once

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
  float edge_function(const glm::ivec2 &p, const glm::ivec2 &v0,
                      const glm::ivec2 &v1);

  float edge_function(const Pixel &p, const glm::ivec2 &v0,
                      const glm::ivec2 &v1);

  bool contains_pixel(const glm::vec3 &weights);
  // Actually 2 * Area, since the actual area is not needed for rasterization
  float get_area(const glm::ivec2 &a, const glm::ivec2 &b, const glm::ivec2 &c);

  glm::vec3 get_weights(const Pixel &p, const glm::ivec2 &a,
                        const glm::ivec2 &b, const glm::ivec2 &c, float area);

  void draw(Buffer &pixel, int width, int height);
};
} // namespace sparrow_rasterizer
