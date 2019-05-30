mkdir -p build_sh

g++ -c -o build_sh/Cone.o src/Cone.cpp 
g++ -c -o build_sh/Cube.o src/Cube.cpp 
g++ -c -o build_sh/Cylinder.o src/Cylinder.cpp 
g++ -c -o build_sh/Plane.o src/Plane.cpp 
g++ -c -o build_sh/Ray.o src/Ray.cpp 
g++ -c -o build_sh/RayTracer.o src/RayTracer.cpp 
g++ -c -o build_sh/SceneObject.o src/SceneObject.cpp 
g++ -c -o build_sh/Sphere.o src/Sphere.cpp 
g++ -c -o build_sh/Tetrahedron.o src/Tetrahedron.cpp 
g++ -c -o build_sh/TextureBMP.o src/TextureBMP.cpp 
g++ -c -o build_sh/Triangle.o src/Triangle.cpp 

g++ -o program.out build_sh/Cone.o build_sh/Cube.o build_sh/Cylinder.o build_sh/Plane.o build_sh/Ray.o build_sh/RayTracer.o build_sh/SceneObject.o build_sh/Sphere.o build_sh/Tetrahedron.o build_sh/TextureBMP.o build_sh/Triangle.o -lm -lGL -lGLU -lglut

./program.out