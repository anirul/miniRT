/////////////////////////////////////////////////////////////////////
// miniRT vertex (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_VERTEX_HEADER__
#define __MINIRT_VERTEX_HEADER__

#include "miniRT_math.h"

namespace miniRT {

class vertex {
 public:
  vertex(const vector3& vp = vector3(0.0f, 0.0f, 0.0f),
         const vector3& vn = vector3(0.0f, 0.0f, 0.0f),
         const vector4& vc = vector4(1.0, 1.0, 1.0, 1.0),
         const vector2& vt = vector2(0.0, 0.0))
      : pos(vp), norm(vn), rgba(vc), uv(vt) {}
  vector3 pos;
  vector3 norm;
  vector4 rgba;
  vector2 uv;
};

}  // end of namespace miniRT

#endif  // __MINIRT_VERTEX_HEADER__