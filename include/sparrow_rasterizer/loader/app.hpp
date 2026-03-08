#pragma once

#include "sparrow_rasterizer/pipeline/graphics_pipeline.hpp"
#include "sparrow_rasterizer/windowing/window_init.hpp"
#include <glm/ext/scalar_constants.hpp>
namespace sparrow_rasterizer {
class App {
public:
  Window &window;
  GraphicsPipeline &pipeline;
  App(Window &window, GraphicsPipeline &pipeline);
};
} // namespace sparrow_rasterizer
