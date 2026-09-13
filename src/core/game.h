#ifndef GAME_H
#define GAME_H

#include <SDL.h>

void game_init(SDL_Renderer* renderer);
void game_update(float dt);
void game_render(SDL_Renderer* renderer);
void game_shutdown();

#endif
