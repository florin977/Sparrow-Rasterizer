#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace sparrow_rasterizer {
class Buffer {
private:
  int width;
  int height;
  std::vector<uint32_t> pixels;
  uint32_t vec4_to_uint32(glm::vec4 vec);

public:
  Buffer(int width, int height);
  void resize_buffer(int width, int height);
  void clear_buffer(glm::vec4 color);
  void set_pixel(int x, int y, glm::vec4 color);
  uint32_t get_pixel(int x, int y);
  int get_pitch();
  void *get_data();
};
} // namespace sparrow_rasterizer
