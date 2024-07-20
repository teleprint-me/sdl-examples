#include "tensor.h"
#include "shape.h"

#include <stdio.h>

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
