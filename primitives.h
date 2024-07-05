/**
 * @file primitives.c
 *
 * This file contains structures and functions to define and manipulate
 * geometric primitives such as points, line segments, polygons, and screen-space
 * representations of these primitives for a software rendering engine inspired by DOOM.
 *
 * The structures defined in this file represent the level information about walls:
 * their position, size, shape, height, and distance from the camera to enable 3D transformation
 * and projection onto the screen space.
 *
 * reference: https://yuriygeorgiev.com/2022/08/17/polygon-based-software-rendering-engine/
 */

// Maximum number of polygons
#define MAX_POLYGONS 10
// Maximum number of vertices per polygon
#define MAX_VERTICES 8 // NOTE: Affects level design

typedef struct Point2D {
    float x, y; // Coordinates of the point
} point2d_t;

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

typedef struct PlaneProjection {
    point2d_t vertices[4]; // A quadrilateral has 4 vertices
    float     depth;       // Depth of the plane from the camera
    int       id;          // Identifier for the plane, used to store polygon info
} plane_t;
