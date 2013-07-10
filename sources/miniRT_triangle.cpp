/////////////////////////////////////////////////////////////////////
// miniRT triangle
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#include "miniRT_math.h"
#include "miniRT_vertex.h"
#include "miniRT_new.h"
#include "miniRT_vertex_buffer.h"
#include "miniRT_triangle.h"

namespace miniRT {

	triangle::triangle(vertex_buffer* vb) {
		assert(vb);
		pvb = vb;
	}

	bool triangle::intersect_plane(
		const int v0, 
		const int v1, 
		const int v2, 
		const vector3& p,
		const vector3& n) 
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());

		if ((((vector3)pvb->get_pos(v0) - p) * n) < -epsilon) {
			if ((((vector3)pvb->get_pos(v1) - p) * n) > epsilon) 
				return true;
			if ((((vector3)pvb->get_pos(v2) - p) * n) > epsilon) 
				return true;
		} else {
			if ((((vector3)pvb->get_pos(v1) - p) * n) < -epsilon) 
				return true;
			if ((((vector3)pvb->get_pos(v2) - p) * n) < -epsilon) 
				return true;
		}
		return false;
	}

	void triangle::intersect_det(
		const int v0,
		const int v1,
		const int v2,
		const vector3& o,
		const vector3& d,
		vector4* pvd)
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());
		assert(pvd);
		
		vector3 edge1, edge2, pvec;
		edge1 = (vector3)pvb->get_pos(v1) - 
			(vector3)pvb->get_pos(v0);
		edge2 = (vector3)pvb->get_pos(v2) - 
			(vector3)pvb->get_pos(v0);
		pvec = d % edge2; // cross product
		float det = edge1 * pvec;
		*pvd = pvec.vec;
		pvd->w = det;
	}

	bool triangle::intersect_ray(
		const int v0,
		const int v1,
		const int v2,
		const vector4& pvd,
		const vector3& o,
		const vector3& d,
		const vector3& m) 
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());

		vector3 tvec, qvec, pv;
		float u, v, det;
		pv = pvd.vec;
		det = pvd.w;

		if (det > epsilon) return false;
		tvec = o - vector3(pvb->get_pos(v0));
		u = tvec * pv;
		if (u < -epsilon || u > det) return false;
		qvec = tvec % ((vector3)pvb->get_pos(v1) - 
			(vector3)pvb->get_pos(v0));
		v = d * qvec;
		if (v < -epsilon || u + v > det) return false;
		// check position
		return true;
	}

	bool triangle::shadow_hit(
		const int v0,
		const int v1,
		const int v2,
		const vector3& o,
		const vector3& d,
		const float tmin,
		const float tmax) 
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());

		vector3 p0 = (vector3)pvb->get_pos(v0);
		vector3 p1 = (vector3)pvb->get_pos(v1);
		vector3 p2 = (vector3)pvb->get_pos(v2);

		vector3 ABC = p0 - p1;
		vector3 DEF = p0 - p2;
		vector3 GHI = d;
		vector3 JKL = p0 - o;

		vector3 smat = DEF % GHI;

		float denom = ABC * smat;
		float inv_denom = 1 / denom;
		float beta = (JKL * smat) * inv_denom;

		if (beta <= 0.0f || beta >= 1.0f) 
			return false;

		smat = ABC % JKL;

		float gamma = (GHI * smat) * inv_denom;
		if (gamma <= 0.0f || beta + gamma >= 1.0f) 
			return false;

		float tval = -(DEF * smat) * inv_denom;

		return (tval >= tmin && tval <= tmax);
	}
	
	bool triangle::intersect_barycentric(
		const int v0,
		const int v1,
		const int v2,
		const vector4& pvd,
		const vector3& o,
		const vector3& d,
		vector4* tuv) 
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());

		vector3 tvec, qvec, pv;
		float inv_det, det;
		pv = pvd.vec;
		det = pvd.w;
		assert(det > epsilon);

		tvec = o - vector3(pvb->get_pos(v0));
		tuv->y = tvec * pv;
		if (tuv->y < -epsilon || tuv->y > det) 
			return false;
		qvec = tvec % ((vector3)pvb->get_pos(v1) - 
			(vector3)pvb->get_pos(v0));
		tuv->z = d * qvec;
		if (tuv->z < -epsilon || tuv->z + tuv->y > det) 
			return false;
		tuv->x = ((vector3)pvb->get_pos(v2) - 
			(vector3)pvb->get_pos(v0)) * qvec;
		inv_det = 1.0f / det;
		tuv->x *= inv_det;
		tuv->y *= inv_det;
		tuv->z *= inv_det;
		return tuv->x > 0;
	}

	vector3 triangle::intersect_point(
		const vector4& tuv,
		const vector3& o,
		const vector3& d)
	{
		return o + d * tuv.x;
	}

	vector3 triangle::intersect_normal(
		const int v0,
		const int v1,
		const int v2,
		const vector4& tuv)
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());
	
		return	
			((vector3)pvb->get_normal(v0) * 
			(1.0f - (tuv.y + tuv.z))) + 
			((vector3)pvb->get_normal(v1) * 
			tuv.y) +
			((vector3)pvb->get_normal(v2) * 
			tuv.z);
	}

	vector2 triangle::intersect_texmap(
		const int v0,
		const int v1,
		const int v2,
		const vector4& tuv)
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());
	
		// scaled texture coordinates
		float stc[6];
		// CHECKME
		stc[0] = (1.0f - tuv.y - tuv.z) * 
			pvb->get_UV(v0).m128_f32[0];
		stc[1] = (1.0f - tuv.y - tuv.z) * 
			pvb->get_UV(v0).m128_f32[0];
		stc[2] = tuv.y * pvb->get_UV(v1).m128_f32[0];
		stc[3] = tuv.y * pvb->get_UV(v1).m128_f32[1];
		stc[4] = tuv.z * pvb->get_UV(v2).m128_f32[0];
		stc[5] = tuv.z * pvb->get_UV(v2).m128_f32[1];
		vector2 uv;
		uv.x = stc[0] + stc[2] + stc[4];
		uv.y = stc[1] + stc[3] + stc[5];
		return uv;
	}

	vector4 triangle::intersect_col(
		const int v0,
		const int v1,
		const int v2,
		const vector4& tuv) 
	{
		assert(pvb);
		assert(v0 >= 0);
		assert(v0 < pvb->size());
		assert(v1 >= 0);
		assert(v1 < pvb->size());
		assert(v2 >= 0);
		assert(v2 < pvb->size());

		return	
			((vector4)pvb->get_color(v0) * 
			(1.0f - (tuv.y + tuv.z))) + 
			((vector4)pvb->get_color(v1) * 
			tuv.y) +
			((vector4)pvb->get_color(v2) * 
			tuv.z);
	}

}
