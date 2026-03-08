#pragma once

#include "sparrow_rasterizer/utils/camera.hpp"
#include <sparrow_rasterizer/utils/model_type.hpp>

namespace sparrow_rasterizer {
class VertexStage {
public:
  static void render(std::vector<Model *> &models, Camera &camera,
                     std::vector<Vertex> &VSOutput);
};
} // namespace sparrow_rasterizer
