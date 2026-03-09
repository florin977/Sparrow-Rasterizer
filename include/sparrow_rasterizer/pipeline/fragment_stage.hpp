#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace sparrow_rasterizer {
class FragmentStage {
private:
  static std::vector<glm::vec4> random_colors;
  static std::vector<glm::vec4> generate_random_colors(int size);

public:
  static glm::vec4 render(int triangle_id, glm::vec3 &weights);
};
} // namespace sparrow_rasterizer
