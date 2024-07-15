#include "primitives.h"

#include <stdio.h>
#include <string.h>

// Vector operations
vector_t* create_vector(size_t size) {
    vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
    if (NULL == vector) { // If no memory was allocated
        fprintf(stderr, "Failed to allocate %zu bytes to struct Vector.\n", size);
        return NULL; // Early return if vector creation failed
    }

    vector->elements = (float*) malloc(size * sizeof(float));
    if (NULL == vector->elements) { // Failed to allocate memory for elements
        fprintf(stderr, "Failed to allocate %zu bytes to vector->elements.\n", size);
        free(vector); // Free allocated vector memory to prevent leaks
        return NULL;  // Early return if vector creation failed
    }

    // After allocating vector->elements
    memset(vector->elements, 0, size * sizeof(float));

    vector->size = size; // track the size of the vector to prevent decay.

    return vector;
}

void free_vector(vector_t* vector) {
    if (NULL == vector) {
        fprintf(stderr, "Cannot free a NULL struct Vector.\n");
    }

    if (NULL == vector->elements) {
        fprintf(stderr, "Cannot free a NULL vector->elements member.\n");
    }

    free(vector->elements);
    free(vector);
}

// Matrix operations
matrix_t* create_matrix(size_t n_rows, size_t n_cols) {
    matrix_t* matrix = (matrix_t*) malloc(sizeof(matrix_t));
    if (NULL == matrix) {
        fprintf(stderr, "Failed to allocate memory for matrix_t.\n");
        return NULL;
    }

    matrix->elements = (float**) malloc(n_rows * sizeof(float*));
    if (NULL == matrix->elements) {
        fprintf(stderr, "Failed to allocate memory for matrix rows.\n");
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < n_rows; ++i) {
        matrix->elements[i] = (float*) malloc(n_cols * sizeof(float));
        if (NULL == matrix->elements[i]) {
            fprintf(stderr, "Failed to allocate memory for matrix columns.\n");
            // Free previously allocated rows
            for (size_t j = 0; j < i; ++j) {
                free(matrix->elements[j]);
            }
            free(matrix->elements);
            free(matrix);
            return NULL;
        }
        memset(matrix->elements[i], 0, n_cols * sizeof(float));
    }

    matrix->n_rows = n_rows;
    matrix->n_cols = n_cols;

    return matrix;
}

void free_matrix(matrix_t* matrix) {
    if (NULL == matrix) {
        fprintf(stderr, "Cannot free a NULL matrix.\n");
        return;
    }

    if (NULL != matrix->elements) {
        for (size_t i = 0; i < matrix->n_rows; ++i) {
            if (NULL != matrix->elements[i]) {
                free(matrix->elements[i]);
            }
        }
        free(matrix->elements);
    }

    free(matrix);
}

// Tensor operations
tensor_t create_tensor(size_t* dimensions, rank_t rank);
void     free_tensor(tensor_t* tensor);

// Line segment operations
line_t create_line(size_t size) {
    return;
}

void free_line(line_t* line) {
    if (NULL != line) {
        free(line);
    }
}

// Polygon operations
polygon_t create_polygon(size_t max_vertices);
void      free_polygon(polygon_t* polygon);

// Screen-space quadrilateral operations
screen_space_t create_screen_space(size_t max_vertices);
void           free_screen_space(screen_space_t* quad);
