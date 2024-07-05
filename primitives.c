/**
 * @file primitives.c
 *
 * This file contains structures and functions to define and manipulate
 * geometric primitives such as points, line segments, polygons, and screen-space
 * representations of these primitives for a software rendering engine inspired by DOOM.
 *
 * The structures defined in this file represent the level information about walls:
 * their position, size, shape, height, and distance from camera to enable 3D transformation
 * and projection onto the screen space.
 *
 * reference: https://yuriygeorgiev.com/2022/08/17/polygon-based-software-rendering-engine/
 */

// Maximum number of shapes
#define MAX_POLYGONS 10
// Maximum number edges
#define MAX_VERTICES 8

typedef struct Point2D {
    float x, y;
} point2d_t;

typedef struct LineSegment {
    point2d_t start, end;
} line_t;

typedef struct Polygon {
    point2d_t vertices[MAX_VERTICES];
    int       count;    // number of vertices
    float     height;   // shape?
    float     distance; // distance from what?
} polygon_t;

typedef struct PlaneProjection {
    // a plane has 4 vertices since it’s a quadrilateral
    point2d_t vertices[4];
    float     depth;
    int       polygon_id;
} plane_t;
