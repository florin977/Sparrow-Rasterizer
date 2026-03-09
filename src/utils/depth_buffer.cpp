#include <sparrow_rasterizer/utils/depth_buffer.hpp>

namespace sparrow_rasterizer {
DepthBuffer::DepthBuffer(int width, int height)
    : width(width), height(height),
      depths(std::vector<float>(width * height, 1.0f)) {}

void DepthBuffer::resize_buffer(int width, int height) {
  this->width = width;
  this->height = height;
  depths.resize(width * height, 1.0f);
}

void DepthBuffer::clear_buffer() {
  std::fill(depths.begin(), depths.end(), 1.0f);
}

void DepthBuffer::set_depth(int x, int y, float depth) {
  if (!(x >= 0 && y >= 0 && x < width && y < height)) {
    return;
  }
  int index = y * width + x;
  if (index >= depths.size()) {
    return;
  }
  depths[index] = depth;
}

uint32_t DepthBuffer::get_depth(int x, int y) {
  if (!(x >= 0 && y >= 0 && x < width && y < height)) {
    return 1.0f;
  }
  int index = y * width + x;
  if (index >= depths.size()) {
    return 1.0f;
  }

  return depths[index];
}
} // namespace sparrow_rasterizer
