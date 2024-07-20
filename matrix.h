/**
 * Copyright © 2024 Austin Berrio
 *
 * @file matrix.h
 *
 * @brief A simple and easy to use Matrix API
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

// Structures

// N-dimensional matrix structure
// A matrix is a rectangular array of rows and columns representing a 2-dimensional space
typedef struct {
    float** elements; // Flat array representing the matrix elements
    size_t  cols;     // The width of a matrix
    size_t  rows;     // The height of a matrix
} matrix_t;

// Life-cycle operations

/**
 * @brief Creates a new matrix with the specified number of rows and columns.
 * Initializes all elements to zero.
 *
 * @param rows Number of rows.
 * @param cols Number of columns.
 * @return Pointer to the newly created matrix or NULL if allocation fails.
 */
matrix_t* matrix_create(size_t rows, size_t cols);

/**
 * Free its memory. Safely handles NULL pointers.
 *
 * @param matrix Pointer to the matrix to be destroyed.
 * @return true if the operation is successful, false otherwise.
 */
void matrix_free(matrix_t* matrix);

/**
 * Creates a deep copy of a given matrix, duplicating all its elements.
 *
 * @param matrix Pointer to the matrix to be copied.
 * @return Pointer to the new matrix copy or NULL if allocation fails.
 */
matrix_t* matrix_deep_copy(const matrix_t* matrix);

/**
 * Creates a shallow copy of a given matrix. Only the matrix structure is duplicated, not the data.
 *
 * @param matrix Pointer to the matrix to be copied.
 * @return Pointer to the new matrix structure or NULL if allocation fails.
 */
matrix_t* matrix_shallow_copy(const matrix_t* matrix);

// Additional operations (placeholders for future implementation)

/**
 * Adds two matrices and returns the result.
 *
 * @param a Pointer to the first matrix.
 * @param b Pointer to the second matrix.
 * @return Pointer to the result matrix or NULL if the operation fails.
 */
matrix_t* matrix_add(const matrix_t* a, const matrix_t* b);

/**
 * Multiplies two matrices and returns the result.
 *
 * @param a Pointer to the first matrix.
 * @param b Pointer to the second matrix.
 * @return Pointer to the result matrix or NULL if the operation fails.
 */
matrix_t* matrix_multiply(const matrix_t* a, const matrix_t* b);

/**
 * Transposes a matrix and returns the result.
 *
 * @param matrix Pointer to the matrix to be transposed.
 * @return Pointer to the transposed matrix or NULL if the operation fails.
 */
matrix_t* matrix_transpose(const matrix_t* matrix);

#endif // MATRIX_H
