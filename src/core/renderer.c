#include "renderer.h"

void Renderer_Init(int width, int height, const char *title) {
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

void Renderer_Begin(void) {
    BeginDrawing();
    ClearBackground(BLUE); // очищает весь экран
}

void Renderer_End(void) {
    EndDrawing();
}

void Renderer_Shutdown(void) {
    CloseWindow();
}
