/////////////////////////////////////////////////////////////////////
// miniRT Vertex Buffer
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_VERTEXBUFFER_HEADER__
#define __MINIRT_VERTEXBUFFER_HEADER__

namespace miniRT {

	class vertex_buffer {
		// optimized storage for vector
		__m128* popt;
		int nb;
	public :
		// create and delete the buffer
		vertex_buffer(size_t size);
		~vertex_buffer();
		// set the datas and optimize (interlace)
		void set_optimized(const vertex* p);
		// get the values
		int size() const { return nb; }
		__m128& get_pos(int i);
		__m128& get_normal(int i);
		__m128& get_color(int i);
		__m128& get_UV(int i);
	};

} // end of namespace miniRT

#endif // __MINIRT_VERTEXBUFFER_HEADER__
