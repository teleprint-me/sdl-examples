/**
 * @file examples/vectors/simple.c
 */

#include "../../shape.h"
#include "../../vector.h"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    size_t dimensions = 2; // 2-dimensional vector

    vector_t* a    = vector_create(dimensions);
    a->elements[X] = 1.5f;
    a->elements[Y] = 2.75f;

    vector_t* b    = vector_create(dimensions);
    b->elements[X] = 3.25f;
    b->elements[Y] = 1.25f;

    vector_t* c = vector_vector_add(a, b);

    // distance formula = | V | = √a^2 + √b^2
    float magnitude = vector_magnitude(c);

    for (size_t i = 0; i < dimensions; i++) {
        fprintf(stderr, "a->elements[%zd] = %.2f\n", i, a->elements[i]);
        fprintf(stderr, "b->elements[%zd] = %.2f\n", i, b->elements[i]);
        fprintf(stderr, "c->elements[%zd] = %.2f\n", i, c->elements[i]);
    }

    fprintf(stderr, "magnitude of c is %f.\n", magnitude);

    vector_free(a);
    vector_free(b);
    vector_free(c);

    return 0;
}
