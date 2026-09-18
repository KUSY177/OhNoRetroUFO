#include "../core/entities.h"
#include "lua_bindings.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdio.h>
#include <string.h>

static lua_State* L = NULL;

// ------------------------------------------------------------
// C-функция для Lua: spawn_enemy(type, x, y)
// ------------------------------------------------------------
static int lua_spawn_enemy(lua_State* L) {
    const char* type = luaL_checkstring(L, 1);
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);

    entities_spawn_enemy(type, x, y);
    return 0;
}

// ------------------------------------------------------------
// Регистрация API
// ------------------------------------------------------------
static void register_api(lua_State* L) {
    lua_pushcfunction(L, lua_spawn_enemy);
    lua_setglobal(L, "spawn_enemy");
}

// ------------------------------------------------------------
// Инициализация Lua
// ------------------------------------------------------------
lua_State* lua_bind_init() {
    L = luaL_newstate();
    luaL_openlibs(L);

    register_api(L);

    // enemy_patterns.lua
    if (luaL_dofile(L, "assets/lua/enemy_patterns.lua") != LUA_OK) {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    // level1.lua
    if (luaL_dofile(L, "assets/lua/level1.lua") != LUA_OK) {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    return L;
}

// ------------------------------------------------------------
// Обновление волны врагов
// ------------------------------------------------------------
void lua_bind_update_wave(lua_State* L, float dt) {
    lua_getglobal(L, "update_wave");

    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    lua_pushnumber(L, dt);

    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}

// ------------------------------------------------------------
// Обновление врага через Lua-паттерн
// ------------------------------------------------------------
void lua_enemy_update(Enemy* e, float dt) {
    lua_getglobal(L, "enemy_update");

    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    // создаём таблицу e
    lua_newtable(L);

    lua_pushnumber(L, e->x);
    lua_setfield(L, -2, "x");

    lua_pushnumber(L, e->y);
    lua_setfield(L, -2, "y");

    lua_pushstring(L, e->type);
    lua_setfield(L, -2, "type");

    lua_pushnumber(L, e->speed);
    lua_setfield(L, -2, "speed");

    // аргументы: (таблица e, dt)
    lua_pushnumber(L, dt);

    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return;
    }

    // проверяем, что вернулась таблица
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    // читаем e.x
    lua_getfield(L, -1, "x");
    if (lua_isnumber(L, -1)) e->x = (float)lua_tonumber(L, -1);
    lua_pop(L, 1);

    // читаем e.y
    lua_getfield(L, -1, "y");
    if (lua_isnumber(L, -1)) e->y = (float)lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pop(L, 1);
}

// ------------------------------------------------------------
// Завершение работы Lua
// ------------------------------------------------------------
void lua_bind_shutdown(lua_State* L) {
    if (L)
        lua_close(L);
}
