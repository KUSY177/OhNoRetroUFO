#ifndef ENTITIES_H
#define ENTITIES_H

#include <SDL.h>

typedef struct {
    float x, y;
    float speed;
} Player;

typedef struct {
    float x, y;
    int alive;
    char type[16];
} Enemy;

// Глобальный массив врагов — нужен для тестов
extern Enemy enemies[32];

// API
void entities_init();
void entities_update(float dt);
void entities_render(SDL_Renderer* renderer);
void entities_shutdown();

// Lua вызывает эту функцию
void entities_spawn_enemy(const char* type, float x, float y);

#endif
