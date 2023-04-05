/////////////////////////////////////////////////////////////////////
// miniRT triangle
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_triangle.h"

#include <glm/glm.hpp>

#include "miniRT_new.h"
#include "miniRT_vertex.h"
#include "miniRT_vertex_buffer.h"

namespace miniRT {

triangle::triangle(vertex_buffer* vb) {
  assert(vb);
  pvb = vb;
}

bool triangle::intersect_plane(const int v0, const int v1, const int v2,
                               glm::vec3 p, glm::vec3 n) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  if (glm::dot(((glm::vec3)pvb->get_pos(v0) - p), n) <
      -std::numeric_limits<float>::epsilon()) {
    if (glm::dot(((glm::vec3)pvb->get_pos(v1) - p), n) >
        std::numeric_limits<float>::epsilon())
      return true;
    if (glm::dot(((glm::vec3)pvb->get_pos(v2) - p), n) >
        std::numeric_limits<float>::epsilon())
      return true;
  } else {
    if (glm::dot(((glm::vec3)pvb->get_pos(v1) - p), n) <
        -std::numeric_limits<float>::epsilon())
      return true;
    if (glm::dot(((glm::vec3)pvb->get_pos(v2) - p), n) <
        -std::numeric_limits<float>::epsilon())
      return true;
  }
  return false;
}

void triangle::intersect_det(const int v0, const int v1, const int v2,
                             glm::vec3 o, glm::vec3 d, glm::vec4* pvd) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());
  assert(pvd);

  glm::vec3 edge1, edge2, pvec;
  edge1 = (glm::vec3)pvb->get_pos(v1) - (glm::vec3)pvb->get_pos(v0);
  edge2 = (glm::vec3)pvb->get_pos(v2) - (glm::vec3)pvb->get_pos(v0);
  pvec = glm::cross(d, edge2);
  float det = glm::dot(edge1, pvec);
  *pvd = glm::vec4(pvec, 0.0f);
  pvd->w = det;
}

bool triangle::intersect_ray(const int v0, const int v1, const int v2,
                             glm::vec4 pvd, glm::vec3 o, glm::vec3 d,
                             glm::vec3 m) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  glm::vec3 tvec, qvec, pv;
  float u, v, det;
  pv = pvd;
  det = pvd.w;

  if (det > std::numeric_limits<float>::epsilon()) return false;
  tvec = o - glm::vec3(pvb->get_pos(v0));
  u = glm::dot(tvec, pv);
  if (u < -std::numeric_limits<float>::epsilon() || u > det) return false;
  qvec = glm::cross(tvec, ((glm::vec3)pvb->get_pos(v1) - (glm::vec3)pvb->get_pos(v0)));
  v = glm::dot(d, qvec);
  if (v < -std::numeric_limits<float>::epsilon() || u + v > det) return false;
  // check position
  return true;
}

bool triangle::shadow_hit(const int v0, const int v1, const int v2, glm::vec3 o,
                          glm::vec3 d, const float tmin, const float tmax) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  glm::vec3 p0 = (glm::vec3)pvb->get_pos(v0);
  glm::vec3 p1 = (glm::vec3)pvb->get_pos(v1);
  glm::vec3 p2 = (glm::vec3)pvb->get_pos(v2);

  glm::vec3 ABC = p0 - p1;
  glm::vec3 DEF = p0 - p2;
  glm::vec3 GHI = d;
  glm::vec3 JKL = p0 - o;

  glm::vec3 smat = glm::cross(DEF, GHI);

  float denom = glm::dot(ABC, smat);
  float inv_denom = 1 / denom;
  float beta = glm::dot(JKL, smat) * inv_denom;

  if (beta <= 0.0f || beta >= 1.0f) return false;

  smat = glm::cross(ABC, JKL);

  float gamma = glm::dot(GHI, smat) * inv_denom;
  if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;

  float tval = -glm::dot(DEF, smat) * inv_denom;

  return (tval >= tmin && tval <= tmax);
}

bool triangle::intersect_barycentric(const int v0, const int v1, const int v2,
                                     glm::vec4 pvd, glm::vec3 o, glm::vec3 d,
                                     glm::vec4* tuv) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  glm::vec3 tvec, qvec, pv;
  float inv_det, det;
  pv = pvd;
  det = pvd.w;
  assert(det > std::numeric_limits<float>::epsilon());

  tvec = o - glm::vec3(pvb->get_pos(v0));
  tuv->y = glm::dot(tvec, pv);
  if (tuv->y < -std::numeric_limits<float>::epsilon() || tuv->y > det)
    return false;
  qvec = glm::cross(
      tvec, ((glm::vec3)pvb->get_pos(v1) - (glm::vec3)pvb->get_pos(v0)));
  tuv->z = glm::dot(d, qvec);
  if (tuv->z < -std::numeric_limits<float>::epsilon() || tuv->z + tuv->y > det)
    return false;
  glm::vec3 dot_res = (glm::vec3)pvb->get_pos(v2) - (glm::vec3)pvb->get_pos(v0);
  tuv->x = glm::dot(dot_res, qvec);
  inv_det = 1.0f / det;
  tuv->x *= inv_det;
  tuv->y *= inv_det;
  tuv->z *= inv_det;
  return tuv->x > 0;
}

glm::vec3 triangle::intersect_point(glm::vec4 tuv, glm::vec3 o, glm::vec3 d) {
  return o + d * tuv.x;
}

glm::vec3 triangle::intersect_normal(const int v0, const int v1, const int v2,
                                     glm::vec4 tuv) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  return ((glm::vec3)pvb->get_normal(v0) * (1.0f - (tuv.y + tuv.z))) +
         ((glm::vec3)pvb->get_normal(v1) * tuv.y) +
         ((glm::vec3)pvb->get_normal(v2) * tuv.z);
}

glm::vec2 triangle::intersect_texmap(const int v0, const int v1, const int v2,
                                     glm::vec4 tuv) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  // scaled texture coordinates
  float stc[6];
  // CHECKME
  stc[0] = (1.0f - tuv.y - tuv.z) * pvb->get_UV(v0).x;
  stc[1] = (1.0f - tuv.y - tuv.z) * pvb->get_UV(v0).x;
  stc[2] = tuv.y * pvb->get_UV(v1).x;
  stc[3] = tuv.y * pvb->get_UV(v1).y;
  stc[4] = tuv.z * pvb->get_UV(v2).x;
  stc[5] = tuv.z * pvb->get_UV(v2).y;
  glm::vec2 uv;
  uv.x = stc[0] + stc[2] + stc[4];
  uv.y = stc[1] + stc[3] + stc[5];
  return uv;
}

glm::vec4 triangle::intersect_col(const int v0, const int v1, const int v2,
                                  glm::vec4 tuv) {
  assert(pvb);
  assert(v0 >= 0);
  assert(v0 < pvb->size());
  assert(v1 >= 0);
  assert(v1 < pvb->size());
  assert(v2 >= 0);
  assert(v2 < pvb->size());

  glm::vec4 a = glm::vec4(pvb->get_color(v0), 1.0);
  glm::vec4 b = glm::vec4(pvb->get_color(v1), 1.0);
  glm::vec4 c = glm::vec4(pvb->get_color(v2), 1.0);

  return a * (1.0f - (tuv.y + tuv.z)) + b * tuv.y + c * tuv.z;
}

}  // namespace miniRT
