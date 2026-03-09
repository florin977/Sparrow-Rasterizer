#include "sparrow_rasterizer/utils/vertex_type.hpp"
#include <glm/fwd.hpp>
namespace sparrow_rasterizer {
Vertex::Vertex() {}
Vertex::Vertex(glm::vec4 position, glm::vec4 normal, glm::vec2 uv)
    : position(position), normal(normal), uv(uv) {}

bool Vertex::inside_clip_space() const {
  return (-position.w <= position.x && position.x <= position.w) &&
         (-position.w <= position.y && position.y <= position.w) &&
         (-position.w <= position.y && position.y <= position.w);
}

glm::vec3 Vertex::ndc_to_screen(int width, int height) const {
  return glm::vec3(((this->position.x + 1.0f) / 2.0f) * width,
                   ((this->position.y + 1.0f) / 2.0f) * height,
                   (this->position.z + 1.0f) / 2.0f);
};
} // namespace sparrow_rasterizer
