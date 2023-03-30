/////////////////////////////////////////////////////////////////////
// miniRT triangle (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////
// holder for the intersection algorithmes.

#ifndef __MINIRT_TRIANGLE_DEFINED__
#define __MINIRT_TRIANGLE_DEFINED__

namespace miniRT {

class triangle {
  vertex_buffer* pvb;

 public:
  triangle(vertex_buffer* vb);

  bool intersect_plane(const int v0, const int v1, const int v2,
                       const vector3& p, const vector3& n);

  // pvd holds pv and det result :
  // vector4(pv[0], pv[1], pv[2], det)
  void intersect_det(const int v0, const int v1, const int v2, const vector3& o,
                     const vector3& d, vector4* pvd);

  bool intersect_ray(const int v0, const int v1, const int v2,
                     const vector4& pvd, const vector3& o, const vector3& d,
                     const vector3& m);

  bool shadow_hit(const int v0, const int v1, const int v2, const vector3& o,
                  const vector3& d, const float tmin, const float tmax);

  bool intersect_barycentric(const int v0, const int v1, const int v2,
                             const vector4& pvd, const vector3& o,
                             const vector3& d, vector4* tuv);

  vector3 intersect_point(const vector4& tuv, const vector3& o,
                          const vector3& d);

  vector3 intersect_normal(const int v0, const int v1, const int v2,
                           const vector4& tuv);

  vector2 intersect_texmap(const int v0, const int v1, const int v2,
                           const vector4& tuv);

  vector4 intersect_col(const int v0, const int v1, const int v2,
                        const vector4& tuv);
};

}  // namespace miniRT

#endif  // __MINIRT_TRIANGLE_DEFINED__