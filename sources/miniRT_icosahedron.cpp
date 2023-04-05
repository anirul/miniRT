/////////////////////////////////////////////////////////////////////
// miniRT icosahedron
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_icosahedron.h"

namespace miniRT {

icosahedron::icosahedron() {
  const vertex vb[] = {
      vertex(vector3(1.0f, 2.701302f, -0.051462f),
             vector3(1.0f, 2.701302f, -0.051462f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(1.0f, -0.701302f, -0.051462f),
             vector3(1.0f, -0.701302f, -0.051462f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(2.051462f, 1.0f, 2.701302f),
             vector3(2.051462f, 1.0f, 2.701302f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(2.051462f, 1.0f, -0.701302f),
             vector3(2.051462f, 1.0f, -0.701302f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(-0.051462f, 1.0f, 2.701302f),
             vector3(-0.051462f, 1.0f, 2.701302f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(-0.051462f, 1.0f, -0.701302f),
             vector3(-0.051462f, 1.0f, -0.701302f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(2.701302f, 2.051462f, 1.0f),
             vector3(2.701302f, 2.051462f, 1.0f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(2.701302f, -0.051462f, 1.0f),
             vector3(2.701302f, -0.051462f, 1.0f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(-0.701302f, 2.051462f, 1.0f),
             vector3(-0.701302f, 2.051462f, 1.0f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(-0.701302f, -0.051462f, 1.0f),
             vector3(-0.701302f, -0.051462f, 1.0f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(1.0f, 2.701302f, 2.051462f),
             vector3(1.0f, 2.701302f, 2.051462f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      vertex(vector3(1.0f, -0.701302f, 2.051462f),
             vector3(1.0f, -0.701302f, 2.051462f).Normalize(),
             vector4(0.0f, 1.0f, 1.0f, 1.0f)),
      // plane
      vertex(vector3(-10.0f, -2.0f, -10.0f),
             vector3(0.0f, 1.0f, 0.0f).Normalize(), vector4(1.0f, 1.0f, 0.0f)),
      vertex(vector3(10.0f, -2.0f, -10.0f),
             vector3(0.0f, 1.0f, 0.0f).Normalize(), vector4(1.0f, 1.0f, 0.0f)),
      vertex(vector3(10.0f, -2.0f, 10.0f),
             vector3(0.0f, 1.0f, 0.0f).Normalize(), vector4(1.0f, 1.0f, 0.0f)),
      vertex(vector3(-10.0f, -2.0f, 10.0f),
             vector3(0.0f, 1.0f, 0.0f).Normalize(), vector4(1.0f, 1.0f, 0.0f))};
  pvb_ = new vertex_buffer(nbvertex_);
  pvb_->set_optimized(vb);
  const int ib[] = {// icosahedron
                    10, 2, 6, 10, 6, 0, 10, 0, 8, 10, 8, 4, 10, 4, 2, 0, 6, 3,
                    0, 3, 5, 0, 5, 8, 11, 1, 7, 11, 7, 2, 11, 2, 4, 11, 4, 9,
                    11, 9, 1, 1, 9, 5, 1, 5, 3, 1, 3, 7, 2, 7, 6, 3, 6, 7, 4, 8,
                    9, 5, 9, 8,
                    // plane
                    12, 14, 13, 12, 15, 14};
  pib_ = new index_buffer(ib, nbindex_);
}

icosahedron::~icosahedron() {
  if (pvb_) delete[] pvb_;
  if (pib_) delete[] pib_;
}

}  // End namespace miniRT.