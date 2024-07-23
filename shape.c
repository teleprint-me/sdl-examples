/**
 * Copyright © 2024 Austin Berrio
 *
 * @file shape.c
 *
 * @brief Shapes
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 */

#include "shape.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Line segment operations
line_segment_t* create_line(size_t cols) {
    line_segment_t* line = (line_segment_t*) malloc(sizeof(line_segment_t));
    if (NULL == line) {
        fprintf(stderr, "Failed to allocate memory for line_segment_t.\n");
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

void free_line(line_segment_t* line) {
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

    polygon->vectices_max   = max_vertices;
    polygon->vertices_count = 0;    // Initialize count of vertices
    polygon->height         = 0.0f; // Default height
    polygon->distance       = 0.0f; // Default distance

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

    screen->vectices_max   = max_vertices;
    screen->vertices_count = 0;    // Initialize count to 0
    screen->depth          = 0.0f; // Default depth
    screen->id             = 0;    // Default identifier

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
