#include "Cone.h"
#include <math.h>

float Cone::intersect(glm::vec3 posn, glm::vec3 dir) {
  // d is used to give (x_0 - x_c, y_0 - y_c, z_0 - z_c)
  glm::vec3 d = posn - center;

  float coeff = (radius * radius) / (height * height);
  float yLocalIntercept = center.y + height - posn.y;

  float a = (dir.x * dir.x) + (dir.z * dir.z) - (coeff * dir.y * dir.y);
  float b =
      2 * ((d.x * dir.x) + (d.z * dir.z) + (coeff * yLocalIntercept * dir.y));
  float c =
      (d.x * d.x) + (d.z * d.z) - (coeff * (yLocalIntercept * yLocalIntercept));

  float delta = (b * b) - 4 * a * c;

  if (fabs(delta) < 0.001 || delta < 0.0) {
    return -1.0;
  }

  float bottom = 2 * a;
  float sqrtDelta = sqrt(delta);

  float t1 = (-b - sqrtDelta) / bottom;
  float t2 = (-b + sqrtDelta) / bottom;

  // Prevents artifacts from appearing on the curve of the cone
  if (t1 < 0.01) {
    t1 = -1.0;
  }
  if (t2 < 0.01) {
    t2 = -1.0;
  }

  // Keeping both `t` values ensures that both sides of the cone is tested
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

glm::vec3 Cone::normal(glm::vec3 posn) {
  // d is used to give (x_0 - x_c, y_0 - y_c, z_0 - z_c)
  glm::vec3 d = posn - center;

  float r = sqrt(d.x * d.x + d.z * d.z);

  glm::vec3 n = glm::vec3(d.x, r * (radius / height), d.z);

  return glm::normalize(n);
}
