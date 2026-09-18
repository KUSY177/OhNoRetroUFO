#include "lua_bridge.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>

static lua_State* L = NULL;

// ------------------------------------------------------------
// Инициализация Lua
// ------------------------------------------------------------
lua_State* lua_init(void)
{
    L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "assets/lua/level1.lua") != LUA_OK)
    {
        printf("Lua error (level1.lua): %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    return L;
}

// ------------------------------------------------------------
// Вызов update_wave(dt)
// ------------------------------------------------------------
void lua_update(float dt)
{
    if (!L) return;

    lua_getglobal(L, "update_wave");

    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1);
        return;
    }

    lua_pushnumber(L, dt);

    if (lua_pcall(L, 1, 0, 0) != LUA_OK)
    {
        printf("Lua error in update_wave(): %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}

// ------------------------------------------------------------
// Завершение Lua
// ------------------------------------------------------------
void lua_shutdown(void)
{
    if (L)
    {
        lua_close(L);
        L = NULL;
    }
}
