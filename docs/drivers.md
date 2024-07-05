## SDL on Linux - Detecting Display Drivers

This example demonstrates how to create and run a simple application using the Simple DirectMedia Layer (SDL) library. It covers basic steps such as discovering the number of displays, discovering the number of display drivers, and identifying them for further use.

### Code Explanation

This section provides an in-depth explanation of the SDL drivers example code.

### Full Source Code

```c
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
```

### Explanation

#### SDL Initialization

- **Initialize the SDL library**
  - Call `SDL_Init(SDL_INIT_VIDEO)` to initialize the SDL library with video support.

    ```c
    // Initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO)) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }
    ```

  - Check if the initialization was successful by verifying the return value.

    ```c
    // Check if initialization was successful
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }
    ```

#### Getting the Number of Video Displays

- Call `SDL_GetNumVideoDisplays()` to get the number of available displays.
  - The function returns the number of available displays or a negative error code on failure.

    ```c
    int n_displays = SDL_GetNumVideoDisplays();
    fprintf(stdout, "Discovered %d displays.\n", n_displays);
    ```

#### Getting the Number of Video Drivers

- Call `SDL_GetNumVideoDrivers()` to get the number of available video drivers.
  - The function returns the number of available video drivers or a negative error code on failure.

    ```c
    int n_drivers = SDL_GetNumVideoDrivers();
    fprintf(stdout, "Discovered %d video drivers.\n", n_drivers);
    ```

#### Iterating Over Video Drivers

- Iterate over the available video drivers and print their names.
  - Use `SDL_GetVideoDriver(n)` to get the name of the driver at index `n`.

    ```c
    for (int n = 0; n < n_drivers; n++) {
        const char* driver_id = SDL_GetVideoDriver(n);
        fprintf(stdout, "Video driver %d: %s\n", n, driver_id);
    }
    ```

#### Cleanup

- Call `SDL_Quit()` to clean up and quit SDL.

    ```c
    SDL_Quit();
    ```

### Additional Notes

- To avoid repetitive explanations in every document, refer to `docs/simple.md` for detailed explanations on common tasks such as initialization and cleanup.
- Highlight any specific differences or unique aspects of the code in each document section.
