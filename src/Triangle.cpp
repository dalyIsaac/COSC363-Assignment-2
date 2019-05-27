#include "Triangle.h"
#include <math.h>

bool Triangle::isInside(glm::vec3 pt) {
  glm::vec3 uA = b - a;
  glm::vec3 uB = c - b;
  glm::vec3 uC = a - c;

  glm::vec3 vA = pt - a;
  glm::vec3 vB = pt - b;
  glm::vec3 vC = pt - c;

  glm::vec3 n = Triangle::normal(pt);

  bool cond1 = glm::dot(glm::cross(uA, vA), n) >= 0.0;
  bool cond2 = glm::dot(glm::cross(uB, vB), n) >= 0.0;
  bool cond3 = glm::dot(glm::cross(uC, vC), n) >= 0.0;

  if (cond1 && cond2 && cond3) {
    return true;
  }
  return false;
}

float Triangle::intersect(glm::vec3 posn, glm::vec3 dir) {
  glm::vec3 n = normal(posn);
  glm::vec3 vdif = a - posn;
  float vdotn = glm::dot(dir, n);
  if (fabs(vdotn) < 1.e-4) {
    return -1;
  }
  float t = glm::dot(vdif, n) / vdotn;
  if (fabs(t) < 0.0001) {
    return -1;
  }
  glm::vec3 q = posn + dir * t;
  if (isInside(q)) {
    return t;
  } else {
    return -1;
  }
}

glm::vec3 Triangle::normal(glm::vec3 pt) {
  glm::vec3 n = glm::normalize(glm::cross(b - a, c - a));
  return n;
}
