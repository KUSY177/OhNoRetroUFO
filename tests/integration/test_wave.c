#include <assert.h>
#include <stdio.h>

#include "../../src/logic/lua_bindings.h"
#include "../../src/core/entities.h"

// Вспомогательная функция: считаем живых врагов
static int count_enemies() {
    int count = 0;
    extern Enemy enemies[32]; // если enemies static — вынеси в entities.h
    for (int i = 0; i < 32; i++)
        if (enemies[i].alive)
            count++;
    return count;
}

int main() {
    lua_State* L = lua_bind_init();
    entities_init();

    // До вызова Lua врагов быть не должно
    assert(count_enemies() == 0);

    // Вызываем update_wave(dt)
    lua_bind_update_wave(L, 1.5f);  // dt > 1.0 → первая волна

    // Теперь должны появиться враги
    int after = count_enemies();
    printf("Enemies after wave: %d\n", after);

    assert(after > 0);

    lua_bind_shutdown(L);
    entities_shutdown();

    printf("test_wave passed\n");
    return 0;
}
