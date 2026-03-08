#include "sparrow_rasterizer/pipeline/graphics_pipeline.hpp"
#include "sparrow_rasterizer/pipeline/raster_stage.hpp"
#include "sparrow_rasterizer/pipeline/vertex_stage.hpp"
#include "sparrow_rasterizer/utils/command_type.hpp"
#include "sparrow_rasterizer/utils/model_type.hpp"
#include "sparrow_rasterizer/utils/pixel_buffer.hpp"
#include "sparrow_rasterizer/windowing/window_init.hpp"
#include <algorithm>

namespace sparrow_rasterizer {
GraphicsPipeline::GraphicsPipeline() {};

void GraphicsPipeline::send_command(Command command) {
  commands.push_back(command);
}

void GraphicsPipeline::execute_commands(Window &window, Buffer &pixel_buffer,
                                        Scene &scene) {
  if (commands.empty()) {
    return;
  }

  std::vector<Model *> models_to_render;
  models_to_render.reserve(scene.models.size());

  for (auto &model : scene.models) {
    models_to_render.push_back(&model);
  }
  /*
  if (commands[0].type == CommandType::Draw_all) {
    for (auto &model : scene.models) {
      models_to_render.push_back(&model);
    }
  } else {
    for (const auto &command : commands) {
      if (command.type == CommandType::Draw) {
        auto it = std::find_if(scene.models.begin(), scene.models.end(),
                               [&command](const Model &model) {
                                 return model.model_name == command.filename;
                               });
        if (it != scene.models.end()) {
          models_to_render.push_back(&(*it));
        }
      }
    }
  }
  */

  // VSOutput will contain Clip Space coordinates
  VertexStage::render(models_to_render, scene.camera, VSOutput);
  RasterStage::render(VSOutput, models_to_render, window.width, window.height,
                      pixel_buffer);

  commands.clear();
}
} // namespace sparrow_rasterizer
