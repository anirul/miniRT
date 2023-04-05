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
  glm::vec4 spec;
  glm::vec4 diff;
  glm::vec4 amb;
  glm::vec3 pos;
  int lh;

 public:
  light()
      : pos(glm::vec3(0.0f, 0.0f, 0.0f)),
        spec(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)),
        diff(glm::vec4(0.5f, 0.5f, 0.5f, 0.0f)),
        amb(glm::vec4(0.2f, 0.2f, 0.2f, 0.0f)),
        lh(-1) {}
  light(glm::vec3 p,  // position
        glm::vec4 s,  // specular
        glm::vec4 d,  // diffuse
        glm::vec4 a)  // ambiant
      : pos(p), spec(s), diff(d), amb(a), lh(-1) {}
  int last_hit() const { return lh; }
  glm::vec4 ambiant() const { return amb; }
  glm::vec4 diffuse() const { return diff; }
  glm::vec4 specular() const { return spec; }
  glm::vec3 position() const { return pos; }
  glm::vec4 ambiant() { return amb; }
  glm::vec4 diffuse() { return diff; }
  glm::vec4 specular() { return spec; }
  glm::vec3 position() { return pos; }
  int& last_hit() { return lh; }
};

}  // end of namespace miniRT

#endif  // __MINIRT_LIGHT_HEADER__