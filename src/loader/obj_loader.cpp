#include "sparrow_rasterizer/utils/vertex_type.hpp"
#include <cstdint>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "sparrow_rasterizer/loader/obj_loader.hpp"
#include "sparrow_rasterizer/utils/mesh_type.hpp"
#include <iostream>
#include <string>

namespace sparrow_rasterizer {
std::vector<Mesh> ObjLoader::load(const std::string &filename) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn, err;

  auto res = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                              filename.c_str());

  if (!warn.empty()) {
    std::cout << "WARN: " << filename << ' ' << warn << '\n';
  }

  if (!err.empty()) {
    std::cout << "ERROR: " << err << '\n';
    return std::vector<Mesh>();
  }

  if (!res) {
    std::cout << "Failed to parse: " << filename << '\n';
    return std::vector<Mesh>();
  }

  std::vector<Mesh> loaded_meshes;

  for (auto shape : shapes) {
    Mesh loaded_mesh;
    uint32_t index_offset = 0;
    for (auto face : shape.mesh.num_face_vertices) {
      for (int vertex = 0; vertex < 3; vertex++) {
        tinyobj::index_t index = shape.mesh.indices[index_offset + vertex];
        // Position
        tinyobj::real_t vx = attrib.vertices[3 * index.vertex_index + 0];
        tinyobj::real_t vy = attrib.vertices[3 * index.vertex_index + 1];
        tinyobj::real_t vz = attrib.vertices[3 * index.vertex_index + 2];

        tinyobj::real_t nx = 0.0f;
        tinyobj::real_t ny = 1.0f;
        tinyobj::real_t nz = 0.0f;

        tinyobj::real_t v = 0.0f;
        tinyobj::real_t t = 0.0f;
        // Normal
        if (attrib.normals.size() != 0) {
          nx = attrib.normals[3 * index.normal_index + 0];
          ny = attrib.normals[3 * index.normal_index + 1];
          nz = attrib.normals[3 * index.normal_index + 1];
        }
        // UVs
        if (attrib.texcoords.size() != 0) {
          v = attrib.texcoords[2 * index.texcoord_index + 0];
          t = attrib.texcoords[2 * index.texcoord_index + 1];
        }

        Vertex new_vertex;
        new_vertex.position = {vx, vy, vz, 1.0};
        new_vertex.normal = {nx, ny, nz, 0.0};
        new_vertex.uv = {v, t};
        loaded_mesh.vertices.push_back(new_vertex);
        loaded_mesh.indices.push_back(loaded_mesh.vertices.size() - 1);
      }
      index_offset += 3;
    }
    loaded_meshes.push_back(loaded_mesh);
  }
  return loaded_meshes;
}
} // namespace sparrow_rasterizer
