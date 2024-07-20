/**
 * Copyright © 2024 Austin Berrio
 *
 * @file rank.h
 *
 * @brief The Rank API provides an easy-to-use interface to work with various ranked data
 * structures, such as scalars, vectors, matrices, and tensors in pure C.
 *
 * This header file defines basic types for handling different ranks of data and offers a simple
 * way to create and manipulate them without relying on external libraries.
 */

#ifndef RANK_H
#define RANK_H

#include <stdlib.h>

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
} point_t;

/**
 * @brief Represents a line segment with a start and end point
 */
typedef struct {
    point_t start; /**< Start point of the line (run) */
    point_t end;   /**< End point of the line (rise) */
} line_segment_t;

#endif // RANK_H
