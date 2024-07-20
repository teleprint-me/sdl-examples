/**
 * @file tensor.h
 */

#ifndef TENSOR_H
#define TENSOR_H

#include <stdlib.h>

/**
 * @brief N-dimensional tensor structure
 *
 * A tensor is a rectangular prism where each element may be thought of as a cubic unit
 * A complex, multidimensional, representation of vectors and or matrices
 * Typically used to represent complex 2D and or 3D spaces and planes
 *
 * @param elements
 * @param cols
 * @param rows
 * @param depth
 */
typedef struct Tensor {
    float*** elements; // 3-dimensional array representing tensor elements
    size_t   cols;     // width?
    size_t   rows;     // height
    size_t   depth;    // length?
} tensor_t;

// Tensor operations
tensor_t* create_tensor(size_t cols, size_t rows, size_t depth);
void      free_tensor(tensor_t* tensor);

#endif // TENSOR_H
