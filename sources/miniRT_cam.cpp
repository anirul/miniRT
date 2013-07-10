/////////////////////////////////////////////////////////////////////
// miniRT camera (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_cam.h"

namespace miniRT {

	camera::camera() {
		pos = vector3(0.0f, 0.0f, 0.0f);
		up = vector3(0.0f, 1.0f, 0.0f);
		to = vector3(0.0f, 0.0f, 1.0f); 
		right = vector3(1.0f, 0.0f, 0.0f);
		fix_perp();
		fov = (float)M_PI_4;
	}

	camera::camera(
			const vector3& vup,
			const vector3& vto,
			const vector3& vpos, 
			const float ffov) {
		up = vup;
		to = vto;
		pos = vpos;
		fov = ffov;
		fix_perp();
	}

	camera& camera::set_up(const vector3& in) {
		up = in;
		return *this;
	}

	camera& camera::set_to(const vector3& in) {
		to = in;
		return *this;
	}

	camera& camera::set_pos(const vector3& in) {
		pos = in;
		return *this;
	}

	camera& camera::set_right(const vector3& in) {
		right = in;
		return *this;
	}

	camera& camera::set_fov(const float in) {
		fov = in;
		return *this;
	}

	camera& camera::fix_perp() {
		right = up % to;
		up = to % right;
		to.Normalize();
		right.Normalize();
		up.Normalize();
		return *this;
	}
	
	camera& camera::operator()(
			const vector3& vup, 
			const vector3& vto, 
			const vector3& vpos, 
			const float ffov) {
		up = vup;
		to = vto;
		pos = vpos;
		fix_perp();
		fov = ffov;
		return *this;
	}

	camera& camera::look_at(const vector3& target, const float roll) {
		// rotate
		up[0] = sinf(roll);
		up[1] = cosf(roll);
		up[2] = 0.0f;
		// change target
		to = target - pos;
		fix_perp();
		return *this;
	}

}