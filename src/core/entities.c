#include "entities.h"
#include <string.h>
#include "../logic/lua_bindings.h"
#include "raylib.h"
#include "resources.h"


// Глобальный массив врагов
Enemy enemies[32];

// Игрок
Player player;

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
void entities_init(void) {
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

    // движение игрока
    if (IsKeyDown(KEY_LEFT))  player.x -= player.speed * dt;
    if (IsKeyDown(KEY_RIGHT)) player.x += player.speed * dt;
    if (IsKeyDown(KEY_UP))    player.y -= player.speed * dt;
    if (IsKeyDown(KEY_DOWN))  player.y += player.speed * dt;

    // обновление врагов через Lua-паттерны
    for (int i = 0; i < 32; i++) {
        if (enemies[i].alive) {
            lua_enemy_update(&enemies[i], dt);
        }
    }
}

// ------------------------------------------------------------
// Рендер сущностей (Raylib)
// ------------------------------------------------------------
void entities_render(void) {
    // игрок
    DrawTexture(texPlayer, (int)player.x, (int)player.y, WHITE);

    // враги
    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        if (strcmp(enemies[i].type, "basic") == 0)
            DrawTexture(texEnemy1, (int)enemies[i].x, (int)enemies[i].y, WHITE);

        else if (strcmp(enemies[i].type, "fast") == 0)
            DrawTexture(texEnemy2, (int)enemies[i].x, (int)enemies[i].y, WHITE);

        else if (strcmp(enemies[i].type, "heavy") == 0)
            DrawTexture(texEnemy3, (int)enemies[i].x, (int)enemies[i].y, WHITE);

        else
            DrawTexture(texEnemy1, (int)enemies[i].x, (int)enemies[i].y, WHITE);
    }
}

// ------------------------------------------------------------
// Завершение работы
// ------------------------------------------------------------
void entities_shutdown(void) {
    // Пока ничего освобождать не нужно
}
