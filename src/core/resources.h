#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

// Глобальные текстуры
extern Texture2D texPlayer;
extern Texture2D texEnemy1;
extern Texture2D texEnemy2;
extern Texture2D texEnemy3;

void Resources_Load(void);
void Resources_Unload(void);

#endif
