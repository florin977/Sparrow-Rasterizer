#pragma once
#include <glm/glm.hpp>
namespace sparrow_rasterizer {
class Camera {
private:
  glm::vec3 position;
  glm::vec3 center;
  glm::vec3 up;
  float fov;
  float near;
  float far;

public:
  Camera();
  void translate(glm::vec3 move);
  glm::mat4 get_view_matrix();
  glm::mat4 get_perspective_matrix();
};
} // namespace sparrow_rasterizer
