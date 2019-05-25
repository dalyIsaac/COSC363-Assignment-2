#include "Cube.h"
#include "Plane.h"

using namespace std;

// ASCII art courtesy of https://1j01.github.io/ascii-hypercube/
// H + + + + + + + + + + + G
// +\                      +\
// + \                     + l
// +  \                    +  e
// +   \                   +   n
// +    \                  +    g
// +     \                 +     t
// +      \                +      h
// +       \               +       \
// +        D + + + + + + +++ + + + C
// +        +              +        +
// +        +              +        +
// E + + + +++ + + + + + + F        h
//  \       +               \       e
//   \      +           *    \      i
//    \     +       (x, y, z) \     g
//     \    +                  \    h
//      \   +                   \   t
//       \  +                    \  +
//        \ +                     \ +
//         \+                      \+
//          A + + + + width + + + + B

// TODO: ANTICLOCKWISE

void drawCube(float x, float y, float z, float width, float length,
              float height, glm::vec3 color,
              vector<SceneObject *> *sceneObjects) {
  float halfLength = length / 2;
  float halfWidth = width / 2;
  float halfHeight = height / 2;

  glm::vec3 A = glm::vec3(x + halfLength, y - halfWidth, z - halfHeight);
  glm::vec3 B = glm::vec3(x + halfLength, y + halfWidth, z - halfHeight);

  glm::vec3 C = glm::vec3(x + halfLength, y + halfWidth, z + halfHeight);
  glm::vec3 D = glm::vec3(x + halfLength, y - halfWidth, z + halfHeight);

  glm::vec3 E = glm::vec3(x - halfLength, y - halfWidth, z - halfHeight);
  glm::vec3 F = glm::vec3(x - halfLength, y + halfWidth, z - halfHeight);

  glm::vec3 G = glm::vec3(x - halfLength, y + halfWidth, z + halfHeight);
  glm::vec3 H = glm::vec3(x - halfLength, y - halfWidth, z + halfHeight);

  Plane *front = new Plane(A, B, C, D, color);
  sceneObjects->push_back(front);
  Plane *back = new Plane(E, F, G, H, color);
  sceneObjects->push_back(back);

  Plane *left = new Plane(A, D, H, E, color);
  sceneObjects->push_back(left);
  Plane *right = new Plane(B, F, G, C, color);
  sceneObjects->push_back(right);

  Plane *top = new Plane(D, C, G, H, color);
  sceneObjects->push_back(top);
  Plane *bottom = new Plane(A, E, F, B, color);
  sceneObjects->push_back(bottom);

  //   glm::vec3 A = glm::vec3(x, y, z);
  //   glm::vec3 B = glm::vec3(x + length, y, z);
  //   glm::vec3 C = glm::vec3(x + length, y + height, z);
  //   glm::vec3 D = glm::vec3(x, y + height, z);
  //   glm::vec3 E = glm::vec3(x + length, y, z - width);
  //   glm::vec3 F = glm::vec3(x + length, y + height, z - width);
  //   glm::vec3 G = glm::vec3(x, y + height, z - width);
  //   glm::vec3 H = glm::vec3(x, y, z - width);

  //   Plane *plane1 = new Plane(A, B, C, D, color);

  //   Plane *plane2 = new Plane(B, E, F, C, color);

  //   Plane *plane3 = new Plane(E, H, G, F, color);

  //   Plane *plane4 = new Plane(D, G, H, A, color);

  //   Plane *plane5 = new Plane(D, C, F, G, color);

  //   Plane *plane6 = new Plane(H, E, B, A, color);

  //   sceneObjects->push_back(plane1);
  //   sceneObjects->push_back(plane2);
  //   sceneObjects->push_back(plane3);
  //   sceneObjects->push_back(plane4);
  //   sceneObjects->push_back(plane5);
  //   sceneObjects->push_back(plane6);
}
