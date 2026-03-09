#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
namespace sparrow_rasterizer {
class Camera {
private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;
  float yaw;
  float pitch;
  float roll;
  float fov;
  float near;
  float far;

  void update_camera_vectors();

public:
  Camera();
  void translate_forward(float speed);
  void translate_backward(float speed);
  void translate_right(float speed);
  void translate_left(float speed);
  glm::mat4 get_view_matrix();
  glm::mat4 get_perspective_matrix();
};
} // namespace sparrow_rasterizer
