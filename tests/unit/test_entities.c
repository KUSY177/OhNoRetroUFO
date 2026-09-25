#include "entities.h"
#include <assert.h>
#include <stdio.h>

extern Enemy enemies[32];
extern Bullet bullets[64];
extern int gameStarted;

int main(void) {
    entities_init();

    // До старта игры враги не должны спавниться
    gameStarted = 0;
    entities_spawn_enemy("basic", 100, 100);
    for (int i = 0; i < 32; i++)
        assert(enemies[i].alive == 0);

    // После старта — должны
    gameStarted = 1;
    entities_spawn_enemy("basic", 100, 100);

    int found = 0;
    for (int i = 0; i < 32; i++)
        if (enemies[i].alive) found = 1;

    assert(found == 1);

    // Тест пули
    bullet_spawn(50, 50);
    int bulletFound = 0;
    for (int i = 0; i < 64; i++)
        if (bullets[i].alive) bulletFound = 1;

    assert(bulletFound == 1);

    printf("test_entities: OK\n");
    return 0;
}
