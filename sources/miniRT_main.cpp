////////////////////////////////////////////////////////////////
// MiniRT
////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
////////////////////////////////////////////////////////////////

#include "miniRT_main.h"

#include <glm/gtx/transform.hpp>

using namespace miniRT;

static int dx = 640;
static int dy = 480;
const float MOVE_SPEED = 0.05f;
const float ROTATE_FACT = 0.02f;
glm::vec3 delta;

render* ren = 0;
camera* cam = 0;
teapot* tea = 0;
icosahedron* ico = 0;

void rtwin::key_up(int key, int x, int y, window* w) {
  switch (key) {
    case 27:
      if (w->is_mouse_captured()) {
        w->trap_mouse(false);
      } else {
        w->end();
        exit(0);
      }
    case 'w':
    case 's':
      if (w->is_mouse_captured()) {
        delta[2] = 0;
      }
      return;
    case 'a':
    case 'd':
      if (w->is_mouse_captured()) {
        delta[0] = 0;
      }
      return;
  }
}

void rtwin::key_down(int key, int x, int y, window* w) {
  switch (key) {
    case 'w':
      if (w->is_mouse_captured()) {
        delta[2] = MOVE_SPEED;
      }
      return;
    case 's':
      if (w->is_mouse_captured()) {
        delta[2] = -MOVE_SPEED;
      }
      return;
    case 'd':
      if (w->is_mouse_captured()) {
        delta[0] = MOVE_SPEED;
      }
      return;
    case 'a':
      if (w->is_mouse_captured()) {
        delta[0] = -MOVE_SPEED;
      }
      return;
  }
}

void rtwin::mouse(int button, int x, int y, window* w) {
  if (button) {
    if (!w->is_mouse_captured()) {
      w->trap_mouse(true);
#ifdef _DEBUG
      printf("mouse trapped.\n");
#endif  // _DEBUG
    }
  }
}

void rtwin::motion(int x, int y, window* w) {
  assert(w);
  if (w->is_mouse_captured()) {
    // rotation
    camera old = *cam;
    glm::mat3 mat_rot_up = glm::rotate(ROTATE_FACT * -x, old.get_up());
    cam->set_right(old.get_right() * mat_rot_up);
    cam->set_to(old.get_to() * mat_rot_up);
    cam->set_up(old.get_up() * mat_rot_up);
    cam->set_right(glm::normalize(cam->get_right()));
    cam->set_to(glm::normalize(cam->get_to()));
    cam->set_right(glm::normalize(cam->get_right()));
    old = *cam;
    glm::mat3 mat_rot_right = glm::rotate(ROTATE_FACT * -y, old.get_right());
    cam->set_right(old.get_right() * mat_rot_right);
    cam->set_to(old.get_to() * mat_rot_right);
    cam->set_up(old.get_up() * mat_rot_right);
    cam->set_right(glm::normalize(cam->get_right()));
    cam->set_to(glm::normalize(cam->get_to()));
    cam->set_right(glm::normalize(cam->get_right()));
    cam->fix_perp();
  }
  ren->set_camera(*cam);
}

void rtwin::update(window* w) {
  static int first = w->get_tick();
  static float fps = 0.0f;
  static int count = 1;
#ifdef _DEBUG
  w->clear();
#endif  // _DEBUG
        // RENDER
  ren->clear_buffer();
  ren->begin();
  ren->draw_indexed_triangles(0, 20);
  ren->present();
  ren->end();
  if ((w->get_tick() - first) > 1000) {
    int deltai = w->get_tick() - first;
    first = w->get_tick();
    fps = (float)count / (float)deltai * 1000.0f;
    count = 1;
  } else {
    count++;
  }
  char temp[512];
  memset(temp, 0, 512);
  sprintf_s(temp, 128, "miniRT : FPS %f : ", (float)fps);
  w->set_title(temp, "miniRT");
  cam->set_pos(cam->get_pos() + (cam->get_right() * delta[0]));
  cam->set_pos(cam->get_pos() + (cam->get_to() * delta[2]));
  ren->set_camera(*cam);
}

int main(int ac, char** av) {
  light lt;
  ico = new icosahedron();
  tea = new teapot();
  glm::vec3 up(0.0f, 0.80f, 0.60f);
  glm::vec3 pos(0.0f, 1.10f, -1.75f);
  glm::vec3 ltpos(3.0f, 3.0f, -3.0f);
  glm::vec3 to(0.0f, -0.60f, 0.80f);
  lt.position() = ltpos;
  cam = new camera(up, to, pos);
  rtwin* main_win = new rtwin();
  window* cwin = new window();
  ren = new render(cwin, dx, dy, 10000);
  ren->set_index_buffer(ico->get_ib());
  ren->set_vertex_buffer(ico->get_vb());
  cwin->init(main_win);
#ifdef _DEBUG
  cwin->create(dx, dy);
#else
  cwin->create(dx, dy, 32, false);
#endif  // _DEBUG
  ren->set_camera(*cam);
  ren->add_light(lt);
  cwin->run();
  return 0;
}
