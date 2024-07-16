#include "primitives.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    vector_t* vec    = create_vector(2); // 2d vector
    vec->elements[X] = 1.5f;
    vec->elements[Y] = 2.75f;

    for (size_t i = 0; i < vec->cols; i++) {
        fprintf(stderr, "vec->elements[%zd] = %.2f\n", i, vec->elements[i]);
    }

    return 0;
}
