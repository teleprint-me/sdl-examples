/**
 * @file examples/drivers/render.c
 *
 * Experiment with rendering
 */

#include <SDL2/SDL.h>

// a window is required to create a least one renderer object instance
SDL_Window* create_window(char* title, int width, int height) {
    SDL_Window* window = NULL;

    // Initialize the SDL library
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return NULL;
    }

    // Create an application window
    window = SDL_CreateWindow(
        title,                   /* Title of the Window */
        SDL_WINDOWPOS_UNDEFINED, /* Initial x position */
        SDL_WINDOWPOS_UNDEFINED, /* Initial y position */
        width,                   /* Width of window in pixels */
        height,                  /* Height of window in pixels */
        SDL_WINDOW_SHOWN         /* Flags - show the window when created */
    );

    // Check if the window was created successfully
    if (NULL == window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    return window;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = create_window("SDL Renderer Example", 640, 480);
    if (NULL == window) {
        return 1;
    }

    SDL_Renderer* renderer
        = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (NULL == renderer) {
        fprintf(stderr, "Error initializing SDL Renderer: %s\n", SDL_GetError());
        return 1;
    }

    // set the background color and clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // set the object color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // set the object
    SDL_Rect rect = {.x = 10, .y = 10, .w = 200, .h = 200};
    // draw the object to the screen
    SDL_RenderFillRect(renderer, &rect);
    // update the screen
    SDL_RenderPresent(renderer);

    // create a event object
    SDL_Event e;
    // set the event life cycle
    int       quit = 0;

    // loop over events
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                quit = 1;
            }
        }
    }

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
