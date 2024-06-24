# SDL Examples

This repository contains examples of using SDL2 for multimedia and game development.

## Prerequisites

Ensure you have the following installed on your Arch Linux system:

- SDL2 and related libraries:
  ```sh
  sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
  ```

- CMake for building the project:
  ```sh
  sudo pacman -S cmake
  ```

## Project Structure

The project has the following structure:

```
.
├── CMakeLists.txt
└── simple.c
```

- `CMakeLists.txt`: The CMake configuration file.
- `simple.c`: A simple SDL2 example program.

## Building the Project

1. **Clone the repository:**
    ```sh
    git clone https://github.com/yourusername/sdl-examples.git
    cd sdl-examples
    ```

2. **Create the build files using CMake:**
    ```sh
    cmake -B build -DCMAKE_BUILD_TYPE=Debug
    ```

    This command generates the necessary build files in the `build` directory and sets the build type to `Debug`. You can change `Debug` to `Release` for an optimized build.

3. **Build the project:**
    ```sh
    cmake --build build -j 8
    ```

    This command compiles the code using 8 parallel jobs (you can adjust the number based on your CPU cores).

4. **Run the executable:**
    ```sh
    ./build/simple
    ```

    This runs the `simple` executable that was created in the `build` directory.

## Example Code

Here is the example code in `simple.c`:

```c
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL Example",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```
