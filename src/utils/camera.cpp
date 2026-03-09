#include "sparrow_rasterizer/utils/camera.hpp"
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sparrow_rasterizer {
Camera::Camera()
    : position(glm::vec3{0.0f, 0.0f, 3.0f}),
      front(glm::vec3{0.0f, 0.0f, -1.0f}), right(glm::vec3{1.0f, 0.0f, 0.0f}),
      up(glm::vec3{0.0f, 1.0f, 0.0f}), yaw(0.0f), pitch(0.0f), roll(0.0f),
      near(0.1f), far(100.0f), fov(45.0f) {
  update_camera_vectors();
};

void Camera::update_camera_vectors() {
  glm::vec3 euler_angles(glm::radians(pitch), glm::radians(yaw),
                         glm::radians(roll));

  glm::quat orientation = glm::quat(euler_angles);

  front = glm::normalize(orientation * glm::vec3(0.0f, 0.0f, -1.0f));
  right = glm::normalize(orientation * glm::vec3(1.0f, 0.0f, 0.0f));
  up = glm::normalize(orientation * glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::translate_forward(float speed) { position += front * speed; }
void Camera::translate_backward(float speed) { position -= front * speed; }
void Camera::translate_right(float speed) { position += right * speed; }
void Camera::translate_left(float speed) { position -= right * speed; }

glm::mat4 Camera::get_view_matrix() {
  glm::vec3 euler_angles(glm::radians(pitch), glm::radians(yaw), 0.0f);
  glm::quat orientation = glm::quat(euler_angles);

  glm::mat4 translation = glm::translate(glm::mat4(1.0f), -position);

  glm::mat4 rotation = glm::mat4_cast(glm::conjugate(orientation));

  return rotation * translation;
}

glm::mat4 Camera::get_perspective_matrix() {
  return glm::perspective(glm::radians(fov), 16.0f / 9.0f, near, far);
}
} // namespace sparrow_rasterizer
