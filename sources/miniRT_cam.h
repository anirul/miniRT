/////////////////////////////////////////////////////////////////////
// miniRT camera (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_CAM_HEADER__
#define __MINIRT_CAM_HEADER__

#define _USE_MATH_DEFINES
#include <math.h>

#include <glm/glm.hpp>

namespace miniRT {

class camera {
  glm::vec3 up;
  glm::vec3 to;
  glm::vec3 pos;
  glm::vec3 right;
  float fov;

 public:
  camera();
  camera(glm::vec3 vup, glm::vec3 vto, glm::vec3 vpos,
         const float ffov = M_PI_4);
  camera& operator()(glm::vec3 vup, glm::vec3 vto,
                     glm::vec3 vpos, const float ffov = M_PI_4);
  camera& set_up(glm::vec3 in);
  camera& set_to(glm::vec3 in);
  camera& set_pos(glm::vec3 in);
  camera& set_right(glm::vec3 in);
  camera& set_fov(float in);
  glm::vec3 get_up() const { return up; }
  glm::vec3 get_to() const { return to; }
  glm::vec3 get_pos() const { return pos; }
  glm::vec3 get_right() const { return right; }
  float get_fov() const { return fov; }
  camera& fix_perp();
  camera& look_at(glm::vec3 target, const float roll);
};

}  // namespace miniRT

#endif  // __MINIRT_CAM_HEADER__