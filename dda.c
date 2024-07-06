/**
 * @file dda.c
 *
 * The Digital Differential Analyzer is used for line drawing
 * in computer graphics, providing a simple and efficient method
 * to render lines with antialiasing capabilities.
 */

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

// A structure representing a point
// NOTE: We should use struct SDL_FPoint and use a custom point
// for illustrative purposes.
typedef struct FloatingPoint {
    float x;
    float y;
} float_point_t;

// NOTE: Same for integer types, e.g. SDL_Point
typedef struct IntegerPoint {
    int x;
    int y;
} int_point_t;

// tolerance should be a default named parameter
// where tolerance defaults to an argument of 0.5f
float float_round(float value, float tolerance) {
    return (value > (floor(value) + tolerance)) ? ceil(value) : floor(value);
}

int int_max(int x, int y) {
    return abs(x) > abs(y) ? abs(x) : abs(y);
}

// Don't use globals! Globals are bad!
// Apply Separation of Concerns (SoC) instead.
int put_pixel(SDL_Renderer* renderer, int_point_t point) {
    // Draw a point on the current rendering target.
    // SDL_RenderDrawPoint() draws a single point.
    // If you want to draw multiple, use SDL_RenderDrawPoints() instead.
    // Note that the function signature differs from rendering individual
    // points and that this is just for illustrative purposes.
    // 0 on success or a negative error code on failure;
    // call SDL_GetError() for more information.
    return SDL_RenderDrawPoint(renderer, point.x, point.y);
}

void dda_line(SDL_Renderer* renderer, float_point_t p_start, float_point_t p_end) {
    int_point_t delta = {
        .y = p_end.y - p_start.y,
        .x = p_end.x - p_start.x,
    };

    int steps = int_max(delta.x, delta.y);

    float_point_t increment = {
        .y = delta.y / (float) steps,
        .x = delta.x / (float) steps,
    };

    int_point_t current = {
        .y = p_start.y,
        .x = p_start.x,
    };

    for (int i = 0; i <= steps; i++) {
        put_pixel(renderer, current);
        current.y += float_round(increment.y, 0.5f);
        current.x += float_round(increment.x, 0.5f);
    }
}

int main(int argc, char* argv[]) {
    // Points (0, 0) and (4, 5) are arbitrary and mostly for illustrative purposes
    float_point_t p_start = {0.0f, 0.0f}; // x_1, y_1
    float_point_t p_end   = {4.0f, 5.0f}; // x_2, y_2

    return 0;
}
