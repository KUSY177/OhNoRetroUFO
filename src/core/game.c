#include "game.h"
#include "entities.h"
#include "input.h"


void game_init(SDL_Renderer* renderer) {
    entities_init();
    input_init();
}

void game_update(float dt) {
    input_update();
    entities_update(dt);
}

void game_render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    entities_render(renderer);

    SDL_RenderPresent(renderer);
}

void game_shutdown() {
    entities_shutdown();
}
