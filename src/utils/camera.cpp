#include "sparrow_rasterizer/utils/camera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace sparrow_rasterizer {
Camera::Camera()
    : position(glm::vec3{0.0f, 0.0f, -1.0f}),
      center(glm::vec3{0.0f, 0.0f, 0.0}), up(glm::vec3{0.0f, 1.0f, 0.0f}),
      fov(45.0f), near(0.1f), far(100.0f) {};

void Camera::translate(glm::vec3 move) { position += move; }

glm::mat4 Camera::get_view_matrix() {
  return glm::lookAt(position, center, up);
}

glm::mat4 Camera::get_perspective_matrix() {
  return glm::perspective(glm::radians(fov), 16.0f / 9.0f, near, far);
}
} // namespace sparrow_rasterizer
