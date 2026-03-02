#include "sparrow_rasterizer/utils/mesh_type.hpp"
#include <string>
namespace sparrow_rasterizer {
class ObjLoader {
public:
  static std::vector<Mesh> load(const std::string &filepath);
};
} // namespace sparrow_rasterizer
