# Simple SDL Example

This example demonstrates how to create and run a simple application using the Simple DirectMedia Layer (SDL) library. It covers basic steps such as initializing the video subsystem, creating a window, handling events, updating content, rendering it, and cleaning up resources upon exiting.

## Building SDL Projects with CMake

Building SDL projects on multiple platforms can be streamlined using CMake, a cross-platform build system generator. Below is an example `CMakeLists.txt` file that can be used to set up a basic SDL project. This configuration supports automated building processes, making it easier to manage dependencies and platform-specific settings.

### CMake Configuration

```cmake
# SDL for education and practice
cmake_minimum_required(VERSION 3.17)
project("simple-example" LANGUAGES C)

# Set the C standard versions
set(CMAKE_C_STANDARD 17)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add SDL2 library for linking
add_link_options(-lSDL2)

# Add executable targets
add_executable(simple simple.c)
```

### Building the Project

1. Navigate to the project directory containing your `CMakeLists.txt` file.
2. Generate the build path and associated files with:

    ```sh
    cmake -B build
    ```

    This command will create the `build` directory if it does not already exist.

3. Compile the executables using:

    ```sh
    cmake --build build
    ```

## Code Explanation

This section provides an in-depth explanation of the simple SDL example code. 

### Full Source Code

```c
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create an application window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Example",           // Title of the window
        SDL_WINDOWPOS_UNDEFINED, // Initial x position
        SDL_WINDOWPOS_UNDEFINED, // Initial y position
        640,                     // Width of window in pixels
        480,                     // Height of window in pixels
        SDL_WINDOW_SHOWN         // Flags - show the window when created
    );

    // Check if the window was created successfully
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Event handling setup
    SDL_Event event;
    int quit = 0;

    // Main loop
    while (!quit) {
        // Handle pending events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
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
```

### SDL Initialization

- **Initialize the SDL library**
  - Call `SDL_Init(SDL_INIT_VIDEO)` to initialize the SDL library with video support.

    ```c
    // Initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
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

### Create Application Window

- **Define window properties**
  - Title: "SDL Example"
  - Initial position: `SDL_WINDOWPOS_UNDEFINED` for both x and y coordinates.
  - Dimensions: 640 pixels width and 480 pixels height.
  - Flags: `SDL_WINDOW_SHOWN` to display the window immediately.

    ```c
    // Create an application window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Example",           // Title of the window
        SDL_WINDOWPOS_UNDEFINED, // Initial x position
        SDL_WINDOWPOS_UNDEFINED, // Initial y position
        640,                     // Width of window in pixels
        480,                     // Height of window in pixels
        SDL_WINDOW_SHOWN         // Flags - show the window when created
    );
    ```

- **Check if the window was created successfully**

    ```c
    // Check if the window was created successfully
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    ```

### Event Handling Setup

- **Initialize the event loop**
  - Declare an `SDL_Event` variable to store event data.
  - Declare an integer variable `quit` and initialize it to 0 to control the main loop.

    ```c
    // Event handling setup
    SDL_Event event;
    int quit = 0;
    ```

### Main Loop

- **Handle pending user input**
  - Use `SDL_PollEvent(&event)` in a loop to poll for new SDL events.
  - Process each received event in a switch-case statement.

    ```c
    // Main loop
    while (!quit) {
        // Handle pending events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Application logic goes here

        // Update window content and render it
    }
    ```

  - **Check if `SDL_QUIT` has been triggered**
    - If `event.type == SDL_QUIT`, set the `quit` flag to 1 to exit the loop.

    ```c
    if (event.type == SDL_QUIT) {
        quit = 1;
    }
    ```

- **Application logic**
  - Placeholder for any application-specific logic that needs to be executed during each loop iteration.

### Cleanup

- **Destroy the application window**
  - Call `SDL_DestroyWindow(window)` to clean up the created window.

    ```c
    // Cleanup
    SDL_DestroyWindow(window);
    ```

- **Quit SDL**
  - Call `SDL_Quit()` to clean up all initialized SDL subsystems.

    ```c
    SDL_Quit();
    ```
