#pragma once

#include "sparrow_rasterizer/utils/mesh_type.hpp"
#include <glm/fwd.hpp>
#include <sparrow_rasterizer/utils/vertex_type.hpp>
#include <string>

namespace sparrow_rasterizer {
class Model {
private:
  std::vector<Mesh> meshes;
  glm::vec3 translation;
  glm::vec3 rotation;
  glm::vec3 scaling;

public:
  std::string model_name;
  Model();
  Model(const std::string &filename);
  glm::mat4 get_model_matrix();
  void translate(glm::vec3 move);
  void rotate(glm::vec3 angles);
  void scale(glm::vec3 scales);
};
} // namespace sparrow_rasterizer
