/**
 * Copyright © 2024 Austin Berrio
 *
 * @file tensor.c
 *
 * @brief A simple and easy to use Tensor API.
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 */

#include "tensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tensor operations
tensor_t* tensor_create(size_t columns, size_t rows, size_t layers) {
    // Allocate memory for the tensor structure
    tensor_t* tensor = (tensor_t*) malloc(sizeof(tensor_t));
    if (NULL == tensor) {
        fprintf(stderr, "Failed to allocate memory for tensor_t.\n");
        return NULL;
    }

    tensor->columns = columns;
    tensor->rows    = rows;
    tensor->layers  = layers;

    // Allocate memory for the 3D array
    tensor->elements = (float***) malloc(layers * sizeof(float**));
    if (NULL == tensor->elements) {
        fprintf(stderr, "Failed to allocate memory for tensor elements.\n");
        free(tensor);
        return NULL;
    }

    for (size_t d = 0; d < layers; ++d) {
        tensor->elements[d] = (float**) malloc(rows * sizeof(float*));
        if (NULL == tensor->elements[d]) {
            fprintf(stderr, "Failed to allocate memory for tensor rows.\n");
            for (size_t i = 0; i < d; ++i) {
                free(tensor->elements[i]);
            }
            free(tensor->elements);
            free(tensor);
            return NULL;
        }

        for (size_t r = 0; r < rows; ++r) {
            tensor->elements[d][r] = (float*) calloc(columns, sizeof(float));
            if (NULL == tensor->elements[d][r]) {
                fprintf(stderr, "Failed to allocate memory for tensor columns.\n");
                for (size_t j = 0; j < r; ++j) {
                    free(tensor->elements[d][j]);
                }
                free(tensor->elements[d]);
                for (size_t i = 0; i < d; ++i) {
                    for (size_t j = 0; j < rows; ++j) {
                        free(tensor->elements[i][j]);
                    }
                    free(tensor->elements[i]);
                }
                free(tensor->elements);
                free(tensor);
                return NULL;
            }
        }
    }

    return tensor;
}

void tensor_free(tensor_t* tensor) {
    if (NULL == tensor) {
        return;
    }

    for (size_t d = 0; d < tensor->layers; ++d) {
        for (size_t r = 0; r < tensor->rows; ++r) {
            free(tensor->elements[d][r]);
        }
        free(tensor->elements[d]);
    }

    free(tensor->elements);
    free(tensor);
}
