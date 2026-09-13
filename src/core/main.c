#include "renderer.h"
#include "game.h"
#include "raylib.h"

int main(void) {
    Renderer_Init(800, 600, "Oh No Retro UFO");

    Game_Init();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Game_Update(dt);

        Renderer_Begin();
        Game_Draw();
        Renderer_End();
    }

    Game_Shutdown();
    Renderer_Shutdown();
    return 0;
}
