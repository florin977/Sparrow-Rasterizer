#pragma once

#include <sparrow_rasterizer/utils/command_type.hpp>
#include <sparrow_rasterizer/utils/scene.hpp>
#include <vector>

namespace sparrow_rasterizer {
class GraphicsPipeline {
private:
  std::vector<Command> commands;

public:
  GraphicsPipeline();
  void send_command(Command command);
  void execute_commands(Scene &scene);
};
} // namespace sparrow_rasterizer
