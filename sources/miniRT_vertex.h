/////////////////////////////////////////////////////////////////////
// miniRT vertex (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_VERTEX_HEADER__
#define __MINIRT_VERTEX_HEADER__

#include <glm/glm.hpp>

namespace miniRT {

class vertex {
 public:
  vertex(glm::vec3 vp = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 vn = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec4 vc = glm::vec4(1.0, 1.0, 1.0, 1.0),
         glm::vec2 vt = glm::vec2(0.0, 0.0))
      : pos(vp), norm(vn), rgba(vc), uv(vt) {}
  glm::vec3 pos;
  glm::vec3 norm;
  glm::vec4 rgba;
  glm::vec2 uv;
};

}  // end of namespace miniRT

#endif  // __MINIRT_VERTEX_HEADER__