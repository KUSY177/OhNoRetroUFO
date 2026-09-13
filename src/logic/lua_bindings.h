#ifndef LUA_BINDINGS_H
#define LUA_BINDINGS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Инициализация Lua и регистрация API
lua_State* lua_bind_init();

// Вызов обновления волны врагов
void lua_bind_update_wave(lua_State* L, float dt);

// Завершение работы Lua
void lua_bind_shutdown(lua_State* L);

#endif
