# SDL on Linux - Build Process Documentation

## Introduction

This document provides detailed steps for building SDL projects on Linux using CMake. The build process includes setting up the environment, configuring the build system, and compiling the project.

## Prerequisites

Ensure you have the following installed on your system:
- GCC (GNU Compiler Collection)
- CMake
- SDL2 library

### Installing Prerequisites on Arch Linux

```sh
sudo pacman -S gcc cmake sdl2
```

## Project Structure

The project directory should have the following structure:

```
sdl-examples/
├── build
├── CMakeLists.txt
├── display.c
├── docs
├── drivers.c
├── line.c
├── precision.c
├── precision.h
├── README.md
└── simple.c
```

## CMake Configuration

Create a `CMakeLists.txt` file in the root of your project directory with the following content:

```cmake
# SDL for education and practice
cmake_minimum_required(VERSION 3.17)
project("sdl-examples" LANGUAGES CXX C)

# Set the C and C++ standard versions
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add SDL2 library for linking
add_link_options(-lSDL2)

# Add executable targets
add_executable(simple simple.c)
add_executable(line line.c)
add_executable(drivers drivers.c)
add_executable(display display.c)
```

## Building the Project

### Step 1: Navigate to the Repository

Navigate to the project directory:

```sh
cd sdl-examples
```

### Step 2: Configure the Build

Use CMake to configure the build system:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

Note that this creates the `build` directory if it does not already exist. It is only updated if the `CMakeLists.txt` file is modified in any way.

### Step 3: Build the Project

Compile the project using CMake:

```sh
cmake --build build -j 8
```

Note that we specify the build directory so that `cmake` can discover the generated directives.

### Step 4: Running the Executables

After the build process is complete, you can find the compiled executables in the `build` directory. Run them using the following commands:

```sh
./simple
./line
./drivers
./display
```

## Troubleshooting

### Missing SDL2 Library

If you encounter issues with finding or linking the SDL2 library, ensure that SDL2 is correctly installed on your system. Verify the installation paths:

```sh
whereis SDL2
```

Alternatively, `mlocate` can be used as a discovery tool:

```sh
sudo pacman -S mlocate
sudo updatedb
locate SDL2
```

Note that `locate` is much noisier than `whereis`.

Ensure the include path is `/usr/include/SDL2` and the library path is correctly linked.

### Common Errors

- **CMake Errors**: Ensure CMake is installed and properly configured.
- **Linker Errors**: Verify that the SDL2 library is linked correctly with `add_link_options(-lSDL2)`.

## Conclusion

This document outlines the steps necessary to build SDL projects on Linux using CMake. By following this guide, you can set up a robust build system that ensures your SDL applications compile and run correctly on Linux.
