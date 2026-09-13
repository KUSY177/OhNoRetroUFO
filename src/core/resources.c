#include "resources.h"

Texture2D texPlayer;
Texture2D texEnemy1;
Texture2D texEnemy2;
Texture2D texEnemy3;

void Resources_Load(void) {
    texPlayer = LoadTexture("assets/sprites/player.png");
    texEnemy1 = LoadTexture("assets/sprites/enemy1.png");
    texEnemy2 = LoadTexture("assets/sprites/enemy2.png");
    texEnemy3 = LoadTexture("assets/sprites/enemy3.png");
}

void Resources_Unload(void) {
    UnloadTexture(texPlayer);
    UnloadTexture(texEnemy1);
    UnloadTexture(texEnemy2);
    UnloadTexture(texEnemy3);
}
