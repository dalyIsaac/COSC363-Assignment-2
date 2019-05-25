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

/**
 * @brief Draws a cube, with the center being at (x, y, z), with the given
 * width, length, height, and color. The cube is pushed onto the given scene
 * objects vector.
 *
 * @param x x-coordinate of the center of the cube.
 * @param y y-coordinate of the center of the cube.
 * @param z z-coordinate of the center of the cube.
 * @param length The length of the cube (x-direction).
 * @param width The width of the cube (y-direction).
 * @param height The height of the cube (z-direction).
 * @param color The color of the cube to draw.
 * @param sceneObjects The vector of scene objects the cube should be pushed
 * onto.
 */
void drawCube(float x, float y, float z, float length, float width,
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
}
