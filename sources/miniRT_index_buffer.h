/////////////////////////////////////////////////////////////////////
// miniRT index buffer
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

namespace miniRT {

	class index_buffer {
		int* pi;
		int nb;
	public :
		index_buffer(const int* ib, int l);
		~index_buffer();
		int& operator[](int i);
		int get(int i) const;
		int size() const { return nb; }
	};

} // end namespace miniRT