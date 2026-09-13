#include "timer.h"
#include "raylib.h"

float Timer_GetDelta(void) {
    return GetFrameTime();
}
