#include "entities.h"
#include <string.h>

// Глобальный массив врагов (НЕ static — нужен для тестов)
Enemy enemies[32];

// Игрок
static Player player;

// ------------------------------------------------------------
// Создание врага (вызывается из Lua через lua_bindings.c)
// ------------------------------------------------------------
void entities_spawn_enemy(const char* type, float x, float y) {
    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) {
            enemies[i].alive = 1;
            enemies[i].x = x;
            enemies[i].y = y;

            strncpy(enemies[i].type, type, sizeof(enemies[i].type) - 1);
            enemies[i].type[sizeof(enemies[i].type) - 1] = '\0';
            break;
        }
    }
}

// ------------------------------------------------------------
// Инициализация сущностей
// ------------------------------------------------------------
void entities_init() {
    player.x = 400;
    player.y = 550;
    player.speed = 200;

    for (int i = 0; i < 32; i++) {
        enemies[i].alive = 0;
        enemies[i].x = 0;
        enemies[i].y = 0;
        enemies[i].type[0] = '\0';
    }
}

// ------------------------------------------------------------
// Обновление сущностей
// ------------------------------------------------------------
void entities_update(float dt) {
    // Логика движения игрока будет позже
    // Логика движения врагов — позже (через enemy_patterns.lua)
}

// ------------------------------------------------------------
// Рендер сущностей
// ------------------------------------------------------------
void entities_render(SDL_Renderer* renderer) {
    // Рендер игрока
    SDL_Rect p = { (int)player.x, (int)player.y, 32, 32 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &p);

    // Рендер врагов
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 32; i++) {
        if (enemies[i].alive) {
            SDL_Rect e = { (int)enemies[i].x, (int)enemies[i].y, 32, 32 };
            SDL_RenderFillRect(renderer, &e);
        }
    }
}

// ------------------------------------------------------------
// Завершение работы
// ------------------------------------------------------------
void entities_shutdown() {
    // Пока ничего освобождать не нужно
}
