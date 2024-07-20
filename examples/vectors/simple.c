/**
 * @file examples/vectors/simple.c
 */

#include "../../vector.h"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#define X 0
#define Y 1

size_t calculate_vector_magnitude(SDL_FPoint* point) {
    // distance formula = | V | = √a^2 + √b^2
    return abs((int) sqrtf(powf(point->x, 2) + powf(point->y, 2)));
}

int main(int argc, char* argv[]) {
    size_t dimensions = 2; // 2-dimensional vector

    vector_t* a    = vector_create(dimensions);
    a->elements[X] = 1.5f;
    a->elements[Y] = 2.75f;

    vector_t* b    = vector_create(dimensions);
    b->elements[X] = 3.25f;
    b->elements[Y] = 1.25f;

    vector_t* c = vector_vector_add(a, b);

    for (size_t i = 0; i < dimensions; i++) {
        fprintf(stderr, "a->elements[%zd] = %.2f\n", i, a->elements[i]);
        fprintf(stderr, "b->elements[%zd] = %.2f\n", i, b->elements[i]);
        fprintf(stderr, "c->elements[%zd] = %.2f\n", i, c->elements[i]);
    }

    vector_free(a);
    vector_free(b);
    vector_free(c);

    return 0;
}
