/**
 * Copyright (c) 2024 Austin Berrio
 *
 * @file examples/lines/dda.c
 *
 * The Digital Differential Analyzer is used for line drawing
 * in computer graphics, providing a simple and efficient method
 * to render lines.
 */

#include <SDL2/SDL.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @struct SDL_FPoint
 *
 * @include SDL_FPoint is defined in include/SDL_rect.h
 *
 * The `SDL_FPoint` struct is used to store floating point coordinates.
 * - x: Floating point value representing the X coordinate of a point
 * - y: Floating point value representing the Y coordinate of a point
 *
 * typedef struct {
 *     float x;
 *     float y;
 * } SDL_FPoint;
 */

/**
 * @brief Calculate the maximum of two integer values.
 *
 * @param delta The difference between the start and end points.
 * @return The maximum absolute value of the differences in x and y coordinates.
 */
int calculate_steps(SDL_FPoint delta) {
    // Explicitly typecast and map the 32-bit float to a 32-bit integer so we can set the limit.
    int32_t x = (int32_t) delta.x;
    int32_t y = (int32_t) delta.y;
    // Return the limit based on the point's axis with the greater absolute value
    return abs(x) > abs(y) ? abs(x) : abs(y);
}

/**
 * @brief Draws a line using the Digital Differential Analyzer (DDA) algorithm.
 *
 * @param renderer The SDL_Renderer to draw on.
 * @param start The starting point of the line.
 * @param end The ending point of the line.
 */
void draw_line(SDL_Renderer* renderer, SDL_FPoint start, SDL_FPoint end) {
    // Calculate delta values
    SDL_FPoint delta = {
        .y = end.y - start.y,
        .x = end.x - start.x,
    };

    // Calculate the number of steps required
    int steps = calculate_steps(delta);

    // Calculate increment values
    SDL_FPoint increment = {
        .y = delta.y / (float) steps,
        .x = delta.x / (float) steps,
    };

    // Initialize current point to start point
    SDL_FPoint current = start;

    // Loop through and plot each point
    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPointF(renderer, current.x, current.y);
        current.y += increment.y;
        current.x += increment.x;
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // errors on truthy values
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow(
        "DDA Line Drawing",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );
    if (NULL == window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create SDL renderer
    SDL_Renderer* renderer
        = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (NULL == renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Set the background to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // Clear the window
    SDL_RenderClear(renderer);

    // Define start and end points here
    SDL_FPoint start = {0.0f, 0.0f};     // x_1, y_1
    SDL_FPoint end   = {320.0f, 240.0f}; // x_2, y_2

    // Set the line color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Draw the line using DDA algorithm
    draw_line(renderer, start, end);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Wait for a few seconds before quitting
    SDL_Delay(5000);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
