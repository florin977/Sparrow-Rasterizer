#include "sparrow_rasterizer/loader/app.hpp"

using namespace sparrow_rasterizer;

int main() {
  GraphicsPipeline pipeline;
  Window window;
  App app(window, pipeline);
  Scene scene;
  Camera camera;
  Command command(CommandType::Draw_all, "");
  scene.add_model("./assets/dragon.obj");
  scene.camera = camera;

  while (app.window.active()) {
    app.window.handle_events(scene);
    app.pipeline.send_command(command);
    app.pipeline.execute_commands(app.window, app.window.buffer,
                                  app.window.depth_buffer, scene);
    app.window.render();
  }

  return 0;
}
