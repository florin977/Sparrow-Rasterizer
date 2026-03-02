#pragma once

#include <sparrow_rasterizer/utils/vertex_type.hpp>

namespace sparrow_rasterizer {
class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;

  Mesh();
  Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
};
} // namespace sparrow_rasterizer
