/////////////////////////////////////////////////////////////////////
// miniRT Screen buffer (spec)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_SCREEN_BUFFER_DEFINED__
#define __MINIRT_SCREEN_BUFFER_DEFINED__

namespace miniRT {

	template<class T>
	class screen_buffer {
		int dx, dy;
	public:
		T* pv;
		screen_buffer(int x, int y);
		~screen_buffer();
		T& operator()(int x, int y) 
			{ return pv[x + ((dy - 1) - y) * dx]; }
		const T& operator()(int x, int y) const 
			{ return pv[x + ((dy - 1) - y) * dx]; }
		void clear(const T& v);
	};

	template<class T>
	screen_buffer<T>::screen_buffer(int x, int y) {
		assert(x > 0);
		assert(y > 0);
		pv = new T[x * y];
		assert(pv);
		dx = x;
		dy = y;
	}

	template<class T>
	screen_buffer<T>::~screen_buffer() {
		if (pv) delete [] pv;
	}

	template<class T>
	void screen_buffer<T>::clear(const T& v) {
		for (int i = 0; i < dx * dy; ++i)
			pv[i] = v;
	}

} // end of namespace miniRT

#endif // __MINIRT_SCREEN_BUFFER_DEFINED__