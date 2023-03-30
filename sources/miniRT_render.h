/////////////////////////////////////////////////////////////////////
// miniRT Render
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_RENDER_DEFINED__
#define __MINIRT_RENDER_DEFINED__

namespace miniRT {

class render {
  window* pw;
  vertex_buffer* pvb;
  camera cam;
  index_buffer* pib;
  bool init;
  bool lock;
  int dx, dy;
  int maxobj;
  bool *sldx, *sldy;
  vector4* bound_tri;
  triangle* tri;
  light* pl;
  int lcount;
  screen_buffer<float>* pzsb;
  screen_buffer<unsigned int>* pisb;
  vector3 top_left;
  vector3 right_step;
  vector3 up_step;
  unsigned int phong(const vector4& tuvi, const vector3& dir, int i);
  unsigned int clampRGBA(const vector4& v);

 public:
  // create the scan line structure
  render(window* w, int x, int y, int obj);
  // some cleaning
  ~render();
  // add a light to the rendering scene
  int add_light(const light& l);
  // precalc all (prepare structures for drawing and lock)
  bool begin();
  // (unlock)
  void end();
  // check if locked
  bool is_locked() const { return lock; }
  // set the camera for the scene
  // (before begin)
  void set_camera(const camera& c) { cam = c; }
  // set the vertex buffer for the future drawing
  // (before begin)
  void set_vertex_buffer(vertex_buffer* vb);
  // set the index buffer for the future drawing
  // (before begin)
  void set_index_buffer(index_buffer* ib);
  // draw the triangles between first and last
  // (between begin and end)
  bool draw_indexed_triangles(int first, int last);
  // clear the Z buffer
  void clear_buffer();
  // finalize the rendering
  void present();
};

}  // end namespace miniRT

#endif  // __MINIRT_RENDER_DEFINED__