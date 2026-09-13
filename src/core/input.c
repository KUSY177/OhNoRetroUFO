#include "input.h"
#include "raylib.h"

bool Input_ShouldQuit(void) {
    return WindowShouldClose();
}

bool Input_IsKeyDown(int key) {
    return IsKeyDown(key);
}
