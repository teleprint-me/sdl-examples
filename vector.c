/**
 * Copyright © 2024 Austin Berrio
 *
 * @file vector.c
 *
 * @brief A simple and easy to use Vector API
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 */

#include "vector.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vector lifecycle management
vector_t* vector_create(size_t dimensions) {
    vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
    if (NULL == vector) { // If no memory was allocated
        fprintf(stderr, "Failed to allocate %zu bytes to vector_t.\n", dimensions);
        return NULL; // Early return if vector creation failed
    }

    vector->displacement = (float*) malloc(dimensions * sizeof(float));
    if (NULL == vector->displacement) { // Failed to allocate memory for displacement
        fprintf(stderr, "Failed to allocate %zu bytes to vector->displacement.\n", dimensions);
        free(vector); // Free allocated vector memory to prevent leaks
        return NULL;  // Early return if vector creation failed
    }

    // After allocating vector->displacement
    memset(vector->displacement, 0, dimensions * sizeof(float));

    vector->dimensions = dimensions; // track the dimensions of the vector to prevent decay.

    return vector;
}

void vector_free(vector_t* vector) {
    if (vector->displacement) {
        free(vector->displacement);
    }

    if (vector) {
        free(vector);
    }
}

vector_t* vector_deep_copy(const vector_t* vector) {
    vector_t* deep_copy = vector_create(vector->dimensions);
    if (NULL == deep_copy) {
        return NULL;
    }

    for (size_t i = 0; i < vector->dimensions; ++i) {
        deep_copy->displacement[i] = vector->displacement[i];
    }

    return deep_copy;
}

vector_t* vector_shallow_copy(const vector_t* vector) {
    if (NULL == vector) {
        return NULL;
    }

    // Allocate memory for the new Vector structure only, not for its displacement
    vector_t* new_vector = (vector_t*) malloc(sizeof(vector_t));
    if (NULL == new_vector) { // If no memory was allocated
        fprintf(stderr, "Failed to allocate %zu bytes to vector_t.\n", sizeof(vector_t));
        return NULL; // Early return if vector creation failed
    }

    // Copy all fields except displacement (pointer to an array)
    new_vector->dimensions = vector->dimensions;

    // Assign the existing pointer to the new Vector structure
    new_vector->displacement = vector->displacement;

    return new_vector;
}

// Vector mathematical operations
float vector_magnitude(const vector_t* vector) {
    float sum = 0;

    // sum the square of the displacement for n-dimensional vectors
    for (size_t i = 0; i < vector->dimensions; i++) {
        sum += vector->displacement[i] * vector->displacement[i];
    }

    return sqrt(sum);
}

vector_t* vector_normalize(vector_t* vector, bool inplace) {
    float magnitude = vector_magnitude(vector);

    if (0 == magnitude) {
        fprintf(stderr, "Cannot normalize a zero-length vector.\n");
        return NULL;
    }

    if (inplace) {
        // scale the displacement down by the magnitude to produce a unit vector
        for (size_t i = 0; i < vector->dimensions; i++) {
            vector->displacement[i] /= magnitude;
        }

        return vector;
    }

    vector_t* unit = vector_create(vector->dimensions);
    if (NULL == unit) {
        fprintf(stderr, "Failed to allocate memory for the normalized unit vector.\n");
        return NULL;
    }

    for (size_t i = 0; i < vector->dimensions; i++) {
        unit->displacement[i] = vector->displacement[i] / magnitude;
    }

    return unit;
}

float vector_distance(const vector_t* a, const vector_t* b) {
    float distance_squared = 0.0f;

    if (a->dimensions != b->dimensions) {
        fprintf(
            stderr,
            "Vector dimensions do not match. Cannot perform operation on vectors of dimensions %zu "
            "and %zu.\n",
            a->dimensions,
            b->dimensions
        );
        return NAN;
    }

    for (size_t i = 0; i < a->dimensions; ++i) {
        distance_squared += (a->displacement[i] - b->displacement[i])
                            * (a->displacement[i] - b->displacement[i]);
    }

    return sqrtf(distance_squared);
}

vector_t* vector_scale(vector_t* vector, float scalar, bool inplace) {
    if (vector == NULL) {
        return NULL;
    }

    if (inplace) { // block out-of-place vector scaling if in-place is true
        for (size_t i = 0; i < vector->dimensions; ++i) {
            vector->displacement[i] *= scalar; // scale the vector in-place
        }
        return vector; // return the scaled vector
    }

    // perform out-of-place vector scaling
    vector_t* scaled_vector = vector_create(vector->dimensions);
    if (scaled_vector == NULL) {
        fprintf(stderr, "Failed to allocate memory for scaled vector.\n");
        return NULL;
    }

    for (size_t i = 0; i < vector->dimensions; ++i) {
        scaled_vector->displacement[i] = vector->displacement[i] * scalar;
    }

    return scaled_vector;
}

float vector_mean(const vector_t* vector) {
    if (NULL == vector || 0 == vector->dimensions) {
        return NAN; // Return NAN for invalid input
    }

    float sum = 0.0f;
    for (size_t i = 0; i < vector->dimensions; i++) {
        if (isnan(vector->displacement[i])) {
            // Log error and return NAN if any element is NaN
            fprintf(stderr, "NaN element found at index %zu.\n", i);
            return NAN;
        }
        sum += vector->displacement[i];
    }

    return sum / vector->dimensions; // Return the mean
}

vector_t* vector_clip(vector_t* vector, float min, float max, bool inplace) {
    if (NULL == vector || 0 == vector->dimensions) {
        return NULL;
    }

    if (inplace) {
        for (size_t i = 0; i < vector->dimensions; i++) {
            if (vector->displacement[i] < min) {
                vector->displacement[i] = min;
            }
            if (vector->displacement[i] > max) {
                vector->displacement[i] = max;
            }
        }

        return vector; // return as soon as possible
    }

    // create a vector if !inplace
    vector_t* clipped_vector = vector_create(vector->dimensions);
    if (NULL == clipped_vector) {
        return NULL; // NOTE: we can return and not log because vector_create logs the error for us
    }

    for (size_t i = 0; i < vector->dimensions; i++) {
        if (vector->displacement[i] < min) {
            clipped_vector->displacement[i] = min;
        } else if (vector->displacement[i] > max) {
            clipped_vector->displacement[i] = max;
        } else {
            clipped_vector->displacement[i] = vector->displacement[i];
        }
    }

    // Return the newly created clipped vector
    return clipped_vector;
}

// Helper function for element-wise operations
float scalar_add(float x, float y) {
    return x + y;
}

float scalar_subtract(float x, float y) {
    return x - y;
}

float scalar_multiply(float x, float y) {
    return x * y;
}

float scalar_divide(float x, float y) {
    if (y == 0) {
        fprintf(stderr, "Division by zero is undefined. Cannot divide x (%f) by y (%f).\n", x, y);
        return NAN; // Division by zero is undefined
    }
    return x / y;
}

// Function to perform element-wise operation on two vectors
vector_t* perform_elementwise_operation(
    const vector_t* a, const vector_t* b, float (*operation)(float, float)
) {
    if (a->dimensions != b->dimensions) {
        fprintf(
            stderr,
            "Vector dimensions do not match. Cannot perform operation on vectors of dimensions %zu "
            "and %zu.\n",
            a->dimensions,
            b->dimensions
        );
        return NULL;
    }

    vector_t* c = vector_create(a->dimensions);
    if (NULL == c) {
        fprintf(stderr, "Failed to allocate memory for the resultant vector.\n");
        return NULL;
    }

    // Perform element-wise operation
    for (size_t i = 0; i < a->dimensions; i++) {
        c->displacement[i] = operation(a->displacement[i], b->displacement[i]);
    }

    return c;
}

// Updated functions using the new helper function
vector_t* vector_vector_add(const vector_t* a, const vector_t* b) {
    return perform_elementwise_operation(a, b, scalar_add);
}

vector_t* vector_vector_subtract(const vector_t* a, const vector_t* b) {
    return perform_elementwise_operation(a, b, scalar_subtract);
}

vector_t* vector_vector_multiply(const vector_t* a, const vector_t* b) {
    return perform_elementwise_operation(a, b, scalar_multiply);
}

vector_t* vector_vector_divide(const vector_t* a, const vector_t* b) {
    return perform_elementwise_operation(a, b, scalar_divide);
}

// dot product is n-dimensional
float vector_dot_product(const vector_t* a, const vector_t* b) {
    if (a->dimensions != b->dimensions) {
        fprintf(
            stderr,
            "Vector dimensions do not match. Cannot perform operation on vectors of dimensions %zu "
            "and %zu.\n",
            a->dimensions,
            b->dimensions
        );
        return NAN;
    }

    float product = 0.0f;

    for (size_t i = 0; i < a->dimensions; i++) {
        product += a->displacement[i] * b->displacement[i];
    }

    return product;
}

// cross product is 3-dimensional
vector_t* vector_cross_product(const vector_t* a, const vector_t* b) {
    // Ensure both vectors are 3-dimensional.
    if (a->dimensions != 3 || b->dimensions != 3) {
        fprintf(stderr, "Cross product is only defined for 3-dimensional vectors.\n");
        return NULL;
    }

    vector_t* result = vector_create(3);
    if (result == NULL) {
        fprintf(stderr, "Failed to allocate memory for cross product vector.\n");
        return NULL;
    }

    // Calculate the components of the cross product vector.
    result->displacement[0]
        = a->displacement[1] * b->displacement[2] - a->displacement[2] * b->displacement[1];
    result->displacement[1]
        = a->displacement[2] * b->displacement[0] - a->displacement[0] * b->displacement[2];
    result->displacement[2]
        = a->displacement[0] * b->displacement[1] - a->displacement[1] * b->displacement[0];

    return result;
}

// Polar coordinates are defined as the ordered pair (r, θ) names a point r units from origin along
// the terminal side of angle θ in standard position (origin to displacement).

// The derivation between polar and cartesian coordinates is to consider a point P with the
// rectangular (x, y) and polar (r, θ) coordinates.

// Formula is as defined:
// r = ± √(x^2 + y^2)
// tan θ = y / x
// x = r cos θ
// y = r sin θ
// theta is the angle between the hypotenuse and the x-axis.
// P is (x, y) is (r, θ)
// x is the base, y is the height, assuming a right angle between rise over run
// r is hypotenuse

// Coordinate transformation functions (prototypes to be defined)

// x = r cos θ and y = r sin θ
vector_t* vector_polar_to_cartesian(const vector_t* polar_vector) {
    if (NULL == polar_vector || polar_vector->dimensions != 2) {
        return NULL; // Return NULL if input is invalid
    }

    vector_t* cartesian_vector = vector_create(2);
    if (NULL == cartesian_vector) {
        return NULL; // Return NULL if memory allocation fails
    }

    // radii/radius/ray all seem equivalently apropos
    // perhaps ray is best suited?
    float r     = polar_vector->displacement[0];
    float theta = polar_vector->displacement[1];

    cartesian_vector->displacement[0] = r * cos(theta); // x = r * cos(θ)
    cartesian_vector->displacement[1] = r * sin(theta); // y = r * sin(θ)

    return cartesian_vector;
}

// r = ± √(x^2 + y^2) and tan θ = y / x
vector_t* vector_cartesian_to_polar(const vector_t* cartesian_vector) {
    if (NULL == cartesian_vector || cartesian_vector->dimensions != 2) {
        return NULL; // Return NULL if input is invalid
    }

    vector_t* polar_vector = vector_create(2);
    if (NULL == polar_vector) {
        return NULL; // Return NULL if memory allocation fails
    }

    float x = cartesian_vector->displacement[0];
    float y = cartesian_vector->displacement[1];

    polar_vector->displacement[0] = sqrt(x * x + y * y); // r = √(x^2 + y^2)
    polar_vector->displacement[1] = atan2(y, x);         // θ = atan2(y, x)

    return polar_vector;
}
