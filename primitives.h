/**
 * @file primitives.c
 *
 * This file contains structures and functions to define and manipulate
 * geometric primitives such as points, line segments, polygons, and screen-space
 * representations of these primitives for a software rendering engine.
 *
 * The structures defined in this file represent the level information about walls:
 * their position, size, shape, height, and distance from the camera to enable 3D transformation
 * and projection onto the screen space.
 *
 * reference: https://yuriygeorgiev.com/2022/08/17/polygon-based-software-rendering-engine/
 */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

// Maximum number of polygons
#define MAX_POLYGONS 10
// Maximum number of vertices per polygon
#define MAX_VERTICES 8 // NOTE: Affects level design

typedef struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

// sdl already has this defined as SDL_FPoint in SDL_rect.h, but
// we define our custom point type for educational purposes.
// technically, these are substitutable and this just exposes
// the interface. this doesn't really interest me though.
// what does interest me is a custom float type, like half or quarter precision.
// i wonder what it would be like to visually represent a vector of these types.
typedef struct Point2D { // Coordinates of the point
    float x;
    float y;
} point2d_t;

typedef struct Point3D {
    float x;
    float y;
    float z;
} point3d_t;

// not sure if this is valid or even a good idea
typedef union Point {
    struct Point2D dim2; // postfixed by num of dims
    struct Point3D dim3;
} point_t;

// n-dimensional vector space
typedef struct Vector {
    float* elements;
    size_t size;
};

// n-dimensional matrix space
typedef struct Matrix {
    struct Vector* vertices;
    size_t         n_rows;
    size_t         n_cols;
};

typedef struct LineSegment {
    point2d_t start; // Starting point of the line segment
    point2d_t end;   // Ending point of the line segment
} line_t;

typedef struct Polygon {
    point2d_t vertices[MAX_VERTICES]; // Array of vertices
    int       count;                  // Number of vertices in the polygon
    float     height;                 // Height of the polygon (for 3D effects)
    float     distance;               // Distance from the camera or reference point
} polygon_t;

// Projection of a quadrilateral onto a plane
typedef struct ScreenSpaceQuadrilateral {
    point2d_t vertices[4]; // A quadrilateral has 4 vertices
    float     depth;       // Depth of the plane from the camera
    int       id;          // Identifier for the plane, used to store polygon info
} screen_space_t;

#endif // PRIMITIVES_H
