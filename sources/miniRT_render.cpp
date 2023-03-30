/////////////////////////////////////////////////////////////////////
// miniRT Render
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_render.h"

#include <assert.h>

#include "miniRT_cam.h"
#include "miniRT_index_buffer.h"
#include "miniRT_light.h"
#include "miniRT_math.h"
#include "miniRT_new.h"
#include "miniRT_screen_buffer.h"
#include "miniRT_triangle.h"
#include "miniRT_vertex.h"
#include "miniRT_vertex_buffer.h"
#include "miniRT_win.h"
#ifdef _DEBUG
#include <stdio.h>
#endif
#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
//#define WITHOUT_SHADOW 1

namespace miniRT {

render::render(window* w, int x, int y, int obj) {
  assert(w);
  assert(x);
  assert(y);
  assert(obj);

  bound_tri = new vector4[obj];
  pzsb = new screen_buffer<float>(x, y);
  pisb = new screen_buffer<unsigned int>(x, y);
  pib = 0;
  pvb = 0;
  pl = 0;
  lcount = 0;
  // check allocation
  assert(bound_tri);
  assert(pzsb);
  assert(pisb);
  // clean it
  pw = w;
  dx = x;
  dy = y;
  maxobj = obj;
  lock = false;
}

render::~render() {
  assert(!lock);

  // free the memory allocated at constructor
  if (bound_tri) delete[] bound_tri;
  if (tri) delete tri;
  if (pzsb) delete pzsb;
  if (pisb) delete pisb;
  if (pl) delete[] pl;
}

bool render::begin() {
  assert(!lock);
  assert(pvb);
  assert(pib);
  assert(pzsb);

  float width = 2.0f * tanf(cam.get_fov());
  float height = width * ((float)dy / (float)dx);

  top_left = cam.get_to();
  top_left += (cam.get_up() * (height * 0.5f));
  top_left -= (cam.get_right() * (width * 0.5f));
  right_step = cam.get_right() * height * (1.0f / (float)dy);
  up_step = cam.get_up() * height * (1.0f / (float)dy);

  vector3 start;
  vector3 pos = cam.get_pos();
  int nb_tri = pib->size() / 3;
  for (int i = 0, j = 0; i < nb_tri; ++i, j += 3) {
    bool found = false;
    bound_tri[i] = vector4(-1.0f);
    start = cam.get_to() - cam.get_right() * (width * 0.5f);
    for (int x = 0; x < dx; ++x) {
      vector3 x_scan_line = start + right_step * (float)x;
      vector3 norm = x_scan_line % cam.get_up();
      norm.Normalize();
      if (tri->intersect_plane(pib->get(j), pib->get(j + 1), pib->get(j + 2),
                               pos, norm)) {
        if (!found) {
          found = true;
          bound_tri[i].x = (float)x;
        }
      } else {
        if (found) {
          found = false;
          bound_tri[i].z = (float)x;
        }
      }
      if ((x == dx - 1) && found) {
        bound_tri[i].z = (float)x;
      }
    }
  }

  for (int i = 0, j = 0; i < nb_tri; ++i, j += 3) {
    bool found = false;
    start = cam.get_to() + cam.get_up() * (height * 0.5f);
    for (int y = 0; y < dy; ++y) {
      vector3 y_scan_line = start - up_step * (float)y;
      vector3 norm = y_scan_line % cam.get_right();
      norm.Normalize();
      if (tri->intersect_plane(pib->get(j), pib->get(j + 1), pib->get(j + 2),
                               pos, norm)) {
        if (!found) {
          found = true;
          bound_tri[i].y = (float)y;
        }
      } else {
        if (found) {
          found = false;
          bound_tri[i].w = (float)y;
        }
      }
      if ((y == dy - 1) && found) {
        bound_tri[i].w = (float)y;
      }
    }
  }

  lock = true;
  return lock;
}

void render::end() { lock = false; }

void render::set_vertex_buffer(vertex_buffer* vb) {
  assert(!lock);
  assert(vb);
  pvb = vb;
  tri = new triangle(pvb);
  assert(tri);
}

void render::set_index_buffer(index_buffer* ib) {
  assert(!lock);
  assert(ib);
  assert(!(ib->size() % 3));
  pib = ib;
}

bool render::draw_indexed_triangles(int first, int last) {
  assert(lock);
  assert(first >= 0);
  assert(last >= 0);
  assert(pib);
  assert(pzsb);
  assert(pisb);

  int nbobj = pib->size() / 3;

  assert(first < nbobj);
  assert(last < nbobj);
  assert(first <= last);

  const vector4 nullvec = vector4(-1.0);
  vector3 pos = cam.get_pos();
  vector4 tuvi;
  vector4 pvd;

  for (int obji = first; obji <= last; ++obji) {
    vector4 bound = bound_tri[obji];
    for (int y = (int)bound.y; y < (int)bound.w; ++y) {
      vector3 yscanline = top_left - up_step * (float)y;
      vector3 dir;
      yscanline += right_step * bound_tri[obji].x;
      bool found = true;
      int lastx = (int)bound.x;
      for (int x = lastx; x < (int)bound.z; ++x) {
        dir = yscanline;
        dir.Normalize();
        int index = obji * 3;
        tri->intersect_det(pib->get(index), pib->get(index + 1),
                           pib->get(index + 2), pos, dir, &pvd);
        if (pvd.w > minirt_epsilon) {
          if (tri->intersect_barycentric(pib->get(index), pib->get(index + 1),
                                         pib->get(index + 2), pvd, pos, dir,
                                         &tuvi)) {
            if (!found)
              if (x > lastx) lastx = x;
            found = true;
            if ((*pzsb)(x, y) > tuvi.x) {
              (*pzsb)(x, y) = tuvi.x;
              (*pisb)(x, y) = phong(tuvi, dir, obji);
            }
          } else {
            if (found) {
              yscanline += right_step;
              continue;
            }
          }
        }
        yscanline += right_step;
      }
    }
  }
  return true;
}

void render::clear_buffer() {
  unsigned int back = 0x00000000;
  for (int i = 0; i < lcount; ++i) {
    back += clampRGBA(pl[i].ambiant());
  }
  pzsb->clear(minirt_huge);
  pisb->clear(back);
}

void render::present() {
  assert(lock);
  assert(pisb);

  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(dx, dy, GL_RGBA, GL_UNSIGNED_BYTE, pisb->pv);
  pw->is_error();
  glFlush();
}

int render::add_light(const light& l) {
  if (lcount) {
    light* temp = new light[lcount + 1];
    memcpy(temp, pl, sizeof(light) * lcount);
    delete[] pl;
    pl = temp;
  } else {
    pl = new light[1];
  }
  pl[lcount] = l;
  return ++lcount;
}

unsigned int render::clampRGBA(const vector4& v) {
  int ir = (int)(v.x * 256.0f);
  if (ir < 0) ir = 0;
  if (ir > 255) ir = 255;

  int ig = (int)(v.y * 256.0f);
  if (ig < 0) ig = 0;
  if (ig > 255) ig = 255;

  int ib = (int)(v.z * 256.0f);
  if (ib < 0) ib = 0;
  if (ib > 255) ib = 255;

  int ia = (int)(v.w * 256.0f);
  if (ia < 0) ia = 0;
  if (ia > 255) ia = 255;

  return (ib << 16) + (ig << 8) + ir;
}

unsigned int render::phong(const vector4& tuvi, const vector3& dir, int i) {
  assert(tri);
  assert(pib);
  assert(i >= 0);
  assert(i < (pib->size() / 3));
  assert(lcount > 0);

  vector4 col(0.0f, 0.0f, 0.0f, 0.0f);
  int v0, v1, v2;
  v0 = pib->get(i * 3);
  v1 = pib->get(i * 3 + 1);
  v2 = pib->get(i * 3 + 2);
  vector3 normal = tri->intersect_normal(v0, v1, v2, tuvi);
  vector3 hitpoint = cam.get_pos() + dir * tuvi.x;
  vector4 pvd;

  // search light
  for (int j = 0; j < lcount; ++j) {
    vector3 incoming_light_normal = (pl[j].position() - hitpoint).Normalize();
    bool visible = true;
    float n_cross_inlt = normal * incoming_light_normal;
    // if the angle is too sharp or behind target
    if (n_cross_inlt < minirt_epsilon) visible = false;
#ifndef WITHOUT_SHADOW
    if (visible) {
      int last_occulted = pl[j].last_hit();
      if (last_occulted != i && last_occulted != -1) {
        int u0, u1, u2;
        u0 = pib->get(last_occulted * 3);
        u1 = pib->get(last_occulted * 3 + 1);
        u2 = pib->get(last_occulted * 3 + 2);
        if (tri->shadow_hit(u0, u1, u2, hitpoint, incoming_light_normal,
                            minirt_epsilon,
                            sqrt((hitpoint - pl[j].position()) *
                                 (hitpoint - pl[j].position())) -
                                minirt_epsilon)) {
          visible = false;
        }
      }
      if (visible) {
        for (int k = 0; k < (pib->size() / 3); ++k) {
          if (k != last_occulted && k != i) {
            int u0, u1, u2;
            u0 = pib->get(k * 3);
            u1 = pib->get(k * 3 + 1);
            u2 = pib->get(k * 3 + 2);
            vector4 pvd;
            if (tri->shadow_hit(u0, u1, u2, hitpoint, incoming_light_normal,
                                minirt_epsilon,
                                1000.0f))  // TODO (faster than sqrt)
            {
              visible = false;
              pl[j].last_hit() = k;
              break;
            }
          }
        }
      }
    }
#endif  // WITHOUT_SHADOW
    if (visible) {
      // should be in material (structure)
      if (n_cross_inlt > 0.90f) {
        col += pl[j].ambiant();
        col += pl[j].diffuse() * n_cross_inlt;
        col |= tri->intersect_col(v0, v1, v2, tuvi);
        col += ((n_cross_inlt - 0.90f) * 10.0f) * pl[j].specular();
      } else {
        col += pl[j].ambiant();
        col += pl[j].diffuse() * n_cross_inlt;
        col |= tri->intersect_col(v0, v1, v2, tuvi);
      }
    } else {
      col += pl[j].ambiant();
      col |= tri->intersect_col(v0, v1, v2, tuvi);
    }
  }
  return clampRGBA(col);
}

}  // namespace miniRT