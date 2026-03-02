#include "sparrow_rasterizer/utils/mesh_type.hpp"

namespace sparrow_rasterizer {
Mesh::Mesh() {}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
    : vertices(vertices), indices(indices) {}
} // namespace sparrow_rasterizer
