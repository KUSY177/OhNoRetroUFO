#include "lua_bindings.h"
#include "../core/entities.h"

// --- C-функции, доступные из Lua ---

// spawn_enemy(type, x, y)
static int l_spawn_enemy(lua_State* L) {
    const char* type = luaL_checkstring(L, 1);
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);

    // Простейшая логика: создаём врага в entities.c
    entities_spawn_enemy(type, x, y);
    return 0;
}

// --- Регистрация API ---

static void register_api(lua_State* L) {
    lua_pushcfunction(L, l_spawn_enemy);
    lua_setglobal(L, "spawn_enemy");
}

// --- Публичные функции ---

lua_State* lua_bind_init() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    register_api(L);

    // Загружаем основной скрипт уровня
    if (luaL_dofile(L, "src/lua/level1.lua") != 0) {
        const char* err = lua_tostring(L, -1);
        printf("Lua error: %s\n", err);
        lua_pop(L, 1);
    }

    return L;
}

void lua_bind_update_wave(lua_State* L, float dt) {
    lua_getglobal(L, "update_wave");
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    lua_pushnumber(L, dt);
    if (lua_pcall(L, 1, 0, 0) != 0) {
        const char* err = lua_tostring(L, -1);
        printf("Lua error in update_wave: %s\n", err);
        lua_pop(L, 1);
    }
}

void lua_bind_shutdown(lua_State* L) {
    if (L)
        lua_close(L);
}
