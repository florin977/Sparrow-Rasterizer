#pragma once

#include <glm/glm.hpp>

namespace sparrow_rasterizer {
class Vertex {
public:
  glm::vec4 position;
  glm::vec4 normal;
  glm::vec2 uv;

  Vertex();
  Vertex(glm::vec4 position, glm::vec4 normal, glm::vec2 uv);
  bool inside_clip_space() const;
  glm::uvec2 ndc_to_screen(int width, int height) const;
};
} // namespace sparrow_rasterizer
