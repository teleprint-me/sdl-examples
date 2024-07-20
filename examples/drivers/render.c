/**
 * @file examples/drivers/render.c
 *
 * Experiment with rendering
 */

#include <SDL2/SDL.h>

// a window is required to create a least one renderer object instance
SDL_Window* create_window(int width, int height) {
    SDL_Window* window = NULL;

    // Initialize the SDL library
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create an application window
    window = SDL_CreateWindow(
        "SDL Example",           /* Title of the Window */
        SDL_WINDOWPOS_UNDEFINED, /* Initial x position */
        SDL_WINDOWPOS_UNDEFINED, /* Initial y position */
        width,                   /* Width of window in pixels */
        height,                  /* Height of window in pixels */
        SDL_WINDOW_SHOWN         /* Flags - show the window when created */
    );

    // Check if the window was created successfully
    if (NULL == window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    return window;
}

int main(int argc, char* argv[]) {
    return 0;
}
