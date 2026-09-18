#include "game.h"
#include "entities.h"
#include "resources.h"
#include "collision.h"
#include "lua_bindings.h"
#include "raylib.h"

static float enemySpawnTimer = 0.0f;
static lua_State* L = NULL;

// ------------------------------------------------------------
// Инициализация игры
// ------------------------------------------------------------
void Game_Init(void) {

    InitAudioDevice();      // если используешь звук
    resources_load();       // загрузка текстур
    entities_init();        // инициализация сущностей

    L = lua_bind_init();    // загрузка Lua (level1.lua, enemy_patterns.lua)
}

// ------------------------------------------------------------
// Обновление игры
// ------------------------------------------------------------
void Game_Update(float dt) {

    // --- спавн врагов через таймер ---
    enemySpawnTimer += dt;
    if (enemySpawnTimer > 1.0f) {

        int r = GetRandomValue(0, 2);

        if (r == 0)
            entities_spawn_enemy("basic", GetRandomValue(50, 670), 0);
        else if (r == 1)
            entities_spawn_enemy("fast", GetRandomValue(50, 670), 0);
        else
            entities_spawn_enemy("heavy", GetRandomValue(50, 670), 0);

        enemySpawnTimer = 0.0f;
    }

    // --- обновление волн из Lua ---
    lua_bind_update_wave(L, dt);

    // --- обновление сущностей ---
    entities_update(dt);

    // --- коллизии игрока с врагами ---
    Rectangle pRect = { player.x, player.y, 32, 32 };

    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        Rectangle eRect = { enemies[i].x, enemies[i].y, 32, 32 };

        if (CheckCollisionRecs(pRect, eRect)) {
            // простая смерть игрока — ресет позиции
            player.x = 400;
            player.y = 550;
        }
    }
}

// ------------------------------------------------------------
// Рендер игры
// ------------------------------------------------------------
void Game_Draw(void) {

    // фон очищается в main.c через ClearBackground()

    entities_render();  // рендер всех сущностей

    // HUD можно добавить здесь
}

// ------------------------------------------------------------
// Завершение игры
// ------------------------------------------------------------
void Game_Shutdown(void) {

    entities_shutdown();
    resources_unload();

    lua_bind_shutdown(L);

    CloseAudioDevice();     // если звук включён
}
