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

int main(int argc, char* argv[]) {
    // Points (2, 3) and (10, 8) are arbitrary and mostly for illustrative purposes
    float_point_t p_start = {2, 3};  // x_1, y_1
    float_point_t p_end   = {10, 8}; // x_2, y_2

    return 0;
}
