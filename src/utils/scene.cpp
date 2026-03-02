#include "sparrow_rasterizer/utils/scene.hpp"
#include "sparrow_rasterizer/utils/model_type.hpp"
#include <algorithm>
#include <glm/common.hpp>
#include <glm/fwd.hpp>
#include <sparrow_rasterizer/loader/obj_loader.hpp>
#include <string>
namespace sparrow_rasterizer {
Scene::Scene() {};
void Scene::add_model(const std::string &filename) {
  Model model(filename);
  models.push_back(model);
}

void Scene::remove_model(const std::string &filename) {
  auto it =
      std::find_if(models.begin(), models.end(), [&filename](const Model &m) {
        return m.model_name == filename;
      });

  if (it != models.end()) {
    models.erase(it);
  }
}
} // namespace sparrow_rasterizer
