/////////////////////////////////////////////////////////////////////
// miniRT camera (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_CAM_HEADER__
#define __MINIRT_CAM_HEADER__

#include "miniRT_math.h"

namespace miniRT {

class camera {
  vector3 up;
  vector3 to;
  vector3 pos;
  vector3 right;
  float fov;

 public:
  camera();
  camera(const vector3& vup, const vector3& vto, const vector3& vpos,
         const float ffov = M_PI_4);
  camera& operator()(const vector3& vup, const vector3& vto,
                     const vector3& vpos, const float ffov = M_PI_4);
  camera& set_up(const vector3& in);
  camera& set_to(const vector3& in);
  camera& set_pos(const vector3& in);
  camera& set_right(const vector3& in);
  camera& set_fov(float in);
  vector3 get_up() const { return up; }
  vector3 get_to() const { return to; }
  vector3 get_pos() const { return pos; }
  vector3 get_right() const { return right; }
  float get_fov() const { return fov; }
  camera& fix_perp();
  camera& look_at(const vector3& target, const float roll);
};

}  // namespace miniRT

#endif  // __MINIRT_CAM_HEADER__