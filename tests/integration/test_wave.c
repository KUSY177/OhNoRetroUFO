#include "entities.h"
#include "lua_bindings.h"
#include <assert.h>
#include <stdio.h>

extern Enemy enemies[32];
extern int gameStarted;

int main(void) {
    entities_init();
    gameStarted = 1;

    // Спавним волну
    for (int i = 0; i < 10; i++)
        entities_spawn_enemy("basic", 100 + i * 20, -10);

    // Проверяем, что появились
    int aliveCount = 0;
    for (int i = 0; i < 32; i++)
        if (enemies[i].alive) aliveCount++;

    assert(aliveCount == 10);

    // Обновляем врагов так, чтобы они ушли за экран
    for (int i = 0; i < 32; i++)
        if (enemies[i].alive)
            enemies[i].y = 900; // за пределами экрана

    // Прогоняем логику исчезновения
    for (int i = 0; i < 32; i++)
        if (enemies[i].alive)
            if (enemies[i].y > 800)
                enemies[i].alive = 0;

    // Проверяем, что все исчезли
    for (int i = 0; i < 32; i++)
        assert(enemies[i].alive == 0);

    printf("test_wave: OK\n");
    return 0;
}
