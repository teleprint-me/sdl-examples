/**
 * Copyright © 2024 Austin Berrio
 *
 * @file vector.h
 *
 * @brief A simple and easy to use Vector API in C
 *
 * This header file provides an implementation for basic mathematical operations on N-dimensional
 * vectors, including creation, destruction, element-wise functions, scalar-based functions,
 * vector-based functions, common vector operations, special vector operations, and conversion
 * between polar and cartesian coordinates.
 *
 * Only pure C is used with minimal dependencies on external libraries.
 */

#ifndef VECTORS_H
#define VECTORS_H

#include <stdbool.h>
#include <stdlib.h>

// Vector lifecycle management

/**
 * @brief A structure representing an N-dimensional vector
 *
 * This structure stores the number of dimensions and a dynamic array of floating point values,
 * which represent the components of the vector in each dimension.
 */
typedef struct {
    size_t dimensions;   // Number of dimensions for the vector
    float* displacement; // Dynamic array of elements representing the vector
} vector_t;

/**
 * @brief Create a new N-dimensional vector
 *
 * This function dynamically allocates memory and initializes a new vector with the specified number
 * of dimensions. The values in the vector are set to zero by default.
 */
vector_t* vector_create(size_t dimensions);

/**
 * @brief Free an allocated N-dimensional vector
 *
 * This function deallocates memory associated with a given vector, releasing any resources used
 * during its creation.
 */
void vector_free(vector_t* vector);

// Element-wise operations

/**
 * @brief Helper functions for element-wise operations
 *
 * These helper functions perform basic arithmetic on two floating point values and return the
 * result.
 */
float scalar_add(float x, float y);
float scalar_subtract(float x, float y);
float scalar_multiply(float x, float y);
float scalar_divide(float x, float y);

/**
 * @brief Executor for element-wise functions
 *
 * This function applies a given operation to each corresponding pair of elements in two vectors and
 * returns the resulting vector.
 */
vector_t* vector_elementwise_operation(
    const vector_t* a, const vector_t* b, float (*operation)(float, float)
);

// Scalar based vector operations

/**
 * @brief Add a scalar value to an N-dimensional vector
 */
vector_t* vector_scalar_add(const vector_t* a, const float b);

/**
 * @brief Subtract a scalar value from an N-dimensional vector
 */
vector_t* vector_scalar_subtract(const vector_t* a, const float b);

/**
 * @brief Multiply a scalar value with an N-dimensional vector
 */
vector_t* vector_scalar_multiply(const vector_t* a, const float b);

/**
 * @brief Divide an N-dimensional vector by a scalar value
 */
vector_t* vector_scalar_divide(const vector_t* a, const float b);

// Vector based operations

/**
 * @brief Add two N-dimensional vectors
 */
vector_t* vector_vector_add(const vector_t* a, const vector_t* b);

/**
 * @brief Subtract one N-dimensional vector from another
 */
vector_t* vector_vector_subtract(const vector_t* a, const vector_t* b);

/**
 * @brief Multiply two N-dimensional vectors
 */
vector_t* vector_vector_multiply(const vector_t* a, const vector_t* b);

/**
 * @brief Divide an N-dimensional vector by another N-dimensional vector
 */
vector_t* vector_vector_divide(const vector_t* a, const vector_t* b);

// Common vector operations

/**
 * @brief Copy a given N-dimensional vector
 *
 * This function creates a deep copy of the input vector by allocating new memory and
 * duplicating its contents.
 */
vector_t* vector_deep_copy(const vector_t* vector);

/**
 * @brief Create a shallow copy of an N-dimensional vector
 *
 * This function returns a pointer to the same allocated memory as the input vector, effectively
 * creating a reference (shallow) copy.
 */
vector_t* vector_shallow_copy(const vector_t* vector);

/**
 * @brief Determine the magnitude or length of an N-dimensional vector
 */
float vector_magnitude(const vector_t* vector);

/**
 * @brief Calculate the distance between two given N-dimensional vectors
 */
float vector_distance(const vector_t* a, const vector_t* b);

/**
 * @brief Calculate the mean of an N-dimensional vector
 */
float vector_mean(vector_t* vector);

/**
 * @brief Low pass filter on an N-dimensional vector
 */
float vector_low_pass_filter(vector_t* vector);

/**
 * @brief Resize the dimensions of an N-dimensional vector
 */
vector_t* vector_resize(vector_t* vector, size_t new_size);

/**
 * @brief Normalize a given N-dimensional vector in place
 */
void vector_normalize_inplace(vector_t* vector);

/**
 * @brief Scale an N-dimensional vector by the specified factor
 */
vector_t* vector_scale(vector_t* vector, float scalar, bool inplace);

/**
 * @brief Clip an N-dimensional vector within a given range
 */
vector_t* vector_clip(vector_t* vector, float min, float max, bool inplace);

// Special vector operations

/**
 * @brief Calculate the dot product of two N-dimensional vectors
 */
float vector_dot_product(const vector_t* a, const vector_t* b);

/**
 * @brief Return the cross product of two 3D vectors
 */
vector_t* vector_cross_product(const vector_t* a, const vector_t* b);

// Special coordinates

/**
 * @brief Convert polar coordinates to cartesian coordinates
 */
vector_t* vector_polar_to_cartesian(const vector_t* polar_vector);

/**
 * @brief Convert cartesian coordinates to polar coordinates
 */
vector_t* vector_cartesian_to_polar(const vector_t* cartesian_vector);

#endif // VECTORS_H
