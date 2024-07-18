/**
 * Copyright © 2024 Austin Berrio
 *
 * @brief A simple and easy to use Vector API
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 */
#ifndef VECTORS_H
#define VECTORS_H

#include <stdbool.h>
#include <stdlib.h>

// N-dimensional vector structure
// Coordinates for a point in a line or plane
// May also represent the magnitude and or direction of an object in a line or plane
typedef struct {
    size_t dimensions;   // Number of dimensions for the vector, e.g. 2d, 3d
    float* displacement; // Dynamic array of elements representing the vector
} vector_t;

vector_t* vector_create(size_t cols);
void      vector_free(vector_t* vector);

// Helper functions for element-wise operations
float scalar_add(float x, float y);
float scalar_subtract(float x, float y);
float scalar_multiply(float x, float y);
float scalar_divide(float x, float y);

vector_t* vector_elementwise_operation(
    const vector_t* a, const vector_t* b, float (*operation)(float, float)
);

// Scalar based vector operations
vector_t* vector_scalar_add(const vector_t* a, const float b);
vector_t* vector_scalar_sub(const vector_t* a, const float b);
vector_t* vector_scalar_mul(const vector_t* a, const float b);
vector_t* vector_scalar_div(const vector_t* a, const float b);

// Vector based operations
vector_t* vector_vector_add(const vector_t* a, const vector_t* b);
vector_t* vector_vector_sub(const vector_t* a, const vector_t* b);
vector_t* vector_vector_mul(const vector_t* a, const vector_t* b);
vector_t* vector_vector_div(const vector_t* a, const vector_t* b);

// Common vector operations
vector_t* vector_copy(const vector_t* vector);
float     vector_magnitude(const vector_t* vector);
vector_t* vector_normalize(vector_t* vector, bool inplace);
float     vector_distance(const vector_t* a, const vector_t* b);
vector_t* vector_scale(vector_t* vector, float scalar, bool inplace);
float     vector_mean(vector_t* vector);
vector_t* vector_clip(vector_t* vector, float min, float max, bool inplace);

// Special vector operations

// Special products
float     vector_dot_product(const vector_t* a, const vector_t* b);
vector_t* vector_cross_product(const vector_t* a, const vector_t* b);

// Special coordinates
vector_t* vector_polar_to_cartesian(const vector_t* polar_vector);
vector_t* vector_cartesian_to_polar(const vector_t* cartesian_vector);

#endif // VECTORS_H
