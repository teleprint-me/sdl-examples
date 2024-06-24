# SDL for education and practice
cmake_minimum_required(VERSION 3.17)
project("sdl-examples" LANGUAGES CXX C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

add_link_options(-lSDL2)
add_executable(simple simple.c)
