#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

// Текстуры
extern Texture2D texPlayer;
extern Texture2D texEnemy1;
extern Texture2D texEnemy2;
extern Texture2D texEnemy3;

extern Texture2D texBoom[5];
extern Texture2D texHP;

extern Texture2D texBG1;
extern Texture2D texBG2;

// Музыка
extern Music musStart;
extern Music musBattle;
extern Music musLastHP;
extern Music musGameOver;

// API
void resources_load(void);
void resources_unload(void);

#endif
