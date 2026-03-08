#include "sparrow_rasterizer/utils/vertex_type.hpp"
#include <glm/fwd.hpp>
#include <sparrow_rasterizer/pipeline/vertex_stage.hpp>
#include <sparrow_rasterizer/utils/model_type.hpp>

namespace sparrow_rasterizer {

void VertexStage::render(std::vector<Model *> &models, Camera &camera,
                         std::vector<Vertex> &VSOutput) {
  glm::mat4 view_matrix = camera.get_view_matrix();
  glm::mat4 perspective_matrix = camera.get_perspective_matrix();
  glm::mat4 VP_matrix = perspective_matrix * view_matrix;

  VSOutput.clear();

  for (auto model : models) {
    glm::mat4 model_matrix = model->get_model_matrix();
    glm::mat4 MVP_matrix = VP_matrix * model_matrix;

    for (auto mesh : model->getMeshes()) {
      for (auto vertex : mesh.vertices) {

        // TODO: Make sure the normals are correctly transformed (handle
        // non-uniform scaling)
        Vertex clip_space_vertex =
            Vertex(MVP_matrix * vertex.position, model_matrix * vertex.normal,
                   vertex.uv);
        VSOutput.push_back(clip_space_vertex);
      }
    }
  }
}
} // namespace sparrow_rasterizer
