#include "sparrow_rasterizer/loader/app.hpp"
#include "sparrow_rasterizer/pipeline/graphics_pipeline.hpp"
#include "sparrow_rasterizer/utils/camera.hpp"
#include "sparrow_rasterizer/utils/command_type.hpp"
#include <sparrow_rasterizer/windowing/window_init.hpp>

using namespace sparrow_rasterizer;

int main() {
  GraphicsPipeline pipeline;
  Window window;
  App app(window, pipeline);
  Scene scene;
  Camera camera;
  Command command(CommandType::Draw_all, "./assets/Suzzane.obj");
  scene.add_model("./assets/Suzzane.obj");
  scene.camera = camera;

  scene.camera.translate(glm::vec3(0.0f, 0.0f, -5.0f));

  while (app.window.active()) {
    app.window.handle_events();
    app.pipeline.send_command(command);
    app.pipeline.execute_commands(app.window, app.window.buffer, scene);
    app.window.render();
  }

  return 0;
}
