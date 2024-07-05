/**
 * @file simple.c
 *
 * A simple introductory program demonstrating basic usage of the
 * Simple DirectMedia Layer (SDL) library to create a window, handle events,
 * and quit gracefully when needed.
 */

#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize the SDL library
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create an application window
    SDL_Window* window = SDL_CreateWindow(
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
