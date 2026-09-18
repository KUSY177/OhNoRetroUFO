#include "update.h"
#include "entities.h"
#include "resources.h"
#include "collision.h"
#include "lua_bindings.h"
#include "raylib.h"
#include <string.h>

void entities_update(float dt) {

    if (!gameStarted) {
        UpdateMusicStream(musStart);

        startBlinkTimer += dt;

        if (IsKeyPressed(KEY_SPACE) ||
            IsKeyPressed(KEY_ENTER) ||
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
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

    UpdateMusicStream(musBattle);

    if (player.hp == 1)
        UpdateMusicStream(musLastHP);

    bgTimer += dt;
    if (bgTimer > 1.0f) {
        bgTimer = 0.0f;
        bgIndex = 1 - bgIndex;
    }

    if (isInvincible) {
        invincibleTimer -= dt;
        if (invincibleTimer <= 0.0f)
            isInvincible = 0;
    }

    // --- управление игроком (стрелки + WASD) ---
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) player.x -= player.speed * dt;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += player.speed * dt;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) player.y -= player.speed * dt;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) player.y += player.speed * dt;

    // --- стрельба игрока (ЛКМ + SPACE, одиночный выстрел) ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE))
        bullet_spawn(player.x + texPlayer.width * 0.25f, player.y);

    // --- пули игрока ---
    for (int i = 0; i < 64; i++) {
        if (!bullets[i].alive) continue;
        bullets[i].y -= bullets[i].speed * dt;
        if (bullets[i].y < -20)
            bullets[i].alive = 0;
    }

    // --- враги ---
    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        lua_enemy_update(&enemies[i], dt);

        // исчезновение за экраном
        if (enemies[i].y > GetScreenHeight() + 50 ||
            enemies[i].x < -50 ||
            enemies[i].x > GetScreenWidth() + 50)
        {
            enemies[i].alive = 0;
        }
    }

    // --- стрельба врагов ---
    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) continue;

        Enemy* e = &enemies[i];
        e->shootTimer += dt;

        if (e->shootTimer > e->shootInterval) {
            enemy_bullet_spawn(e->x + 16, e->y + 32, 0, 1);
            e->shootInterval = GetRandomValue(80, 200) / 100.0f;
            e->shootTimer = 0.0f;
        }
    }

    // --- пули врагов ---
    for (int i = 0; i < 64; i++) {
        if (!enemyBullets[i].alive) continue;

        enemyBullets[i].x += enemyBullets[i].dx * enemyBullets[i].speed * dt;
        enemyBullets[i].y += enemyBullets[i].dy * enemyBullets[i].speed * dt;

        if (enemyBullets[i].y > GetScreenHeight() + 20)
            enemyBullets[i].alive = 0;
    }

    // --- коллизии пуль игрока с врагами ---
    for (int b = 0; b < 64; b++) {
        if (!bullets[b].alive) continue;

        for (int e = 0; e < 32; e++) {
            if (!enemies[e].alive) continue;

            if (rects_intersect(
                    bullets[b].x, bullets[b].y, 4, 12,
                    enemies[e].x, enemies[e].y,
                    texEnemy1.width * 0.5f,
                    texEnemy1.height * 0.5f))
            {
                bullets[b].alive = 0;
                enemies[e].hp--;

                if (enemies[e].hp <= 0) {
                    enemies[e].alive = 0;

                    // очки по типу врага
                    if (strcmp(enemies[e].type, "basic") == 0) {
                        playerScore += 1;
                    } else if (strcmp(enemies[e].type, "fast") == 0) {
                        playerScore += 2;
                    } else if (strcmp(enemies[e].type, "heavy") == 0) {
                        playerScore += 4;
                    } else {
                        playerScore += 1;
                    }

                    // бонус HP каждые 50 очков
                    static int lastScoreHP = 0;
                    if (playerScore - lastScoreHP >= 50 && player.hp < 6) {
                        player.hp++;
                        lastScoreHP = playerScore;
                        show_hp_bonus(enemies[e].x, enemies[e].y);
                    }

                    spawn_explosion(enemies[e].x, enemies[e].y);
                }
            }
        }
    }

    // --- коллизии пуль врагов с игроком ---
    for (int i = 0; i < 64; i++) {
        if (!enemyBullets[i].alive) continue;

        if (!isInvincible &&
            rects_intersect(
                enemyBullets[i].x, enemyBullets[i].y, 4, 12,
                player.x, player.y, 32, 32))
        {
            enemyBullets[i].alive = 0;

            player.hp--;
            isInvincible = 1;
            invincibleTimer = 2.0f;

            if (player.hp == 1) {
                StopMusicStream(musBattle);
                PlayMusicStream(musLastHP);
            }

            if (player.hp <= 0) {
                gameOver = 1;
                StopMusicStream(musBattle);
                StopMusicStream(musLastHP);
                PlayMusicStream(musGameOver);
            }
        }
    }

    // --- взрывы ---
    for (int i = 0; i < 64; i++) {
        if (!explosions[i].alive) continue;

        explosions[i].timer += dt;

        if (explosions[i].timer > 0.4f) {
            explosions[i].alive = 0;
        }
    }
}
