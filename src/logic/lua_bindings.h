#ifndef LUA_BINDINGS_H
#define LUA_BINDINGS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "../core/entities.h"

// Инициализация Lua и регистрация API
lua_State* lua_bind_init();

// Вызов обновления волны врагов
void lua_bind_update_wave(lua_State* L, float dt);

// Обновление конкретного врага через Lua-паттерны
void lua_enemy_update(Enemy* e, float dt);

// Завершение работы Lua
void lua_bind_shutdown(lua_State* L);

#endif
