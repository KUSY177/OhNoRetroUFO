#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "lua_bridge.h"

static lua_State* L = NULL;

void lua_init() {
    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "assets/lua/level1.lua");
}

void lua_update(float dt) {
    lua_getglobal(L, "update_wave");
    lua_pushnumber(L, dt);
    lua_call(L, 1, 0);
}

void lua_shutdown() {
    lua_close(L);
}
