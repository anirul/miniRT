/////////////////////////////////////////////////////////////////////
// miniRT main (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_MAIN_HEADER__
#define __MINIRT_MAIN_HEADER__

#include <SDL.h>
#include "miniRT_win.h"
#include "miniRT_new.h"
#include "miniRT_vertex.h"
#include "miniRT_math.h"
#include "miniRT_cam.h"
#include "miniRT_vertex_buffer.h"
#include "miniRT_index_buffer.h"
#include "miniRT_screen_buffer.h"
#include "miniRT_triangle.h"
#include "miniRT_light.h"
#include "miniRT_render.h"
// #include "miniRT_icosahedron.h"
#include "miniRT_teapot.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	int main(int ac, char** av);
#ifdef __cplusplus
}
#endif

using miniRT::window;

class rtwin : public miniRT::IWin {
	virtual void key_up(int key, int x, int y, window* w);
	virtual void key_down(int key, int x, int y, window* w);
	virtual void mouse(int button, int x, int y, window* w);
	virtual void motion(int x, int y, window* w);
	virtual void update(window* w);
};

#endif // __MINIRT_MAIN_HEADER__