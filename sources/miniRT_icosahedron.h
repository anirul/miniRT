/////////////////////////////////////////////////////////////////////
// miniRT icosahedron
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_ICOSAHEDRON_DEFINED__
#define __MINIRT_ICOSAHEDRON_DEFINED__

#include "miniRT_index_buffer.h"
#include "miniRT_vertex.h"
#include "miniRT_vertex_buffer.h"

namespace miniRT {

class icosahedron {
 public:
  icosahedron();
  ~icosahedron();
  index_buffer* get_ib() { return pib_; }
  size_t get_ib_size() const { return nbindex_; }
  vertex_buffer* get_vb() { return pvb_; }
  size_t get_vb_size() const { return nbvertex_; }

 private:
  static constexpr size_t nbvertex_ = 16;
  static constexpr size_t nbindex_ = 20 * 3 + 6;
  vertex_buffer* pvb_ = nullptr;
  index_buffer* pib_ = nullptr;
};

}  // end namespace miniRT

#endif  // __MINIRT_ICOSAHEDRON_DEFINED__