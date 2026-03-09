#pragma once

#include "sparrow_rasterizer/utils/depth_buffer.hpp"
#include "sparrow_rasterizer/utils/model_type.hpp"
#include "sparrow_rasterizer/utils/triangle_type.hpp"
#include "sparrow_rasterizer/utils/vertex_type.hpp"

namespace sparrow_rasterizer {
class RasterStage {
public:
  static void render(std::vector<Vertex> &VSInput,
                     std::vector<Model *> models_to_render, int width,
                     int height, Buffer &pixel_buffer,
                     DepthBuffer &depth_buffer);
};
} // namespace sparrow_rasterizer
