#include "resources.h"
#include "renderer.h"

SDL_Texture* tex_player = NULL;
SDL_Texture* tex_enemy  = NULL;

void resources_init(SDL_Renderer* renderer) {
    tex_player = load_texture(renderer, "assets/sprites/player.bmp");
    tex_enemy  = load_texture(renderer, "assets/sprites/enemy.bmp");
}

void resources_shutdown() {
    // SDL_DestroyTexture(tex_player);
    // SDL_DestroyTexture(tex_enemy);
}
