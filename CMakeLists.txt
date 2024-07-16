# SDL for education and practice
cmake_minimum_required(VERSION 3.17)
project("sdl-examples" LANGUAGES C)

# Set the C and C++ standard versions
set(CMAKE_C_STANDARD 17)

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add SDL2 library for linking
add_link_options(-lm -lSDL2)

# Add executable targets
add_executable(simple simple.c)
add_executable(line line.c)
add_executable(drivers drivers.c)
add_executable(display display.c)
add_executable(dda dda.c)
add_executable(simple_vector primitives.c simple_vector.c)
