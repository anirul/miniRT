/////////////////////////////////////////////////////////////////////
// miniRT Vertex Buffer
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-amil	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_vertex_buffer.h"

#include <assert.h>
#include <glm/glm.hpp>

#include "miniRT_new.h"
#include "miniRT_vertex.h"

namespace miniRT {

vertex_buffer::vertex_buffer(size_t size) {
  assert(size > 0);
  nb = (int)size;
  popt = new glm::vec3[size * 4];
  assert(popt);
}

vertex_buffer::~vertex_buffer() {
  if (popt) delete[] popt;
  popt = 0;
}

void vertex_buffer::set_optimized(const vertex* p) {
  assert(popt);
  for (int i = 0; i < nb; ++i) {
    int pos = i;
    memcpy(&popt[pos], &(p[i].pos), sizeof(glm::vec3));
    pos += nb;
    memcpy(&popt[pos], &(p[i].norm), sizeof(glm::vec3));
    pos += nb;
    memcpy(&popt[pos], &(p[i].rgba), sizeof(glm::vec3));
    pos += nb;
    memcpy(&popt[pos], &(p[i].uv), sizeof(glm::vec3));
  }
}

glm::vec3 vertex_buffer::get_pos(int i) {
  assert(i >= 0);
  assert(i < nb);
  return popt[i];
}

glm::vec3 vertex_buffer::get_normal(int i) {
  assert(i >= 0);
  assert(i < nb);
  return popt[nb + i];
}

glm::vec3 vertex_buffer::get_color(int i) {
  assert(i >= 0);
  assert(i < nb);
  return popt[2 * nb + i];
}

glm::vec3 vertex_buffer::get_UV(int i) {
  assert(i >= 0);
  assert(i < nb);
  return popt[3 * nb + i];
}

}  // end of namespace miniRT
