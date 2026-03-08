#include "sparrow_rasterizer/utils/model_type.hpp"
#include "sparrow_rasterizer/loader/obj_loader.hpp"
#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <string>

namespace sparrow_rasterizer {
Model::Model() {
  translation = glm::vec3(0.0f, 0.0f, 0.0f);
  rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  scaling = glm::vec3(1.0f, 1.0f, 1.0f);
};
Model::Model(const std::string &filename) : model_name(filename) {
  translation = glm::vec3(0.0f, 0.0f, 0.0f);
  rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  scaling = glm::vec3(1.0f, 1.0f, 1.0f);
  meshes = ObjLoader::load(filename);
}

std::vector<Mesh> &Model::getMeshes() { return this->meshes; }

glm::mat4 Model::get_model_matrix() {
  glm::mat4 model_matrix = glm::mat4(1.0f);

  glm::vec3 x_axis = glm::vec3(1.0f, 0.0f, 0.0f);
  glm::vec3 y_axis = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 z_axis = glm::vec3(0.0f, 0.0f, 1.0f);

  model_matrix = glm::translate(model_matrix, translation);
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x), x_axis);
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y), y_axis);
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z), z_axis);
  model_matrix = glm::scale(model_matrix, scaling);

  return model_matrix;
}

void Model::translate(glm::vec3 move) { translation += move; }
void Model::rotate(glm::vec3 angles) { rotation += angles; }
void Model::scale(glm::vec3 scales) { scaling += scales; }
} // namespace sparrow_rasterizer
