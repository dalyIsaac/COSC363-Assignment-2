# COSC363-Assignment-2

GitHub: https://github.com/dalyIsaac/OpenGL-raytracer

This project was for the second assignment for COSC363 Computer Graphics, at the University of Canterbury, in Semester 1 2019.

The specifications for the assignment can be found in [`./specifications.pdf`](./specifications.pdf).

The report for the assignment can be found in [`./report.pdf`](./report.pdf).

## Building

This guide assumes that `g++` is present on the machine, and that the computer is running Linux (Ubuntu 18.04). This may or may not work for other distributions or operating systems.

### Using Visual Studio Code

The following assumes that CMake is present on the machine.

1. Install the recommended extensions
2. If CMake is not running:
   1. Select a kit (optional), by running from the command palette `CMake: Select a Kit`
   2. Select a variant (optional), by running from the command palette `CMake: Set the current build variant`
   3. Run `CMake: Configure` from the command palette.
3. Build, by running from the command palette `CMake: Build`.
4. To run the project, either run:
   - `CMake: Execute the current target without a debugger`
   - `CMake: Debug Target`
  
### Building from the terminal

From the project root, run:

``` console
user@domain:~/path/to/project/COSC363-Assignment-2$ ./build.sh
```

## Screenshot

![Picture of the scene](screenshot.png)
