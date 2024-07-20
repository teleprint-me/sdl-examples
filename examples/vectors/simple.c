/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/vectors/simple.c
 *
 * @brief Simple C program demonstrating vector addition and calculating the magnitude of a
 * resulting vector.
 */

#include "../../shape.h"
#include "../../vector.h"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    size_t dimensions = 2; // 2-dimensional vector

    // Create and initialize vector 'a'
    vector_t* a = vector_create(dimensions);
    if (!a) {
        fprintf(stderr, "Failed to allocate memory for vector 'a'.\n");
        return EXIT_FAILURE;
    }
    a->elements[X] = 1.5f;
    a->elements[Y] = 2.75f;

    // Create and initialize vector 'b'
    vector_t* b = vector_create(dimensions);
    if (!b) {
        fprintf(stderr, "Failed to allocate memory for vector 'b'.\n");
        vector_free(a);
        return EXIT_FAILURE;
    }
    b->elements[X] = 3.25f;
    b->elements[Y] = 1.25f;

    // Perform vector addition
    vector_t* c = vector_vector_add(a, b);
    if (!c) {
        fprintf(stderr, "Failed to allocate memory for vector 'c'.\n");
        vector_free(a);
        vector_free(b);
        return EXIT_FAILURE;
    }

    // Calculate the magnitude of vector 'c'
    float magnitude = vector_magnitude(c);

    // Print vector elements and magnitude
    for (size_t i = 0; i < dimensions; i++) {
        fprintf(stderr, "a->elements[%zu] = %.2f\n", i, a->elements[i]);
        fprintf(stderr, "b->elements[%zu] = %.2f\n", i, b->elements[i]);
        fprintf(stderr, "c->elements[%zu] = %.2f\n", i, c->elements[i]);
    }
    fprintf(stderr, "Magnitude of c is %.2f.\n", magnitude);

    // Free allocated memory
    vector_free(a);
    vector_free(b);
    vector_free(c);

    return EXIT_SUCCESS;
}
