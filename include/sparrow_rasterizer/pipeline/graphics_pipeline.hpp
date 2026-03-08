#pragma once

#include "sparrow_rasterizer/windowing/window_init.hpp"
#include <sparrow_rasterizer/utils/command_type.hpp>
#include <sparrow_rasterizer/utils/scene.hpp>
#include <sparrow_rasterizer/utils/triangle_type.hpp>
#include <sparrow_rasterizer/utils/vertex_type.hpp>
#include <vector>

namespace sparrow_rasterizer {
class GraphicsPipeline {
private:
  std::vector<Vertex> VSOutput;
  std::vector<Triangle> primitive_assembly;
  std::vector<Command> commands;

public:
  GraphicsPipeline();
  void send_command(Command command);
  void execute_commands(Window &window, Buffer &pixel_buffer, Scene &scene);
};
} // namespace sparrow_rasterizer
