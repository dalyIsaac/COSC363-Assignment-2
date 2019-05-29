#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Ray.h"
#include "SceneObject.h"
#include "Sphere.h"
#include "Tetrahedron.h"
#include "TextureBMP.h"
#include <GL/glut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
using namespace std;

// width of the image plane in world units
const float WIDTH = 20.0;

// height of the image place in world unites
const float HEIGHT = 20.0;

// the distance of the image plane from the camera/origin
const float EDIST = 40.0;

// the number of cells along x and y directions
const int NUMDIV = 500;

// the number of levels of recursion
const int MAX_STEPS = 5;

// boundary values of the image plane
const float XMIN = -WIDTH * 0.5;
const float XMAX = WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX = HEIGHT * 0.5;

const glm::vec3 floorA = glm::vec3(-20.0, -20, -40);
const glm::vec3 floorB = glm::vec3(20.0, -20, -40);
const glm::vec3 floorC = glm::vec3(20.0, -20, -200);
const glm::vec3 floorD = glm::vec3(-20.0, -20, -200);

const float pixel = (XMAX - XMIN) / 500;
const float pixelQuarter = pixel / 4;

const float TRANSPARENCY = 0.6;
const float ETA = 1.0 / 1.5;

const glm::vec3 earthCenter = glm::vec3(5.0, 5.0, -30.0);

/**
 * @brief BMP texture for the floor plane.
 *
 */
TextureBMP earthTexture;

// A global list containing pointers to objects in the scene
vector<SceneObject *> sceneObjects;

/**
 * @brief Computes the color value obtained by tracing a ray and finding its
 * closest point of intersection with objects in the scene. If `xindex` is `-1`,
 * then the background color is returned. Otherwise, it returns the object's
 * color.
 *
 * @param ray
 * @param step
 * @return glm::vec3
 */
glm::vec3 trace(Ray ray, int step) {
  glm::vec3 backgroundCol(0);
  glm::vec3 primaryLight(-10, 40, -3);
  glm::vec3 secondaryLight(40, 40, -100);

  // Ambient color of light
  glm::vec3 ambientCol(0.2);

  // Compute the closest point of intersection of objects with the ray
  ray.closestPt(sceneObjects);

  // If there is no intersection return background colour
  if (ray.xindex == -1) {
    return backgroundCol;
  }

  // else return object's colour
  glm::vec3 materialCol = sceneObjects[ray.xindex]->getColor();

  // normal vector on the sphere at the point of intersection
  glm::vec3 normalVector = sceneObjects[ray.xindex]->normal(ray.xpt);

  // vector from the point of intersection towards the light source
  glm::vec3 primaryLightVector = primaryLight - ray.xpt;
  primaryLightVector = glm::normalize(primaryLightVector);
  float primaryLDotN = glm::dot(primaryLightVector, normalVector);

  glm::vec3 secondaryLightVector = secondaryLight - ray.xpt;
  secondaryLightVector = glm::normalize(secondaryLightVector);
  float secondaryLDotN = glm::dot(secondaryLightVector, normalVector);

  // Specular reflections

  glm::vec3 viewVector = -ray.dir;

  // first param: incident light's direction (unit vector from light source to
  // the point of intersection)
  glm::vec3 primaryReflVector = glm::reflect(-primaryLightVector, normalVector);
  glm::vec3 secondaryReflVector =
      glm::reflect(-secondaryLightVector, normalVector);

  float primaryRDotV = glm::dot(primaryReflVector, normalVector);
  float primarySpecularTerm =
      primaryRDotV < 0.0 ? 0.0 : pow(primaryRDotV, 20.0);

  float secondaryRDotV = glm::dot(secondaryReflVector, normalVector);
  float secondarySpecularTerm =
      secondaryRDotV < 0.0 ? 0.0 : pow(secondaryRDotV, 20.0);

  // Shadows
  Ray primaryShadow(ray.xpt, primaryLightVector);
  primaryShadow.closestPt(sceneObjects);
  float primaryLightDist = glm::length(secondaryLight);

  Ray secondaryShadow(ray.xpt, secondaryLightVector);
  secondaryShadow.closestPt(sceneObjects);
  float secondaryLightDist = glm::length(secondaryLight);

  glm::vec3 colorSum(0);

  // Earth sphere texture
  if (ray.xindex == 16) {
    glm::vec3 d = glm::normalize(ray.xpt - earthCenter);
    // differs from wikipedia formula, so that the northern hemisphere is on the
    // top
    float u = 0.5 - atan2(d.z, d.x) / (2 * M_PI);
    float v = 0.5 + asinf(d.y) / M_PI;
    materialCol = earthTexture.getColorAt(u, v);
  }

  // Floor texture
  if (ray.xindex == 3) {
    int floorX = (int)((ray.xpt.x + 20) / 5) % 2;
    int floorZ = (int)(ray.xpt.z / 5) % 2;

    if ((floorX + floorZ) % 2 == 0) {
      materialCol = glm::vec3(0.050, 0.184, 0.611);
    } else {
      materialCol = glm::vec3(0.827, 0.011, 0.011);
    }
  }

  if (ray.xindex == 17) {
    int value = (int)(ray.xpt.x + ray.xpt.z) % 2;
    if (value == 0) {
      materialCol = glm::vec3(0.901, 0.941, 0.156);
    } else {
      materialCol = glm::vec3(0.156, 0.941, 0.403);
    }
  }

  if (primaryLDotN <= 0 ||
      (primaryShadow.xindex > -1 && primaryShadow.xdist < primaryLightDist)) {
    colorSum += ambientCol * materialCol;
  } else {
    colorSum += ambientCol * materialCol + primaryLDotN * materialCol +
                primarySpecularTerm;
  }

  if (secondaryLDotN <= 0 || (secondaryShadow.xindex > -1 &&
                              secondaryShadow.xdist < secondaryLightDist)) {
    colorSum += ambientCol * materialCol;
  } else {
    colorSum += ambientCol * materialCol + secondaryLDotN * materialCol +
                secondarySpecularTerm;
  }

  // Reflection
  if (ray.xindex == 0 && step < MAX_STEPS) {
    // the following does not need to be normalized as it will have a unit
    // length, since both the incident rays direction and the normal vector
    // are unit vectors
    glm::vec3 reflectedDir = glm::reflect(ray.dir, normalVector);

    // Defines the reflected ray using its source (the point of
    // intersection  on the object), and the direction
    Ray reflectedRay(ray.xpt, reflectedDir);

    // Recursive
    glm::vec3 reflectedCol = trace(reflectedRay, step + 1);

    // Coefficient of reflection is specified as 0.8
    colorSum = colorSum + (0.8f * reflectedCol);
  }

  // Refraction
  if (ray.xindex == 2 && step < MAX_STEPS) {
    glm::vec3 g = glm::refract(ray.dir, normalVector, ETA);
    Ray refractRay(ray.xpt, g);
    refractRay.closestPt(sceneObjects);
    if (refractRay.xindex == -1) {
      return backgroundCol;
    }
    glm::vec3 m = sceneObjects[refractRay.xindex]->normal(refractRay.xpt);
    glm::vec3 h = glm::refract(g, -m, 1.0f / ETA);

    Ray refractOutRay(refractRay.xpt, h);
    refractOutRay.closestPt(sceneObjects);
    if (refractOutRay.xindex == -1) {
      return backgroundCol;
    }
    glm::vec3 refractColor = trace(refractOutRay, step + 1);
    colorSum = colorSum * TRANSPARENCY + refractColor * (1 - TRANSPARENCY);
    return colorSum;
  }

  // Transparency
  if (ray.xindex == 5 && step < MAX_STEPS) {
    Ray transparentRay(ray.xpt, ray.dir);
    glm::vec3 transparentColor = trace(transparentRay, step + 1);
    colorSum = colorSum * TRANSPARENCY + transparentColor * (1 - TRANSPARENCY);
  }

  return colorSum;
}

/**
 * @brief Adds anti-aliasing functionality to the ray tracer.
 *
 * @param eye
 * @param x
 * @param y
 * @return glm::vec3
 */
glm::vec3 antiAliase(glm::vec3 eye, float x, float y) {
  glm::vec3 color = glm::vec3(0);

  Ray bottomLeft =
      Ray(eye, glm::vec3(x - pixelQuarter, y - pixelQuarter, -EDIST));
  bottomLeft.normalize();
  color += trace(bottomLeft, 1);

  Ray bottomRight =
      Ray(eye, glm::vec3(x + pixelQuarter, y - pixelQuarter, -EDIST));
  bottomRight.normalize();
  color += trace(bottomRight, 1);

  Ray topLeft = Ray(eye, glm::vec3(x - pixelQuarter, y + pixelQuarter, -EDIST));
  topLeft.normalize();
  color += trace(topLeft, 1);

  Ray topRight =
      Ray(eye, glm::vec3(x + pixelQuarter, y + pixelQuarter, -EDIST));
  topRight.normalize();
  color += trace(topRight, 1);

  return color * glm::vec3(0.25);
}

/**
 * @brief The main display module. In a ray tracing application, it just
 * displays the ray traced image by drawing each cell as a quad.
 *
 */
void display() {
  float xp, yp;                         // grid point
  float cellX = (XMAX - XMIN) / NUMDIV; // cell width
  float cellY = (YMAX - YMIN) / NUMDIV; // cell height

  // A ray is generated from the origin through the center of each cell
  // The eye position (source of primary rays) is the origin
  glm::vec3 eye(0.0, 0.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // draws each cell as a quad
  // Each cell is a quad.
  glBegin(GL_QUADS);

  // For each grid point xp, yp
  for (int i = 0; i < NUMDIV; i++) {
    xp = XMIN + i * cellX;
    for (int j = 0; j < NUMDIV; j++) {
      yp = YMIN + j * cellY;

      // direction of the primary ray
      glm::vec3 dir(xp + 0.5 * cellX, yp + 0.5 * cellY, -EDIST);

      // Create a ray originating from the camera in the direction 'dir'
      Ray ray = Ray(eye, dir);

      // Normalize the direction of the ray to a unit vector
      ray.normalize();

      // Trace the primary ray and get the colour value
      glm::vec3 col = antiAliase(eye, xp, yp);
      // glm::vec3 col = trace(ray, 1);

      glColor3f(col.r, col.g, col.b);
      // Draw each cell with its color value
      glVertex2f(xp, yp);
      glVertex2f(xp + cellX, yp);
      glVertex2f(xp + cellX, yp + cellY);
      glVertex2f(xp, yp + cellY);
    }
  }

  glEnd();
  glFlush();
}

/**
 * @brief This function initializes the scene.
 * Specifically, it creates scene objects (spheres, planes, cones, cylinders
 * etc.) and adds them to the list of scene objects. It also initializes the
 * OpenGL othographic projection matrix for drawing the ray traced image.
 */
void initialize() {
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
  glClearColor(0, 0, 0, 1);

  // index 0
  Sphere *sphere1 =
      new Sphere(glm::vec3(-5.0, -5.0, -150.0), 15.0, glm::vec3(0, 0, 1));
  sceneObjects.push_back(sphere1);

  // index 1
  Sphere *sphere2 =
      new Sphere(glm::vec3(10.0, 5.0, -130.0), 4.0, glm::vec3(1, 1, 0));
  sceneObjects.push_back(sphere2);

  // index 2
  Sphere *sphere3 =
      new Sphere(glm::vec3(-10.0, -8.0, -60.0), 5.0, glm::vec3(0, 1, 0));
  sceneObjects.push_back(sphere3);

  // index 3
  Plane *plane =
      new Plane(glm::vec3(-20.0, -20, -40), glm::vec3(20.0, -20, -40),
                glm::vec3(20.0, -20, -200), glm::vec3(-20.0, -20, -200),
                glm::vec3(1.0, 1.0, 1.0));
  sceneObjects.push_back(plane);

  // index 4
  Cylinder *cylinder = new Cylinder(glm::vec3(8, -15, -100), 2, 8.0,
                                    glm::vec3(0.27, 0.85, 0.91));
  sceneObjects.push_back(cylinder);

  // index 5
  Cone *cone =
      new Cone(glm::vec3(2, -15, -100), 2, 8.0, glm::vec3(0.341, 0.756, 0.490));
  sceneObjects.push_back(cone);

  // index 6 - 11 (inclusive)
  drawCube(-8, -10, -90, 5, 5, 5, glm::vec3(0.15, 0.77, 0.4), &sceneObjects);

  // index 12 - 15 (inclusive)
  drawTetrahedron(3, -15, -65, glm::vec3(0.996, 0.184, 0.184), &sceneObjects);

  // index 16
  Sphere *sphere4 = new Sphere(earthCenter, 2.0, glm::vec3(0, 1, 0));
  sceneObjects.push_back(sphere4);

  // index 17
  Sphere *sphere5 = new Sphere(glm::vec3(8.0, -8.0, -60.0), 2.0,
                               glm::vec3(0.901, 0.941, 0.156));
  sceneObjects.push_back(sphere5);

  earthTexture = TextureBMP("textures/earth.bmp");
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(20, 20);
  glutCreateWindow("Raytracer");

  glutDisplayFunc(display);
  initialize();

  glutMainLoop();
  return 0;
}
