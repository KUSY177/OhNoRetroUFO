#include <SDL.h>
#include "timer.h"

static Uint32 last = 0;

float timer_delta() {
    Uint32 now = SDL_GetTicks();
    float dt = (now - last) / 1000.0f;
    last = now;
    return dt;
}
