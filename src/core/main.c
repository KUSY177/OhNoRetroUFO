#include "renderer.h"
#include "game.h"
#include "raylib.h"

int main(void) {

    // Инициализация рендера и окна
    Renderer_Init(720, 720, "Oh No Retro UFO");

    // Инициализация игрового модуля
    Game_Init();

    // Главный игровой цикл
    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        Game_Update(dt);

        Renderer_Begin();
        Game_Draw();
        Renderer_End();
    }

    // Завершение игры и освобождение ресурсов
    Game_Shutdown();
    Renderer_Shutdown();

    return 0;
}
