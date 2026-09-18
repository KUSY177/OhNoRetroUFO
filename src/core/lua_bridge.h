#ifndef LUA_BRIDGE_H
#define LUA_BRIDGE_H

#include <lua.h>

// Инициализация Lua и загрузка level1.lua
lua_State* lua_init(void);

// Вызов update_wave(dt)
void lua_update(float dt);

// Завершение Lua
void lua_shutdown(void);

#endif
