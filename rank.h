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
    VECTOR,  /**< w dimensions; a sequence of points */
    MATRIX,  /**< w x h dimensions; a grid of points */
    TENSOR,  /**< w x h x d dimensions; a "cube", "volume", or "space" of points */
    MAX_RANK /**< Maximum supported dimensions */
} rank_t;

#endif // RANK_H
