/**
 * @file primitives.h
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

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stddef.h> // For size_t
#include <stdint.h> // For uint8_t

// Constants
#define MAX_POLYGONS 10
#define MAX_VERTICES 8 // NOTE: Affects level design

// 2D and 3D coordinates; for semantic legibility
#define X            0
#define Y            1
#define Z            2

typedef enum {
    SCALAR,   // value; a point
    VECTOR,   // n dimensions; a sequence of points
    MATRIX,   // n by m dimensions; a grid of points
    TENSOR,   // n by m by o dimensions; a "cube", "volume", or "space" of points
    MAX_RANK, // max supported dimensions
} rank_t;

// Color structure
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

// N-dimensional vector structure
typedef struct {
    float* elements; // Dynamic array of elements
    size_t size;     // Number of elements in the vector
} vector_t;

// N-dimensional matrix structure
typedef struct {
    float** elements; // 2D array representing the matrix elements
    size_t  n_rows;   // Number of rows
    size_t  n_cols;   // Number of columns
} matrix_t;

// N-dimensional tensor structure
typedef struct {
    float*  elements;   // Flat array representing the tensor elements
    size_t* dimensions; // Array representing the size of each dimension
    rank_t  rank;       // Number of dimensions
} tensor_t;

// Line segment structure
typedef struct {
    vector_t* start; // Starting point of the line segment
    vector_t* end;   // Ending point of the line segment
} line_t;

// Polygon structure
typedef struct {
    vector_t* vertices;     // Array of vertices
    size_t    max_vertices; // Max number of vertices; Note this affects level design
    size_t    count;        // Number of vertices within the polygon
    float     height;       // Height of the polygon (for 3D effects)
    float     distance;     // Distance from the camera or reference point
} polygon_t;

// Screen-space quadrilateral structure
typedef struct {
    vector_t* vertices; // Array of vertices
    size_t    max;      // Max number of vertices
    size_t    count;    // Current number of vertices
    float     depth;    // Depth of the plane from the camera
    int       id;       // Identifier for the plane, used to store polygon info
} screen_space_t;

// Function prototypes

// Vector operations
vector_t* create_vector(size_t size);
void      free_vector(vector_t* vector);

// Matrix operations
matrix_t* create_matrix(size_t n_rows, size_t n_cols);
void      free_matrix(matrix_t* matrix);

// Tensor operations
tensor_t* create_tensor(size_t* dimensions, rank_t rank);
void      free_tensor(tensor_t* tensor);

// Line segment operations
line_t* create_line(size_t size);
void    free_line(line_t* line);

// Polygon operations
polygon_t* create_polygon(size_t max_vertices);
void       free_polygon(polygon_t* polygon);

// Screen-space quadrilateral operations
screen_space_t* create_screen_space(size_t max_vertices);
void            free_screen_space(screen_space_t* quad);

#endif // PRIMITIVES_H
