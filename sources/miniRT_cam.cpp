/////////////////////////////////////////////////////////////////////
// miniRT camera (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>

#include "miniRT_cam.h"

namespace miniRT {

camera::camera() {
  pos = glm::vec3(0.0f, 0.0f, 0.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
  to = glm::vec3(0.0f, 0.0f, 1.0f);
  right = glm::vec3(1.0f, 0.0f, 0.0f);
  fix_perp();
  fov = (float)M_PI_4;
}

camera::camera(glm::vec3 vup, glm::vec3 vto, glm::vec3 vpos,
               const float ffov) {
  up = vup;
  to = vto;
  pos = vpos;
  fov = ffov;
  fix_perp();
}

camera& camera::set_up(glm::vec3 in) {
  up = in;
  return *this;
}

camera& camera::set_to(glm::vec3 in) {
  to = in;
  return *this;
}

camera& camera::set_pos(glm::vec3 in) {
  pos = in;
  return *this;
}

camera& camera::set_right(glm::vec3 in) {
  right = in;
  return *this;
}

camera& camera::set_fov(const float in) {
  fov = in;
  return *this;
}

camera& camera::fix_perp() {
  right = glm::cross(up, to);
  up = glm::cross(to, right);
  to = glm::normalize(to);
  right = glm::normalize(right);
  up = glm::normalize(up);
  return *this;
}

camera& camera::operator()(glm::vec3 vup, glm::vec3 vto,
                           glm::vec3 vpos, const float ffov) {
  up = vup;
  to = vto;
  pos = vpos;
  fix_perp();
  fov = ffov;
  return *this;
}
                             
camera& camera::look_at(glm::vec3 target, const float roll) {
  // rotate
  up[0] = sinf(roll);
  up[1] = cosf(roll);
  up[2] = 0.0f;
  // change target
  to = target - pos;
  fix_perp();
  return *this;
}

}  // namespace miniRT