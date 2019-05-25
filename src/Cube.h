#include "SceneObject.h"
#include <glm/glm.hpp>
#include <vector>

using namespace std;

void drawCube(float x, float y, float z, float length, float width,
              float height, glm::vec3 color,
              vector<SceneObject *> *sceneObjects);
