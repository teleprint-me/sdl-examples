/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/matrices/simple.c
 *
 * @brief Simple C program demonstrating the creation, initialization, and printing of a 2x2 matrix
 */

#include "../../matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matrix(const matrix_t* matrix) {
    const size_t width = matrix->columns + 2;

    // Print header row
    fprintf(stderr, "[\n");

    // Iterate through the rows and columns
    for (size_t row = 0; row < matrix->rows; ++row) {
        fprintf(stderr, "  [ ");

        for (size_t column = 0; column < matrix->columns; ++column) {
            float element = matrix->elements[row][column];

            // Print the value with proper formatting
            fprintf(stderr, "%*.*f ", width - 2, width - 3, element);
        }

        fprintf(stderr, "]\n");
    }

    fprintf(stderr, "]\n");
}

int main(int argc, char* argv[]) {
    // Create a 2x2 matrix
    matrix_t* matrix = matrix_create(2, 2);

    // Initialize the matrix with specific values
    matrix->elements[0][0] = 1.25f;
    matrix->elements[0][1] = 2.7f;
    matrix->elements[1][0] = 3.15f;
    matrix->elements[1][1] = 4.5f;

    // Print the initialized matrix
    print_matrix(matrix);

    // Free the memory allocated for the matrix
    matrix_free(matrix);

    return 0;
}
