#ifndef H_CONE
#define H_CONE

#include "SceneObject.h"
#include <glm/glm.hpp>
#include <math.h>

/**
 * @brief Defines a Cone as a subclass of `SceneObject`.
 *
 */
class Cone : public SceneObject {
private:
  /**
   * @brief The center of the Cone is at the bottom (in the y-direction).
   *
   */
  glm::vec3 center;
  float radius;
  float height;

public:
  Cone() : center(glm::vec3(0)), radius(1), height(1) { color = glm::vec3(1); }

  Cone(glm::vec3 c, float r, float h, glm::vec3 col)
      : center(c), radius(r), height(h) {
    color = col;
  }

  float intersect(glm::vec3 posn, glm::vec3 dir);

  glm::vec3 normal(glm::vec3 p);
};

#endif //! H_CONE
