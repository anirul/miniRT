/////////////////////////////////////////////////////////////////////
// miniRT window system
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include <SDL.h>
#include <SDL_events.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#ifdef WIN32
#	include <windows.h>
#endif
#ifdef __APPLE__
#	include <OpenGL/gl.h>
#else
#	include <GL/gl.h>
#endif
#include "miniRT_win.h"

namespace miniRT {
	
	bool window::init(IWin* w) {
		if (!w) 
			return false;
		else
			win = w;
		if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
		return true;
	}

	void window::end() {
		SDL_Quit();
	}

	bool window::trap_mouse(bool t) {
		if (t) {
#			ifndef _DEBUG
			SDL_ShowCursor(0);
			SDL_WM_GrabInput(SDL_GRAB_ON);
#			endif // _DEBUG
			mouse_captured = true;
		} else {
#			ifndef _DEBUG
			SDL_WM_GrabInput(SDL_GRAB_OFF);
			SDL_ShowCursor(1);
#			endif // _DEBUG
			mouse_captured = false;
		}
		return mouse_captured;
	}

	bool window::create
		(unsigned int x, unsigned int y, unsigned int d, bool f) {
		dx = x;
		dy = y;
		full = f;

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		bool succeed = true;
		if (full) {
			if (SDL_SetVideoMode(
				x, y, d,	SDL_OPENGL | SDL_FULLSCREEN) == 0)
				succeed = false;
		} else { 
			if (SDL_SetVideoMode(x, y, d,	SDL_OPENGL) == 0)
				succeed = false;
		}
		glShadeModel(GL_FLAT);
		glPixelStoref(GL_UNPACK_ALIGNMENT, 4);
		// Setup our viewport.
		glViewport(0, 0, x, y);
		if (succeed) {
			created = true;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, double(dx), double(dy), 0, -10, 10);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			return true;
		} else {
			return false;
		}
	}

	void window::clear() {
		glClearColor(0,0,1,0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}
	
	void window::set_title(const char* title, const char* caption) {
		SDL_WM_SetCaption(title, caption);
	}

	bool window::run() {
		bool loop = true;
		while (loop) {
			SDL_Event event;
			memset(&event, 0, sizeof(SDL_Event));
			mx = 0;
			my = 0;
			while(SDL_PollEvent(&event)) {
				switch(event.type) {
				case SDL_KEYDOWN :
					if (win) win->key_down(
						event.key.keysym.sym, mx, my, this);
					break;
				case SDL_KEYUP :
					if (win) win->key_up(
						event.key.keysym.sym, mx, my, this);
					break;
				case SDL_MOUSEBUTTONDOWN :
					if (win) win->mouse(
						event.button.button, mx, my, this);
					break;
				case SDL_MOUSEMOTION :
					if (mouse_captured) {
						mx = event.motion.xrel;
						my = event.motion.yrel;	
					} else {
						mx = event.motion.x;
						my = event.motion.y;
					}
					if (win) win->motion(mx, my, this);
					break;
				case SDL_QUIT :
					end();
					return true;
				}
			}
			if (win) win->update(this);
			// flip
			SDL_GL_SwapBuffers();
		}
		return true;
	}

	int window::get_tick() const {
		return SDL_GetTicks();
	}

	bool window::is_error() const {
#ifdef _DEBUG
		switch (glGetError()) {
			case GL_NO_ERROR :
				return false;
			case GL_INVALID_VALUE :
				printf("GL : Invalid Value\n");
				return true;
			case GL_INVALID_ENUM :
				printf("GL : Invalid Enum\n");
				return true;
			case GL_INVALID_OPERATION :
				printf("GL : Invalid Operation\n");
				return true;
			case GL_STACK_OVERFLOW :
				printf("GL : Stack Overflow\n");
				return true;
			case GL_STACK_UNDERFLOW :
				printf("GL : Stack Underflow\n");
				return true;
			case GL_OUT_OF_MEMORY :
				printf("GL : Out of Memory\n");
				return true;
			default :
				printf("GL : Unknown Error\n");
				return true;
		}
#else
		if (glGetError() != GL_NO_ERROR)
			return true;
		else
			return false;
#endif
	}

}
