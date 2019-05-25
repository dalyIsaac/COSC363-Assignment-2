#include "Cylinder.h"
#include <math.h>

float Cylinder::intersect(glm::vec3 posn, glm::vec3 dir) {
  // d is used to give (x_0 - x_c, y_0 - y_c, z_0 - z_c)
  glm::vec3 d = posn - center;

  float a = (dir.x * dir.x) + (dir.z * dir.z);
  float b = 2 * (dir.x * d.x + dir.z * d.z);
  float c = (d.x * d.x) + (d.z * d.z) - (radius * radius);

  float delta = (b * b) - 4 * a * c;

  if (fabs(delta) < 0.001 || delta < 0.0) {
    return -1.0;
  }

  float bottom = 2 * a;
  float sqrtDelta = sqrt(delta);

  float t1 = (-b - sqrtDelta) / bottom;
  float t2 = (-b + sqrtDelta) / bottom;

  // Prevents artifacts from appearing on the curve of the cylinder
  if (t1 < 0.01) {
    t1 = -1.0;
  }
  if (t2 < 0.01) {
    t2 = -1.0;
  }

  // Keeping both `t` values ensures that both sides of the cylinder is tested
  float tHigh, tLow;
  if (t1 > t2) {
    tHigh = t1;
    tLow = t2;
  } else {
    tHigh = t2;
    tLow = t1;
  }

  float yIntersection = posn.y + tLow * dir.y;
  if (yIntersection >= center.y && yIntersection <= center.y + height) {
    return tLow;
  }

  yIntersection = posn.y + tHigh * dir.y;
  if (yIntersection >= center.y && yIntersection <= center.y + height) {
    return tHigh;
  }

  return -1.0;
}

glm::vec3 Cylinder::normal(glm::vec3 posn) {
  // d is used to give (x_0 - x_c, y_0 - y_c, z_0 - z_c)
  glm::vec3 d = posn - center;

  float x = d.x / radius;
  float y = 0;
  float z = d.z / radius;
  return glm::vec3(x, y, z);
}
