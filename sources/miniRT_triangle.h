/////////////////////////////////////////////////////////////////////
// miniRT triangle (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////
// holder for the intersection algorithmes.

#ifndef __MINIRT_TRIANGLE_DEFINED__
#define __MINIRT_TRIANGLE_DEFINED__

#include <glm/glm.hpp>

namespace miniRT {

class vertex_buffer;

class triangle {
  vertex_buffer* pvb;

 public:
  triangle(vertex_buffer* vb);

  bool intersect_plane(const int v0, const int v1, const int v2, glm::vec3 p,
                       glm::vec3 n);

  // pvd holds pv and det result :
  // glm::vec4(pv[0], pv[1], pv[2], det)
  void intersect_det(const int v0, const int v1, const int v2, glm::vec3 o,
                     glm::vec3 d, glm::vec4* pvd);

  bool intersect_ray(const int v0, const int v1, const int v2, glm::vec4 pvd,
                     glm::vec3 o, glm::vec3 d, glm::vec3 m);

  bool shadow_hit(const int v0, const int v1, const int v2, glm::vec3 o,
                  glm::vec3 d, const float tmin, const float tmax);

  bool intersect_barycentric(const int v0, const int v1, const int v2,
                             glm::vec4 pvd, glm::vec3 o, glm::vec3 d,
                             glm::vec4* tuv);

  glm::vec3 intersect_point(glm::vec4 tuv, glm::vec3 o, glm::vec3 d);

  glm::vec3 intersect_normal(const int v0, const int v1, const int v2,
                             glm::vec4 tuv);

  glm::vec2 intersect_texmap(const int v0, const int v1, const int v2,
                             glm::vec4 tuv);

  glm::vec4 intersect_col(const int v0, const int v1, const int v2,
                          glm::vec4 tuv);
};

}  // namespace miniRT

#endif  // __MINIRT_TRIANGLE_DEFINED__