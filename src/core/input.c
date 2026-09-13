#include <SDL.h>
#include "input.h"

static const Uint8* keys;

void input_init() {
    keys = SDL_GetKeyboardState(NULL);
}

void input_update() {
    SDL_PumpEvents();
}

int input_left()  { return keys[SDL_SCANCODE_LEFT]; }
int input_right() { return keys[SDL_SCANCODE_RIGHT]; }
int input_fire()  { return keys[SDL_SCANCODE_SPACE]; }
