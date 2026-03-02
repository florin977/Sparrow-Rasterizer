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
};
} // namespace sparrow_rasterizer
