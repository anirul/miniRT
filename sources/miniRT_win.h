/////////////////////////////////////////////////////////////////////
// miniRT window system (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_WIN_HEADER__
#define __MINIRT_WIN_HEADER__

namespace miniRT {

	class window; //< pre declaration

	// interface
	struct IWin {
		virtual void key_down(
			int key, 
			int x, int y, 
			window* w) = 0;
		virtual void key_up(
			int key, 
			int x, int y, 
			window* w) = 0;
		virtual void mouse(
			int button, 
			int x, int y, 
			window* w) = 0;
		virtual void motion(
			int x, int y, 
			window* w) = 0;
		virtual void update(window* w) = 0;
	};

	// class
	class window {
		IWin* win;
		bool mouse_captured, full, created;
		unsigned int dx, dy, mx, my;
	public :
		window() : 
			win(0), 
			mouse_captured(false), 
			dx(0), dy(0), 
			mx(0), my(0), 
			full(false), created(false) {}
		bool init(IWin* w);
		void end();
		bool trap_mouse(bool t);
		bool is_mouse_captured() const { return mouse_captured; }
		bool is_fullscreen() const { return full; }
		bool is_created() const { return created; }
		int get_tick() const;
		bool is_error() const;
		unsigned int get_dx() const { return dx; }
		unsigned int get_dy() const { return dy; }
		void set_title(const char* title, const char* caption);
		bool create(
			unsigned int x, unsigned int y, 
			unsigned int d = 32, bool f = false);
		void clear();
		bool run();
	};
}

#endif // __MINIRT_WIN_HEADER__