#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL.h>

void resources_init(SDL_Renderer* renderer);
void resources_shutdown();

SDL_Texture* tex_player;
SDL_Texture* tex_enemy;

#endif
