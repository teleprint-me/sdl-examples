#include "primitives.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vector operations
vector_t* create_vector(size_t cols) {
    vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
    if (NULL == vector) { // If no memory was allocated
        fprintf(stderr, "Failed to allocate %zu bytes to struct Vector.\n", cols);
        return NULL; // Early return if vector creation failed
    }

    vector->elements = (float*) malloc(cols * sizeof(float));
    if (NULL == vector->elements) { // Failed to allocate memory for elements
        fprintf(stderr, "Failed to allocate %zu bytes to vector->elements.\n", cols);
        free(vector); // Free allocated vector memory to prevent leaks
        return NULL;  // Early return if vector creation failed
    }

    // After allocating vector->elements
    memset(vector->elements, 0, cols * sizeof(float));

    vector->cols = cols; // track the length of the vector to prevent decay.

    return vector;
}

void free_vector(vector_t* vector) {
    if (NULL == vector) {
        fprintf(stderr, "Cannot free a NULL vector.\n");
        return;
    }

    if (vector->elements) {
        free(vector->elements);
    }

    free(vector);
}

// Matrix operations
matrix_t* create_matrix(size_t rows, size_t cols) {
    matrix_t* matrix = (matrix_t*) malloc(sizeof(matrix_t));
    if (NULL == matrix) {
        fprintf(stderr, "Failed to allocate memory for matrix_t.\n");
        return NULL;
    }

    // multiply the width by the height to determine the max number of elements
    size_t total_elements = rows * cols;
    matrix->elements      = (float*) malloc(total_elements * sizeof(float));
    if (NULL == matrix->elements) {
        fprintf(stderr, "Failed to allocate memory for matrix rows.\n");
        free(matrix);
        return NULL;
    }

    memset(matrix->elements, 0, total_elements * sizeof(float));

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

void free_matrix(matrix_t* matrix) {
    if (NULL == matrix) {
        fprintf(stderr, "Cannot free a NULL matrix.\n");
        return;
    }

    if (matrix->elements) {
        free(matrix->elements);
    }

    free(matrix);
}

// Tensor operations
tensor_t* create_tensor(size_t* dimensions, rank_t rank) {
    if (rank == SCALAR || rank >= MAX_RANK) {
        fprintf(stderr, "Invalid rank for tensor. Must be between 1 and %d.\n", MAX_RANK - 1);
        return NULL;
    }

    tensor_t* tensor = (tensor_t*) malloc(sizeof(tensor_t));
    if (NULL == tensor) {
        fprintf(stderr, "Failed to allocate memory for tensor_t.\n");
        return NULL;
    }

    tensor->rank       = rank;
    tensor->dimensions = (size_t*) malloc(rank * sizeof(size_t));
    if (NULL == tensor->dimensions) {
        fprintf(stderr, "Failed to allocate memory for tensor dimensions.\n");
        free(tensor);
        return NULL;
    }

    size_t total_elements = 1;
    for (size_t i = 0; i < rank; ++i) {
        tensor->dimensions[i]  = dimensions[i];
        total_elements        *= dimensions[i];
    }

    tensor->elements = (float*) malloc(total_elements * sizeof(float));
    if (NULL == tensor->elements) {
        fprintf(stderr, "Failed to allocate memory for tensor elements.\n");
        free(tensor->dimensions);
        free(tensor);
        return NULL;
    }

    memset(tensor->elements, 0, total_elements * sizeof(float));

    return tensor;
}

void free_tensor(tensor_t* tensor) {
    if (NULL == tensor) {
        fprintf(stderr, "Cannot free a NULL tensor.\n");
        return;
    }

    if (tensor->dimensions) {
        free(tensor->dimensions);
    }

    if (tensor->elements) {
        free(tensor->elements);
    }

    free(tensor);
}

// Line segment operations
line_t* create_line(size_t cols) {
    line_t* line = (line_t*) malloc(sizeof(line_t));
    if (NULL == line) {
        fprintf(stderr, "Failed to allocate memory for line_t.\n");
        return NULL;
    }

    line->start = create_vector(cols);
    if (NULL == line->start) {
        fprintf(stderr, "Failed to allocate memory for line start.\n");
        free(line);
        return NULL;
    }

    line->end = create_vector(cols);
    if (NULL == line->end) {
        fprintf(stderr, "Failed to allocate memory for line end.\n");
        free_vector(line->start);
        free(line);
        return NULL;
    }

    return line;
}

void free_line(line_t* line) {
    if (NULL == line) {
        fprintf(stderr, "Cannot free a NULL line.\n");
        return;
    }

    if (line->start) {
        free_vector(line->start);
    }

    if (line->end) {
        free_vector(line->end);
    }

    free(line);
}

// Polygon operations
polygon_t* create_polygon(size_t max_vertices) {
    polygon_t* polygon = (polygon_t*) malloc(sizeof(polygon_t));
    if (NULL == polygon) {
        fprintf(stderr, "Failed to allocate memory for polygon_t structure.\n");
        return NULL;
    }

    polygon->vertices = create_vector(max_vertices);
    if (NULL == polygon->vertices) {
        fprintf(stderr, "Failed to allocate memory for polygon vertices.\n");
        free(polygon);
        return NULL;
    }

    polygon->max_vertices = max_vertices;
    polygon->count        = 0;    // Initialize count of vertices
    polygon->height       = 0.0f; // Default height
    polygon->distance     = 0.0f; // Default distance

    return polygon;
}

void free_polygon(polygon_t* polygon) {
    if (NULL == polygon) {
        fprintf(stderr, "Cannot free a NULL polygon.\n");
        return;
    }

    if (polygon->vertices) {
        free_vector(polygon->vertices);
    }

    free(polygon);
}

// Screen-space quadrilateral operations
screen_space_t* create_screen_space(size_t max_vertices) {
    screen_space_t* screen = (screen_space_t*) malloc(sizeof(screen_space_t));
    if (NULL == screen) {
        fprintf(stderr, "Failed to allocate memory for screen_space_t structure.\n");
        return NULL;
    }

    screen->vertices = create_vector(max_vertices);
    if (NULL == screen->vertices) {
        fprintf(stderr, "Failed to allocate memory for screen vertices.\n");
        free(screen);
        return NULL;
    }

    screen->max_vertices = max_vertices;
    screen->count        = 0;    // Initialize count to 0
    screen->depth        = 0.0f; // Default depth
    screen->id           = 0;    // Default identifier

    return screen;
}

void free_screen_space(screen_space_t* screen) {
    if (NULL == screen) {
        fprintf(stderr, "Cannot free a NULL screen_space_t structure.\n");
        return;
    }

    if (screen->vertices) {
        free_vector(screen->vertices);
    }

    free(screen);
}
