#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace sparrow_rasterizer {
class Pixel {
public:
  int x, y;
  Pixel(int x, int y);
};
} // namespace sparrow_rasterizer
