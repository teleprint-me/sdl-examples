/**
 * @file dda.c
 *
 * The Digital Differential Analyzer is used for line drawing
 * in computer graphics, providing a simple and efficient method
 * to render lines with antialiasing capabilities.
 */

#include <SDL2/SDL.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    float x;
    float y;
} float_point_t;

// Function to calculate the maximum of two integer values
int get_steps(float_point_t delta) {
    // Explicitly type cast to an integer so we can set the limit
    int x = (int) delta.x;
    int y = (int) delta.y;
    // Return the limit based on the point's axis with the greater absolute value
    return abs(x) > abs(y) ? abs(x) : abs(y);
}

void draw_line(SDL_Renderer* renderer, float_point_t start, float_point_t stop) {
    // Calculate delta values
    float_point_t delta = {
        .y = stop.y - start.y,
        .x = stop.x - start.x,
    };

    // Calculate the number of steps required
    int steps = get_steps(delta);

    // Calculate increment values
    float_point_t increment = {
        .y = delta.y / (float) steps,
        .x = delta.x / (float) steps,
    };

    // Initialize current point to start point
    float_point_t current = start;

    // Loop through and plot each point
    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPointF(renderer, current.x, current.y);
        current.y += increment.y;
        current.x += increment.x;
    }
}

int main(int argc, char* argv[]) {
    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO)) { // errors on truthy values
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // create sdl window
    SDL_Window* window = SDL_CreateWindow(
        "DDA Line Drawing",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );
    if (NULL == window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create sdl renderer
    SDL_Renderer* renderer
        = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (NULL == renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // set the background to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // clear the window
    SDL_RenderClear(renderer);

    // define start and end points here
    // Points (0, 0) and (4, 5) are arbitrary and mostly for illustrative purposes
    // we draw a line from the origin to the center of the window
    // origin = start = (0, 0)
    // center = stop  = (640 / 2, 480 / 2) = (320, 240)
    float_point_t start = {0.0f, 0.0f};     // x_1, y_1
    float_point_t stop  = {320.0f, 240.0f}; // x_2, y_2

    // set the line color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // draw the line using dda algo
    draw_line(renderer, start, stop);

    // present the renderer
    SDL_RenderPresent(renderer);

    // wait for a few seconds before quitting
    SDL_Delay(5000);

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
