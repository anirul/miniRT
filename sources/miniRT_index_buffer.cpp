/////////////////////////////////////////////////////////////////////
// miniRT index buffer
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_index_buffer.h"

#include <assert.h>
#include <glm/glm.hpp>

#include "miniRT_new.h"

namespace miniRT {

index_buffer::index_buffer(const int* ib, int l) {
  assert(l > 0);
  assert(ib);
  nb = l;
  pi = new int[nb];
  memcpy(pi, ib, sizeof(int) * nb);
  assert(pi);
}

index_buffer::~index_buffer() {
  if (pi) delete[] pi;
  pi = 0;
  nb = 0;
}

int& index_buffer::operator[](int i) {
  assert(i >= 0);
  assert(i < nb);
  return pi[i];
}

int index_buffer::get(int i) const {
  assert(i >= 0);
  assert(i < nb);
  return pi[i];
}

}  // end of namespace miniRT