#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace sparrow_rasterizer {
class DepthBuffer {
private:
  int width;
  int height;
  std::vector<float> depths;

public:
  DepthBuffer(int width, int height);
  void resize_buffer(int width, int height);
  void clear_buffer();
  void set_depth(int x, int y, float depth);
  uint32_t get_depth(int x, int y);
};
} // namespace sparrow_rasterizer
