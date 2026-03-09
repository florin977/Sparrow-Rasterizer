#include <cstdlib>
#include <ctime>
#include <glm/ext/vector_float4.hpp>
#include <sparrow_rasterizer/pipeline/fragment_stage.hpp>

namespace sparrow_rasterizer {

std::vector<glm::vec4> FragmentStage::random_colors =
    FragmentStage::generate_random_colors(10);

std::vector<glm::vec4> FragmentStage::generate_random_colors(int size) {
  srand(static_cast<unsigned int>(time(NULL)));
  std::vector<glm::vec4> colors(size);

  for (int i = 0; i < size; i++) {
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    colors[i] = glm::vec4(r, g, b, 1.0f);
  }

  return colors;
}

glm::vec4 FragmentStage::render(int triangle_id, glm::vec3 &weights) {
  return random_colors[triangle_id % random_colors.size()];
}
} // namespace sparrow_rasterizer
