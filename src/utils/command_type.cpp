#include <sparrow_rasterizer/utils/command_type.hpp>

namespace sparrow_rasterizer {
Command::Command(CommandType type, const std::string &filename)
    : type(type), filename(filename) {};
}
