#include "primitives.h"

#include <stdio.h>

vector_t* vector_add(vector_t* a, vector_t* b) {
    if (a->cols != b->cols) {
        fprintf(stderr, "Vectors must have the same length.\n");
        return NULL;
    }

    // also known as the length or size of a vector
    size_t magnitude = a->cols;

    vector_t* c = create_vector(magnitude);
    for (size_t i = 0; i < magnitude; i++) {
        c->elements[i] = a->elements[i] + b->elements[i];
    }

    return c;
}

int main(int argc, char* argv[]) {
    size_t    magnitude = 2; // 2-dimensional vector
    vector_t* a         = create_vector(magnitude);
    a->elements[X]      = 1.5f;
    a->elements[Y]      = 2.75f;

    vector_t* b    = create_vector(magnitude);
    b->elements[X] = 3.25f;
    b->elements[Y] = 1.25f;

    vector_t* c = vector_add(a, b);

    for (size_t i = 0; i < magnitude; i++) {
        fprintf(stderr, "a->elements[%zd] = %.2f\n", i, a->elements[i]);
        fprintf(stderr, "b->elements[%zd] = %.2f\n", i, b->elements[i]);
        fprintf(stderr, "c->elements[%zd] = %.2f\n", i, c->elements[i]);
    }

    free_vector(a);
    free_vector(b);
    free_vector(c);

    return 0;
}
