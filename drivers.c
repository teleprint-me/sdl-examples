#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    int n_displays = SDL_GetNumVideoDisplays();
    fprintf(stdout, "Discovered %d displays.\n", n_displays);

    int n_drivers = SDL_GetNumVideoDrivers();
    fprintf(stdout, "Discovered %d video drivers.\n", n_drivers);

    for (int n = 0; n < n_drivers; n++) {
        const char* driver_id = SDL_GetVideoDriver(n);
        fprintf(stdout, "Display driver %d: %s\n", n, driver_id);
    }

    SDL_Quit();

    return 0;
}
