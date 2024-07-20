/**
 * Copyright © 2024 Austin Berrio
 *
 * @file tensor.h
 *
 * @brief A simple and easy to use Tensor API
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 */

#ifndef TENSOR_H
#define TENSOR_H

#include <stdlib.h>

// Tensor lifecycle

/**
 * @brief A structure representing a 3-dimensional tensor.
 *
 * A tensor is a rectangular prism where each element may be thought of as a cubic unit.
 * It is a complex, multidimensional representation of vectors and/or matrices, typically used to
 * represent complex 2D and/or 3D spaces and planes.
 *
 * @param elements A three-dimensional pointer to an array of floats, representing the tensor
 * elements.
 * @param columns  The number of columns (width) of the tensor.
 * @param rows     The number of rows (height) of the tensor.
 * @param depth    The number of layers (depth) of the tensor.
 */
typedef struct {
    float*** elements; ///< Three-dimensional array representing the tensor elements.
    size_t   columns;  ///< The number of columns (width) of the tensor.
    size_t   rows;     ///< The number of rows (height) of the tensor.
    size_t   depth;    ///< The number of layers (depth) of the tensor.
} tensor_t;

/**
 * @brief Creates a new tensor with the specified dimensions.
 *
 * This function allocates memory for a tensor with the given number of columns, rows, and depth.
 * The tensor elements are initialized to zero.
 *
 * @param columns The number of columns (width) for the tensor.
 * @param rows    The number of rows (height) for the tensor.
 * @param depth   The number of layers (depth) for the tensor.
 *
 * @return        A pointer to the newly created tensor, or NULL if memory allocation fails.
 */
tensor_t* tensor_create(size_t columns, size_t rows, size_t depth);

/**
 * @brief Frees the memory allocated for a tensor.
 *
 * This function deallocates the memory associated with a tensor, including the memory for the
 * tensor elements and the tensor structure itself.
 *
 * @param tensor A pointer to the tensor to be freed. If the pointer is NULL, no action is taken.
 */
void tensor_free(tensor_t* tensor);

// Tensor operations

#endif // TENSOR_H
