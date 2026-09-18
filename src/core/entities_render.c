#include "entities.h"
#include "resources.h"
#include "raylib.h"
#include <string.h>

// ------------------------------------------------------------
// Рендер
// ------------------------------------------------------------
void entities_render(void) {

    Texture2D bg = (bgIndex == 0 ? texBG1 : texBG2);

    DrawTexturePro(
        bg,
        (Rectangle){ 0, 0, bg.width, bg.height },
        (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    // --- START SCREEN ---
    if (!gameStarted) {

        const char* title = "SKY DEFENDER";
        const char* press = "PRESS ANY KEY TO START";

        int tw = MeasureText(title, 70);
        int pw = MeasureText(press, 30);

        DrawText(title, screenW/2 - tw/2, screenH/2 - 120, 70, YELLOW);

        if (((int)(startBlinkTimer * 2)) % 2 == 0) {
            DrawText(press, screenW/2 - pw/2, screenH/2 + 20, 30, WHITE);
        }

        return;
    }

    // --- GAME OVER ---
    if (gameOver) {

        const char* text1 = "GAME OVER";
        const char* text2 = TextFormat("Score: %d", playerScore);

        int t1w = MeasureText(text1, 60);
        int t2w = MeasureText(text2, 40);

        DrawText(text1, screenW/2 - t1w/2, screenH/2 - 60, 60, RED);
        DrawText(text2, screenW/2 - t2w/2, screenH/2 + 10, 40, YELLOW);

        return;
    }

    float scalePlayer = 0.5f;
    float scaleEnemy  = 0.5f;

    int drawPlayer = 1;

    if (isInvincible) {
        if (((int)(invincibleTimer * 10)) % 2 == 0)
            drawPlayer = 0;
    }

    if (drawPlayer) {
        DrawTextureEx(texPlayer, (Vector2){ player.x, player.y }, 0.0f, scalePlayer, WHITE);
    }

    // враги
    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        Vector2 pos = { enemies[i].x, enemies[i].y };

        if (strcmp(enemies[i].type, "basic") == 0)
            DrawTextureEx(texEnemy1, pos, 0.0f, scaleEnemy, WHITE);
        else if (strcmp(enemies[i].type, "fast") == 0)
            DrawTextureEx(texEnemy2, pos, 0.0f, scaleEnemy, WHITE);
        else if (strcmp(enemies[i].type, "heavy") == 0)
            DrawTextureEx(texEnemy3, pos, 0.0f, scaleEnemy, WHITE);
    }

    // пули игрока
    for (int i = 0; i < 64; i++) {
        if (bullets[i].alive)
            DrawRectangle(bullets[i].x, bullets[i].y, 4, 12, YELLOW);
    }

    // пули врагов
    for (int i = 0; i < 64; i++) {
        if (enemyBullets[i].alive)
            DrawRectangle(enemyBullets[i].x, enemyBullets[i].y, 4, 12, RED);
    }

    // взрывы
    for (int i = 0; i < 64; i++) {
        if (!explosions[i].alive) continue;

        DrawTexture(
            texBoom[explosions[i].frame],
            explosions[i].x,
            explosions[i].y,
            WHITE
        );
    }

    // --- бонусное сердечко ---
    if (hpBonusShown) {
        hpBonusTimer -= GetFrameTime();
        if (hpBonusTimer > 0.0f) {
            DrawTextureEx(
                texHP,
                (Vector2){ hpBonusX, hpBonusY },
                0.0f,
                0.05f,
                WHITE
            );
        } else {
            hpBonusShown = 0;
        }
    }

    // HP сердечки
    float heartScale = 0.03f;
    int heartSize = (int)(texHP.width * heartScale);
    int spacing = 6;

    for (int i = 0; i < player.hp; i++) {
        int x = screenW - (heartSize + spacing) * (i + 1);
        int y = screenH - heartSize - 10;

        DrawTextureEx(
            texHP,
            (Vector2){ x, y },
            0.0f,
            heartScale,
            WHITE
        );
    }

    DrawText(TextFormat("Score: %d", playerScore), 10, screenH - 40, 28, YELLOW);
}
