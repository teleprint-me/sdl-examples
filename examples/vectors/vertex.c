/**
 * @file vertex.c
 */

#include "../../shape.h"
#include "../../vector.h"

#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;

    // Initialize the SDL library
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create an application window
    window = SDL_CreateWindow(
        "SDL Example",           /* Title of the Window */
        SDL_WINDOWPOS_UNDEFINED, /* Initial x position */
        SDL_WINDOWPOS_UNDEFINED, /* Initial y position */
        640,                     /* Width of window in pixels */
        480,                     /* Height of window in pixels */
        SDL_WINDOW_SHOWN         /* Flags - show the window when created */
    );

    // Check if the window was created successfully
    if (NULL == window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    size_t dimensions = 2; // 2-dimensional vector

    vector_t* vector    = vector_create(dimensions);
    vector->elements[X] = 120;
    vector->elements[Y] = 240;

    SDL_FPoint initial = {.x = 0.0f, .y = 0.0f}; // Initialize with some values
    SDL_Color  color   = {.r = 255, .g = 255, .b = 255, .a = 255};
    SDL_Vertex vertex  = {.color = color, .position = initial};

    // Event handling setup
    SDL_Event event;
    int       quit = 0;

    // Main loop
    while (0 == quit) {
        // Handle pending events
        while (1 == SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;

                // Add more event cases as needed
                default:
                    break;
            }
        }

        // Application logic goes here

        // Update window content and render it
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
