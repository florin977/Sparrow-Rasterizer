#include <sparrow_rasterizer/utils/camera.hpp>
#include <sparrow_rasterizer/utils/model_type.hpp>
#include <string>
#include <vector>

namespace sparrow_rasterizer {
class Scene {
public:
  std::vector<Model> models;
  Camera camera;

  Scene();
  void add_model(const std::string &filename);
  void remove_model(const std::string &filename);
};
} // namespace sparrow_rasterizer
