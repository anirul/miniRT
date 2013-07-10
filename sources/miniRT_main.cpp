////////////////////////////////////////////////////////////////
// MiniRT
////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
////////////////////////////////////////////////////////////////

#include "miniRT_main.h"

using namespace miniRT;

static int dx = 320;
static int dy = 200;
const float MOVE_SPEED = 0.05f;
const float ROTATE_FACT = 0.02f;
vector3 delta;

render* ren = 0;
camera* cam = 0;
teapot* ico = 0;

void rtwin::key_up(int key, int x, int y, window* w) {
	switch (key) {
		case 27 :
			if(w->is_mouse_captured()) {
				w->trap_mouse(false);
			} else {
				w->end();
				exit(0);
			}
		case 'w' :
		case 's' :
			if (w->is_mouse_captured()) {
				delta[2] = 0;
			}
			return;
		case 'a' :
		case 'd' :
			if (w->is_mouse_captured()) {
				delta[0] = 0;
			}
			return;
	}
}

void rtwin::key_down(int key, int x, int y, window* w) {
	switch (key) {
		case 'w' :
			if (w->is_mouse_captured()) {
				delta[2] = MOVE_SPEED;
			}
			return;
		case 's' :
			if (w->is_mouse_captured()) {
				delta[2] = - MOVE_SPEED;
			}
			return;
		case 'd' :
			if (w->is_mouse_captured()) {
				delta[0] = MOVE_SPEED;
			}
			return;
		case 'a' :
			if (w->is_mouse_captured()) {
				delta[0] = - MOVE_SPEED;
			}
			return;
	}
}

void rtwin::mouse(int button, int x, int y, window* w) {
	if (button) {
		if (!w->is_mouse_captured()) {
			w->trap_mouse(true);
#			ifdef _DEBUG
				printf("mouse trapped.\n");
#			endif // _DEBUG
		}
	}
}

void rtwin::motion(int x, int y, window* w) {
	assert(w);
	if (w->is_mouse_captured()) {
		// rotation
		camera old = *cam;
		cam->set_right(
			vector3(
				(old.get_right() * AA2M3(old.get_up(), 
					ROTATE_FACT * -x)).vec));
		cam->set_to(
			vector3(
				(old.get_to() * AA2M3(old.get_up(), 
					ROTATE_FACT * -x)).vec));
		cam->set_up(
			vector3(
				(old.get_up() * AA2M3(old.get_up(), 
					ROTATE_FACT * -x)).vec));
		cam->set_right(cam->get_right().Normalize());
		cam->set_to(cam->get_to().Normalize());
		cam->set_right(cam->get_right().Normalize());
		old = *cam;
		cam->set_right(
			vector3(
				(old.get_right() * AA2M3(old.get_right(), 
					ROTATE_FACT * -y)).vec));
		cam->set_to(
			vector3(
				(old.get_to() * AA2M3(old.get_right(), 
					ROTATE_FACT * -y)).vec));
		cam->set_up(
			vector3(
				(old.get_up() * AA2M3(old.get_right(), 
					ROTATE_FACT * -y)).vec));
		cam->set_right(cam->get_right().Normalize());
		cam->set_to(cam->get_to().Normalize());
		cam->set_right(cam->get_right().Normalize());
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
#endif // _DEBUG
	// RENDER
	ren->clear_buffer();
	ren->begin();
	ren->draw_indexed_triangles(0, 2255);
	ren->present();
	ren->end();	
	if ((w->get_tick() - first) > 1000 ) {
		int deltai = w->get_tick() - first;
		first = w->get_tick();
		fps = (float)count / (float)deltai * 1000.0f;
		count = 1;
	} else {
		count++;
	}
	char temp[512];
	memset(temp, 0, 512);
	sprintf(temp, "miniRT : FPS %f : ", (float)fps);
	w->set_title(temp, "miniRT");
	cam->set_pos(cam->get_pos() + 
		(cam->get_right() * delta[0]));
	cam->set_pos(cam->get_pos() + 
		(cam->get_to() * delta[2]));
	ren->set_camera(*cam);
}

int main(int ac, char** av) {
	light lt;
	ico = new teapot();
	vector3 up(0.0f, 0.80f, 0.60f);
	vector3 pos(0.0f, 1.10f, -1.75f);
	vector3 ltpos(3.0f, 3.0f, -3.0f);
	vector3 to(0.0f, -0.60f, 0.80f);
	lt.position() = ltpos;
	cam = new camera(up, to, pos);
	rtwin* main_win = new rtwin();
	window* cwin = new window();
	ren = new render(cwin, dx, dy, 10000);
	ren->set_index_buffer(ico->get_ib());
	ren->set_vertex_buffer(ico->get_vb());
	cwin->init(main_win);
#	ifdef _DEBUG
		cwin->create(dx, dy);
#	else
		cwin->create(dx, dy, 32, false);
#	endif // _DEBUG
	ren->set_camera(*cam);
	ren->add_light(lt);
	cwin->run();
	return 0;
}