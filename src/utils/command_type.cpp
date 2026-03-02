#include <sparrow_rasterizer/utils/command_type.hpp>

namespace sparrow_rasterizer {
Command::Command(CommandType type, std::string &filename)
    : type(type), filename(filename) {};
}
