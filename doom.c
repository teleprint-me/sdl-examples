/**
 * @file doom.c
 *
 * reference: https://yuriygeorgiev.com/2022/08/17/polygon-based-software-rendering-engine/
 */

#include "primitives.h"

#include <SDL2/SDL.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>

// This is fine for now. Maybe allow overrides in future?
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Globals are bad! Naughty, naughty 😿
const SDL_Renderer* renderer; // tracks rendering state

// NOTE: There's probably a cleaner way to implement this.
// I really don't like this, it's crude for sure.
// author claims we're doing this from scratch and then
// immediately relies upon the api making this redundant.
// there seems to be no underlying exposure and would require
// inspection of the underlying source code.
void put_pixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT) {
        return;
    }

    if (x < 0 || y < 0) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

int main(int argc, char* argv[]) {
    // initialize events
    SDL_Init(SDL_INIT_VIDEO);

    // initialize window
    SDL_Window* window = SDL_CreateWindow(
        "3D Poly Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN // window is visible
    );

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
