/**
 * @file doom.c
 *
 * reference: https://yuriygeorgiev.com/2022/08/17/polygon-based-software-rendering-engine/
 */
#include <SDL2/SDL.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>

// This is fine for now. Maybe allow overrides in future?
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Globals are bad! Naughty, naughty 😿
const SDL_Renderer* renderer;

// NOTE: There's probably a cleaner way to implement this.
// I really don't like this, it's crude for sure.
void PutPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
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
    return 0;
}
