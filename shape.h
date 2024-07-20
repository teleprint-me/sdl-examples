/**
 * @file shape.h
 *
 * This file contains structures and functions to define and manipulate
 * geometric primitives such as points, line segments, polygons, screen-space
 * representations of these primitives for a software rendering engine, and
 * basic tensor operations.
 *
 * The structures defined in this file represent the level information about walls:
 * their position, size, shape, height, and distance from the camera to enable 3D transformation
 * and projection onto the screen space.
 *
 * Reference: https://yuriygeorgiev.com/2022/08/17/polygon-based-software-rendering-engine/
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "vector.h"

#include <stddef.h> // For size_t
#include <stdint.h> // For uint8_t

/**
 * @brief Enumeration representing 2D or 3D coordinates for semantic legibility
 */
typedef enum {
    X = 0, /**< The horizontal axis */
    Y = 1, /**< The vertical axis */
    Z = 2  /**< The depth axis */
} coordinate_t;

/**
 * @brief Represents the rank (dimensions) of data structures
 */
typedef enum {
    SCALAR,  /**< Value; a point */
    VECTOR,  /**< N dimensions; a sequence of points */
    MATRIX,  /**< N by M dimensions; a grid of points */
    TENSOR,  /**< N by M by O dimensions; a "cube", "volume", or "space" of points */
    MAX_RANK /**< Maximum supported dimensions */
} rank_t;

/**
 * @brief Represents a point in an N-dimensional space
 */
typedef struct {
    size_t dimensions;  /**< Number of dimensions */
    float* coordinates; /**< Array of coordinate values */
} float_point_t;

/**
 * @brief Represents a line segment with a start and end point
 */
typedef struct {
    float_point_t* start; /**< Start point of the line (run) */
    float_point_t* end;   /**< End point of the line (rise) */
} line_segment_t;

// Polygon structure
typedef struct {
    vector_t* vertices;       // Array of vertices
    size_t    vectices_max;   // Max number of vertices; Note this affects level design
    size_t    vertices_count; // Number of vertices within the polygon
    float     height;         // Height of the polygon (for 3D effects)
    float     distance;       // Distance from the camera or reference point
} polygon_t;

// Screen-space quadrilateral structure
typedef struct {
    vector_t* vertices;       // Array of vertices
    size_t    vectices_max;   // Max number of vertices
    size_t    vertices_count; // Current number of vertices
    float     depth;          // Depth of the plane from the camera
    int       id;             // Identifier for the plane, used to store polygon info
} screen_space_t;

// Function prototypes

// Line segment operations
line_segment_t* create_line(size_t cols);
void            free_line(line_segment_t* line);

// Polygon operations
polygon_t* create_polygon(size_t max_vertices);
void       free_polygon(polygon_t* polygon);

// Screen-space quadrilateral operations
screen_space_t* create_screen_space(size_t max_vertices);
void            free_screen_space(screen_space_t* screen);

#endif // SHAPE_H
