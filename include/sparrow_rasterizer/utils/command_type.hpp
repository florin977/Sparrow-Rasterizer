#pragma once
#include <string>
namespace sparrow_rasterizer {
enum class CommandType {
  Draw,
  Draw_all,
};

class Command {
public:
  CommandType type;
  std::string filename;

  Command(CommandType type, const std::string &filename);
};
} // namespace sparrow_rasterizer
