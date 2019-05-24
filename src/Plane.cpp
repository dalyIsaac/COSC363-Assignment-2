/**
 * @file Plane.cpp
 * @brief Contains the `Plane` class. This is a subclass of Object, and hence
 * implements the methods `intersect` and `normal`.
 */

#include "Plane.h"
#include <math.h>

/**
 * @brief Checks if a point `pt` is inside the current polygon.
 *
 * @param pt The point to be checked.
 * @return true The point is inside the current polygon.
 * @return false The point is not inside the current polygon.
 */
bool Plane::isInside(glm::vec3 pt) {
  glm::vec3 uA = b - a;
  glm::vec3 uB = c - b;
  glm::vec3 uC = d - c;
  glm::vec3 uD = a - d;

  glm::vec3 vA = pt - a;
  glm::vec3 vB = pt - b;
  glm::vec3 vC = pt - c;
  glm::vec3 vD = pt - d;

  glm::vec3 normal = Plane::normal(pt);

  bool cond1 = glm::dot(glm::cross(uA, vA), normal) >= 0.0;
  bool cond2 = glm::dot(glm::cross(uB, vB), normal) >= 0.0;
  bool cond3 = glm::dot(glm::cross(uC, vC), normal) >= 0.0;
  bool cond4 = glm::dot(glm::cross(uD, vD), normal) >= 0.0;

  if (cond1 && cond2 && cond3 && cond4) {
    return true;
  }
  return false;
}

/**
 * @brief Checks if a ray intersects the plane.
 *
 * @param posn The source point of the ray.
 * @param dir The direction of the ray.
 * @return float
 */
float Plane::intersect(glm::vec3 posn, glm::vec3 dir) {
  glm::vec3 n = normal(posn);
  glm::vec3 vdif = a - posn;
  float vdotn = glm::dot(dir, n);
  if (fabs(vdotn) < 1.e-4)
    return -1;
  float t = glm::dot(vdif, n) / vdotn;
  if (fabs(t) < 0.0001)
    return -1;
  glm::vec3 q = posn + dir * t;
  if (isInside(q))
    return t;
  else
    return -1;
}

/**
 * @brief Normalizes a vector a given point.
 *
 * @param pt The point to normalize.
 * @return glm::vec3 Returns the unit normal vector at a given point.
 */
glm::vec3 Plane::normal(glm::vec3 pt) {
  glm::vec3 n = glm::vec3(0);
  n = glm::normalize(glm::cross(b - a, d - a));
  return n;
}
