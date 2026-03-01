#include <glm/ext/vector_float4.hpp>
#include <sparrow_rasterizer/utils/pixel_buffer.hpp>

namespace sparrow_rasterizer {
Buffer::Buffer(int width, int height)
    : width(width), height(height), pixels(width * height, 0) {}

void Buffer::resize_buffer(int width, int height) {
  this->width = width;
  this->height = height;
  pixels.resize(width * height, 0);
}

uint32_t Buffer::vec4_to_uint32(glm::vec4 vec) {
  int x = vec.x * 255;
  int y = vec.y * 255;
  int z = vec.z * 255;
  int w = vec.w * 255;

  uint32_t result = w | (z << 8) | (y << 16) | (x << 24);
  return result;
}

void Buffer::clear_buffer(glm::vec4 color) {
  uint32_t formatted_color = vec4_to_uint32(color);
  std::fill(pixels.begin(), pixels.end(), formatted_color);
}

void Buffer::set_pixel(int x, int y, glm::vec4 color) {
  if (!(x >= 0 && y >= 0 && x < width && y < height)) {
    return;
  }
  int index = y * width + x;
  if (index >= pixels.size()) {
    return;
  }
  pixels[index] = vec4_to_uint32(color);
}

int Buffer::get_pitch() { return width * sizeof(uint32_t); }
void *Buffer::get_data() { return pixels.data(); }

} // namespace sparrow_rasterizer
