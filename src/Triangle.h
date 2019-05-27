#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "SceneObject.h"
#include <glm/glm.hpp>

class Triangle : public SceneObject {
private:
  glm::vec3 a, b, c;

public:
  Triangle(void);

  Triangle(glm::vec3 pa, glm::vec3 pb, glm::vec3 pc, glm::vec3 col)
      : a(pa), b(pb), c(pc) {
    color = col;
  };

  bool isInside(glm::vec3 pt);

  float intersect(glm::vec3 posn, glm::vec3 dir);

  glm::vec3 normal(glm::vec3 pt);
};

#endif //! H_TRIANGLE
