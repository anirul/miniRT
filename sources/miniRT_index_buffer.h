/////////////////////////////////////////////////////////////////////
// miniRT index buffer
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_INDEX_BUFFER_DEFINED__
#define __MINIRT_INDEX_BUFFER_DEFINED__

namespace miniRT {

class index_buffer {
  int* pi;
  int nb;

 public:
  index_buffer(const int* ib, int l);
  ~index_buffer();
  int& operator[](int i);
  int get(int i) const;
  int size() const { return nb; }
};

}  // end namespace miniRT

#endif // __MINIRT_INDEX_BUFFER_DEFINED__