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

# Simple
add_executable(simple examples/windows/simple.c)

# Drivers
add_executable(driver_environ examples/drivers/environ.c)
add_executable(driver_display examples/drivers/display.c)
add_executable(driver_render examples/drivers/render.c)

# Lines
add_executable(line_simple examples/lines/line.c)
add_executable(line_dda examples/lines/dda.c)

# Vectors
add_executable(vector_simple vector.c examples/vectors/simple.c)
add_executable(vector_vertex vector.c examples/vectors/vertex.c)

# Matrices
add_executable(matrix_simple matrix.c examples/matrices/simple.c)
