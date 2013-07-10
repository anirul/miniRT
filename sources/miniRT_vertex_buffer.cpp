/////////////////////////////////////////////////////////////////////
// miniRT Vertex Buffer
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-amil	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include <assert.h>
#include "miniRT_new.h"
#include "miniRT_math.h"
#include "miniRT_vertex.h"
#include "miniRT_vertex_buffer.h"

namespace miniRT {

	vertex_buffer::vertex_buffer(size_t size) {
		assert(size > 0);
		nb = (int)size;
		popt = new __m128[size * 4];
		assert(popt);
	}

	vertex_buffer::~vertex_buffer() {
		if (popt)
			delete [] popt;
		popt = 0;
	}

	void vertex_buffer::set_optimized(const vertex* p) {
		assert(popt);
		for (int i = 0; i < nb; ++i) {
			int pos = i;
			memcpy(&popt[pos], &(p[i].pos), sizeof(__m128));
			pos += nb;
			memcpy(&popt[pos], &(p[i].norm), sizeof(__m128));
			pos += nb;
			memcpy(&popt[pos], &(p[i].rgba), sizeof(__m128));
			pos += nb;
			memcpy(&popt[pos], &(p[i].uv), sizeof(__m128));
		}
	}

	__m128& vertex_buffer::get_pos(int i) {
		assert(i >= 0);
		assert(i < nb);
		return popt[i];
	}

	__m128& vertex_buffer::get_normal(int i) {
		assert(i >= 0);
		assert(i < nb);
		return popt[nb + i];
	}

	__m128& vertex_buffer::get_color(int i) {
		assert(i >= 0);
		assert(i < nb);
		return popt[2 * nb + i];
	}

	__m128& vertex_buffer::get_UV(int i) {
		assert(i >= 0);
		assert(i < nb);
		return popt[3 * nb + i];
	}

} // end of namespace miniRT