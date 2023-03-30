/////////////////////////////////////////////////////////////////////
// miniRT light (header)
/////////////////////////////////////////////////////////////////////
// author	: Dubouchet Frederic
// e-mail	: angel@calodox.org
/////////////////////////////////////////////////////////////////////

#ifndef __MINIRT_LIGHT_HEADER__
#define __MINIRT_LIGHT_HEADER__

namespace miniRT {

class light {
  vector4 spec;
  vector4 diff;
  vector4 amb;
  vector3 pos;
  int lh;

 public:
  light()
      : pos(vector3(0.0f, 0.0f, 0.0f)),
        spec(vector4(1.0f, 1.0f, 1.0f, 0.0f)),
        diff(vector4(0.5f, 0.5f, 0.5f, 0.0f)),
        amb(vector4(0.2f, 0.2f, 0.2f, 0.0f)),
        lh(-1) {}
  light(const vector3& p,  // position
        const vector4& s,  // specular
        const vector4& d,  // diffuse
        const vector4& a)  // ambiant
      : pos(p), spec(s), diff(d), amb(a), lh(-1) {}
  const int last_hit() const { return lh; }
  const vector4& ambiant() const { return amb; }
  const vector4& diffuse() const { return diff; }
  const vector4& specular() const { return spec; }
  const vector3& position() const { return pos; }
  vector4& ambiant() { return amb; }
  vector4& diffuse() { return diff; }
  vector4& specular() { return spec; }
  vector3& position() { return pos; }
  int& last_hit() { return lh; }
};

}  // end of namespace miniRT

#endif  // __MINIRT_LIGHT_HEADER__