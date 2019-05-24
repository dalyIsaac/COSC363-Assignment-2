cmake_minimum_required(VERSION 2.8)

project(COSC363-Assignment-2)

file(GLOB_RECURSE sources src/*.cpp src/*.h)
add_executable(main.out ${sources})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )

target_link_libraries( main.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} )
