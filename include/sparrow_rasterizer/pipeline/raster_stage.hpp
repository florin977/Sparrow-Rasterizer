#pragma once

#include "sparrow_rasterizer/utils/model_type.hpp"
#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include "sparrow_rasterizer/utils/vertex_type.hpp"

namespace sparrow_rasterizer {
class RasterStage {
public:
  static void render(std::vector<Vertex> &VSInput,
                     std::vector<Model *> models_to_render, int width,
                     int height, Buffer &pixel_buffer);
};
} // namespace sparrow_rasterizer
