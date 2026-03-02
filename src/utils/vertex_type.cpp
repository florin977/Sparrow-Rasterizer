#include "sparrow_rasterizer/utils/vertex_type.hpp"
namespace sparrow_rasterizer {
Vertex::Vertex() {}
Vertex::Vertex(glm::vec4 position, glm::vec4 normal, glm::vec2 uv)
    : position(position), normal(normal), uv(uv) {}
} // namespace sparrow_rasterizer
