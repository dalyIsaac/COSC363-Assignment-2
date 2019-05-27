#include "Tetrahedron.h"
#include "Triangle.h"

using namespace std;

// ASCII art courtesy of
// https://www.asciiart.eu/buildings-and-places/monuments/pyramids
//                D
//               / \\
//              /   \ \
//             /     \  \
//            /       \   \
//           /         \    \
//          /           \     \
//         /             \      \
//        /               \       \
//       /                 \        \
//      /                   \         \
//     /                     \          C
//    /                       \,       /
//   /               ,         \     /
//  /       ,                   \  /
// A------------center-----------B
// The z-axis lies through C, such that the point which intersects the line AB
// has equal length on each side.
// The center of the triangle lies at `center`

/**
 * @brief Draws a tetrahedron, with the center being at (x, y, z), with the
 * given width, length, height, and color. The tetrahedron is pushed onto the
 * given scene objects vector.
 *
 * @param x x-coordinate of the center of the tetrahedron.
 * @param y y-coordinate of the center of the tetrahedron.
 * @param z z-coordinate of the center of the tetrahedron.
 * @param color The color of the tetrahedron to draw.
 * @param sceneObjects The vector of scene objects the tetrahedron should be
 * pushed onto.
 */
void drawTetrahedron(float x, float y, float z, glm::vec3 color,
                     vector<SceneObject *> *sceneObjects) {
  glm::vec3 A = glm::vec3(x - 3, y, z);
  glm::vec3 B = glm::vec3(x + 3, y, z);
  glm::vec3 C = glm::vec3(x, y, z + 6);
  glm::vec3 D = glm::vec3(x, y + 6, z + 3);

  Triangle *front = new Triangle(A, B, D, color);
  sceneObjects->push_back(front);

  Triangle *left = new Triangle(C, A, D, color);
  sceneObjects->push_back(left);

  Triangle *right = new Triangle(B, C, D, color);
  sceneObjects->push_back(right);

  Triangle *bottom = new Triangle(A, B, C, color);
  sceneObjects->push_back(bottom);
}
