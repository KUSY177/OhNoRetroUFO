#include "collision.h"
#include "raylib.h"

int collision_rect(float x1, float y1, float w1, float h1,
                   float x2, float y2, float w2, float h2) {
    Rectangle a = { x1, y1, w1, h1 };
    Rectangle b = { x2, y2, w2, h2 };
    return CheckCollisionRecs(a, b);
}
