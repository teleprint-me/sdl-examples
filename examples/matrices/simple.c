#include "../../matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    matrix_t* matrix       = matrix_create(2, 2);
    matrix->elements[0][0] = 1.25f;
    matrix->elements[0][1] = 2.7f;
    matrix->elements[1][0] = 3.15f;
    matrix->elements[1][1] = 4.5f;

    for (size_t row = 0; row < matrix->rows; row++) {
        for (size_t column = 0; column < matrix->columns; column++) {
            float element = matrix->elements[row][column];
            fprintf(stderr, "matrix->elements[%zu][%zu] = %.2f\n", row, column, element);
        }
    }

    matrix_free(matrix);
    return 0;
}
