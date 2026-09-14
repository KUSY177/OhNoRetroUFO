#include "collision.h"
#include "entities.h"
#include <string.h>
#include "../logic/lua_bindings.h"
#include "raylib.h"
#include "resources.h"

Enemy enemies[32];
Player player;
Bullet bullets[64];
EnemyBullet enemyBullets[64];
Explosion explosions[64];

int playerScore = 0;

static float bgTimer = 0.0f;
static int bgIndex = 0;

static float invincibleTimer = 0.0f;
static int isInvincible = 0;

static int gameOver = 0;

// Стартовый экран
static int gameStarted = 0;
static float startBlinkTimer = 0.0f;

// бонусное сердечко
static int   hpBonusShown = 0;
static float hpBonusTimer = 0.0f;
static float hpBonusX = 0.0f;
static float hpBonusY = 0.0f;

// ------------------------------------------------------------
// Взрыв
// ------------------------------------------------------------
void spawn_explosion(float x, float y) {
    for (int i = 0; i < 64; i++) {
        if (!explosions[i].alive) {
            explosions[i].alive = 1;
            explosions[i].x = x;
            explosions[i].y = y;
            explosions[i].timer = 0.0f;
            explosions[i].frame = GetRandomValue(0, 4);
            return;
        }
    }
}

// ------------------------------------------------------------
// Показ бонусного сердечка
// ------------------------------------------------------------
void show_hp_bonus(float x, float y) {
    hpBonusShown = 1;
    hpBonusTimer = 1.5f;
    hpBonusX = x;
    hpBonusY = y;
}

// ------------------------------------------------------------
// Спавн врага
// ------------------------------------------------------------
void entities_spawn_enemy(const char* type, float x, float y) {

    const float MIN_DIST = 40.0f;

    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        float dx = enemies[i].x - x;
        float dy = enemies[i].y - y;
        float distSq = dx*dx + dy*dy;

        if (distSq < MIN_DIST * MIN_DIST)
            return;
    }

    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) {

            Enemy* e = &enemies[i];

            e->alive = 1;
            e->x = x;
            e->y = y;
            e->speed = 100;
            strcpy(e->type, type);

            if (strcmp(type, "basic") == 0)
                e->hp = 3;
            else if (strcmp(type, "fast") == 0)
                e->hp = 2;
            else if (strcmp(type, "heavy") == 0)
                e->hp = 4;
            else
                e->hp = 1;

            e->shootTimer = 0.0f;
            e->shootInterval = GetRandomValue(80, 200) / 100.0f;

            return;
        }
    }
}

// ------------------------------------------------------------
// Пули игрока
// ------------------------------------------------------------
void bullet_spawn(float x, float y) {
    for (int i = 0; i < 64; i++) {
        if (!bullets[i].alive) {
            bullets[i].alive = 1;
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].speed = 450;
            return;
        }
    }
}

// ------------------------------------------------------------
// Пули врагов
// ------------------------------------------------------------
void enemy_bullet_spawn(float x, float y, float dx, float dy) {
    for (int i = 0; i < 64; i++) {
        if (!enemyBullets[i].alive) {
            enemyBullets[i].alive = 1;
            enemyBullets[i].x = x;
            enemyBullets[i].y = y;
            enemyBullets[i].dx = dx;
            enemyBullets[i].dy = dy;
            enemyBullets[i].speed = 200;
            return;
        }
    }
}

// ------------------------------------------------------------
// Инициализация
// ------------------------------------------------------------
void entities_init(void) {
    player.x = 400;
    player.y = 550;
    player.speed = 250;
    player.hp = 6;

    playerScore = 0;
    gameOver = 0;
    gameStarted = 0;

    hpBonusShown = 0;
    hpBonusTimer = 0.0f;

    memset(enemies, 0, sizeof(enemies));
    memset(bullets, 0, sizeof(bullets));
    memset(enemyBullets, 0, sizeof(enemyBullets));
    memset(explosions, 0, sizeof(explosions));
}

// ------------------------------------------------------------
// Обновление
// ------------------------------------------------------------
void entities_update(float dt) {

    // --- START SCREEN ---
    if (!gameStarted) {

        UpdateMusicStream(musStart);

        startBlinkTimer += dt;

        if (IsKeyPressed(KEY_SPACE) ||
            IsKeyPressed(KEY_ENTER) ||
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
            IsKeyPressed(KEY_Z) ||
            IsKeyPressed(KEY_X) ||
            IsKeyPressed(KEY_C)) {

            gameStarted = 1;

            StopMusicStream(musStart);
            PlayMusicStream(musBattle);
        }

        return;
    }

    if (gameOver) {
        UpdateMusicStream(musGameOver);
        return;
    }

    // музыка боя
    UpdateMusicStream(musBattle);

    // музыка последнего HP
    if (player.hp == 1 && !gameOver) {
        UpdateMusicStream(musLastHP);
    }

    bgTimer += dt;
    if (bgTimer > 1.0f) {
        bgTimer = 0.0f;
        bgIndex = 1 - bgIndex;
    }

    if (isInvincible) {
        invincibleTimer -= dt;
        if (invincibleTimer <= 0.0f) {
            isInvincible = 0;
        }
    }

    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) player.x -= player.speed * dt;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += player.speed * dt;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) player.y -= player.speed * dt;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) player.y += player.speed * dt;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) {
        bullet_spawn(player.x + texPlayer.width * 0.25f, player.y);
    }

    for (int i = 0; i < 64; i++) {
        if (!bullets[i].alive) continue;

        bullets[i].y -= bullets[i].speed * dt;

        if (bullets[i].y < -20)
            bullets[i].alive = 0;
    }

    for (int i = 0; i < 32; i++) {
        if (enemies[i].alive)
            lua_enemy_update(&enemies[i], dt);
    }

    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        Enemy* e = &enemies[i];

        e->shootTimer += dt;

        if (e->shootTimer > e->shootInterval) {

            if (strcmp(e->type, "basic") == 0) {
                enemy_bullet_spawn(e->x + 16, e->y + 32, 0.0f, 1.0f);
            }
            else if (strcmp(e->type, "heavy") == 0) {
                enemy_bullet_spawn(e->x + 16, e->y + 32, -0.3f, 1.0f);
                enemy_bullet_spawn(e->x + 16, e->y + 32,  0.0f, 1.0f);
                enemy_bullet_spawn(e->x + 16, e->y + 32,  0.3f, 1.0f);
            }

            e->shootInterval = GetRandomValue(80, 200) / 100.0f;
            e->shootTimer = 0.0f;
        }
    }

    for (int i = 0; i < 64; i++) {
        if (!enemyBullets[i].alive) continue;

        enemyBullets[i].x += enemyBullets[i].dx * enemyBullets[i].speed * dt;
        enemyBullets[i].y += enemyBullets[i].dy * enemyBullets[i].speed * dt;

        if (enemyBullets[i].y > 700)
            enemyBullets[i].alive = 0;
    }

    for (int b = 0; b < 64; b++) {
        if (!bullets[b].alive) continue;

        for (int e = 0; e < 32; e++) {
            if (!enemies[e].alive) continue;

            float enemyW = texEnemy1.width * 0.5f;
            float enemyH = texEnemy1.height * 0.5f;

            if (rects_intersect(
                    bullets[b].x, bullets[b].y, 4, 12,
                    enemies[e].x, enemies[e].y, enemyW, enemyH))
            {
                bullets[b].alive = 0;
                enemies[e].hp--;

                if (enemies[e].hp <= 0) {

                    if (strcmp(enemies[e].type, "basic") == 0)
                        playerScore += 1;
                    else if (strcmp(enemies[e].type, "fast") == 0)
                        playerScore += 2;
                    else if (strcmp(enemies[e].type, "heavy") == 0)
                        playerScore += 4;

                    // бонус HP каждые 50 очков
                    if (playerScore >= 50 && playerScore % 50 == 0) {
                        if (player.hp < 6) {
                            player.hp++;
                            show_hp_bonus(enemies[e].x, enemies[e].y);

                            if (player.hp > 1 && !gameOver) {
                                StopMusicStream(musLastHP);
                                PlayMusicStream(musBattle);
                            }
                        }
                    }

                    spawn_explosion(enemies[e].x, enemies[e].y);

                    enemies[e].alive = 0;
                }
            }
        }
    }
    for (int i = 0; i < 64; i++) {
        if (!enemyBullets[i].alive) continue;

        if (!isInvincible &&
            rects_intersect(
                enemyBullets[i].x, enemyBullets[i].y, 4, 12,
                player.x, player.y, 32, 32))
        {
            enemyBullets[i].alive = 0;

            if (!isInvincible) {
                player.hp--;

                isInvincible = 1;
                invincibleTimer = 2.0f;

                // --- LAST HP MUSIC ---
                if (player.hp == 1) {
                    StopMusicStream(musBattle);
                    PlayMusicStream(musLastHP);
                }
            }

            // --- GAME OVER ---
            if (player.hp <= 0) {
                gameOver = 1;

                StopMusicStream(musBattle);
                StopMusicStream(musLastHP);

                PlayMusicStream(musGameOver);
            }
        }
    }

    // обновление взрывов
    for (int i = 0; i < 64; i++) {
        if (!explosions[i].alive) continue;

        explosions[i].timer += dt;

        if (explosions[i].timer > 0.4f)
            explosions[i].alive = 0;
    }
}

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
        DrawTextureEx(texPlayer, (Vector2){player.x, player.y}, 0.0f, scalePlayer, WHITE);
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
    int heartSize = texHP.width * heartScale;
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

// ------------------------------------------------------------
// Завершение
// ------------------------------------------------------------
void entities_shutdown(void) {}
