/////////////////////////////////////////////////////////////////////
// miniRT icosahedron
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_TEAPOT_DEFINED__
#define __MINIRT_TEAPOT_DEFINED__

#include "miniRT_index_buffer.h"
#include "miniRT_vertex.h"
#include "miniRT_vertex_buffer.h"

namespace miniRT {

class teapot {
 public:
  teapot();
  ~teapot();
  size_t get_ib_size() const { return nbindex; }
  index_buffer* get_ib() { return pib; }
  size_t get_vb_size() const { return nbvertex; }
  vertex_buffer* get_vb() { return pvb; }

 private:
  static constexpr size_t nbindex = 1178;
  static constexpr size_t nbvertex = 2256 * 3;
  vertex_buffer* pvb;
  index_buffer* pib;
};

}  // end namespace miniRT

#endif  // __MINIRT_TEAPOT_DEFINED__