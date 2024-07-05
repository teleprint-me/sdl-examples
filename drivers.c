/**
 * @file drivers.c
 *
 * Example program using Simple DirectMedia Layer (SDL) to iterate over
 * all available display drivers on a system.
 */

#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize SDL with video support (implies initialization of events)
    if (SDL_Init(SDL_INIT_VIDEO)) { // Init returns non-zero value on failure
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Get and print the number of available displays
    int n_displays = SDL_GetNumVideoDisplays();
    fprintf(stdout, "Discovered %d displays.\n", n_displays);

    // Get and print the number of available video drivers
    int n_drivers = SDL_GetNumVideoDrivers();
    fprintf(stdout, "Discovered %d video drivers.\n", n_drivers);

    // Iterate over and print the available video drivers
    for (int n = 0; n < n_drivers; n++) {
        // Get and print the name of the video driver
        const char* driver_id = SDL_GetVideoDriver(n);
        fprintf(stdout, "Video driver %d: %s\n", n, driver_id);
    }

    // Clean up and quit SDL
    SDL_Quit();

    return 0;
}
