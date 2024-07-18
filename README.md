# SDL Examples

This repository contains examples of using SDL2 for multimedia, gaming, and machine learning
development. It serves as a playground for experimenting with C, SDL, and Vulkan for fun and profit.

## Goals

The primary goal of this project is to apply mathematics pragmatically to practical software
applications while documenting any progress. The documentation can be found within the `docs/`
directory.

## Scope

- All source code is written in pure C.
- Libraries are used only when absolutely necessary.
- Dependencies are kept to a minimum. The primary dependencies are:
  - clang
  - cmake
  - SDL
  - Vulkan

## Supported Platforms

The following platforms are recommended for this project:

- **EndeavourOS:** Recommended for beginners, enthusiasts, and power users. It is a user-friendly
  Arch-based derivative.
- **Arch Linux:** Officially supported for adept and experienced users. This is not recommended for
  beginners.
- **Debian:** A good alternative to Ubuntu, suitable for various levels of users and use cases.

## Prerequisites

Ensure you have the following libraries installed on your Arch Linux system:

- SDL2 and related libraries:

  ```sh
  sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
  ```

- CMake for building the project:

  ```sh
  sudo pacman -S cmake clang
  ```

## Project Structure

The project has the following structure:

```
.
├── build
├── CMakeLists.txt
├── docs
├── examples
├── LICENSE
├── NOTE.md
├── src
├── test
├── README.md
├── precision.c
├── precision.h
├── primitives.c
├── primitives.h
├── vector.c
└── vector.h

6 directories, 10 files
```

- `CMakeLists.txt`: The CMake configuration file.
- `docs`: Documentation providing in-depth information, references, and guides.
- `examples`: Isolated/independent examples.
- `src`: The primary source code (currently empty).
- `test`: Tests for `src` (currently empty).

Note that the directory structure may evolve over time.

## Building the Project

1. **Clone the repository:**

   ```sh
   git clone https://github.com/teleprint-me/sdl-examples.git
   cd sdl-examples
   ```

2. **Create the build files using CMake:**

   ```sh
   cmake -B build -DCMAKE_BUILD_TYPE=Debug
   ```

3. **Build the project:**

   ```sh
   cmake --build build -j 8
   ```

4. **Run the executable:**
   ```sh
   ./build/simple
   ```

See `docs/building.md` for more information.

## Example Code

Here's a simple example named `simple.c`:

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

## License

This repository and its contents are licensed under the AGPL license. All respective and legally
applicable copyrights apply.
