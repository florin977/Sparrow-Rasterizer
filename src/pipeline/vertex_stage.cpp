#include <glm/fwd.hpp>
#include <sparrow_rasterizer/pipeline/vertex_stage.hpp>
#include <sparrow_rasterizer/utils/model_type.hpp>

namespace sparrow_rasterizer {
void VertexStage::render(std::vector<Model *> &models, Camera &camera) {
  for (auto model : models) {
    glm::mat4 model_matrix = model->get_model_matrix();
    glm::mat4 view_matrix = camera.get_view_matrix();
    glm::mat4 perspective_matrix = camera.get_perspective_matrix();
    glm::mat4 MVP_matrix = perspective_matrix * view_matrix * model_matrix;
  }
}
} // namespace sparrow_rasterizer
