#include "game.h"
#include "entities.h"
#include "resources.h"
#include "collision.h"
#include "lua_bindings.h"
#include "raylib.h"

static float enemySpawnTimer = 0.0f;
static lua_State* L = NULL;

void Game_Init(void) {
    entities_init();
    Resources_Load();

    // правильная инициализация Lua
    L = lua_bind_init();
}

void Game_Update(float dt) {

    // обновление игрока — теперь в entities_update()
    // НЕ дублируем движение здесь

    // --- спавн врагов через таймер ---
    enemySpawnTimer += dt;
    if (enemySpawnTimer > 1.0f) {

        int r = GetRandomValue(0, 2);

        if (r == 0)
            entities_spawn_enemy("basic", GetRandomValue(50, 750), 0);
        else if (r == 1)
            entities_spawn_enemy("fast", GetRandomValue(50, 750), 0);
        else
            entities_spawn_enemy("heavy", GetRandomValue(50, 750), 0);

        enemySpawnTimer = 0.0f;
    }

    // --- обновление врагов через Lua ---
    for (int i = 0; i < 32; i++) {
        if (enemies[i].alive) {
            lua_enemy_update(&enemies[i], dt);
        }
    }

    // --- обновление сущностей (игрок + враги) ---
    entities_update(dt);

    // --- коллизии игрока с врагами ---
    Rectangle pRect = { player.x, player.y, 32, 32 };

    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        Rectangle eRect = { enemies[i].x, enemies[i].y, 32, 32 };

        if (CheckCollisionRecs(pRect, eRect)) {
            // смерть игрока
            player.x = 400;
            player.y = 550;
        }
    }
}

void Game_Draw(void) {
    // фон
    DrawRectangle(0, 0, 800, 600, DARKBLUE);

    // сущности
    entities_render();

    // HUD
    DrawText("Sky Defender", 10, 10, 20, WHITE);
}

void Game_Shutdown(void) {
    Resources_Unload();
    lua_bind_shutdown(L);
}
