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

// NOTE: SDL has defined this as struct SDL_FPoint
// We use a custom point for illustrative purposes.
// A structure representing a floating point
typedef struct FloatingPoint {
    float x;
    float y;
} float_point_t;

// NOTE: SDL has defined this as struct SDL_Point
// We use a custom point for illustrative purposes.
// A structure representing an integer point
typedef struct IntegerPoint {
    int x;
    int y;
} int_point_t;

// Function to round float values based on a given tolerance
float float_round(float value, float tolerance) {
    return (value > (floor(value) + tolerance)) ? ceil(value) : floor(value);
}

// Function to calculate the maximum of two integer values
int int_max(int x, int y) {
    return abs(x) > abs(y) ? abs(x) : abs(y);
}

// Function to draw a pixel at a given point using SDL (integer coordinates)
int put_pixel(SDL_Renderer* renderer, float_point_t point) {
    // Cast the pixel coordinates from float to int
    int_point_t pixel = {
        .y = float_round(point.y, 0.5f),
        .x = float_round(point.x, 0.5f),
    };
    // The SDL_RenderDrawPoint only accepts integers
    // Otherwise we must use the SDL_RenderDrawPointF function instead
    // 0 on success or a negative error code on failure
    // call SDL_GetError() for more information
    return SDL_RenderDrawPoint(renderer, pixel.x, pixel.y);
}

// Function to draw a line using the DDA algorithm
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

    float_point_t current = {
        .y = p_start.y,
        .x = p_start.x,
    };

    for (int i = 0; i <= steps; i++) {
        put_pixel(renderer, current);
        current.y += increment.y;
        current.x += increment.x;
    }
}

int main(int argc, char* argv[]) {
    // Points (0, 0) and (4, 5) are arbitrary and mostly for illustrative purposes
    float_point_t p_start = {0.0f, 0.0f}; // x_1, y_1
    float_point_t p_end   = {4.0f, 5.0f}; // x_2, y_2

    return 0;
}
