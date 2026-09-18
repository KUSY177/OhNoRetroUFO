#include "entities.h"
#include "resources.h"
#include "raylib.h"
#include <string.h>

// ------------------------------------------------------------
// Глобальные сущности
// ------------------------------------------------------------
Enemy enemies[32];
Player player;
Bullet bullets[64];
EnemyBullet enemyBullets[64];
Explosion explosions[64];

int playerScore = 0;

int gameStarted = 0;
int gameOver = 0;

float startBlinkTimer = 0.0f;
float invincibleTimer = 0.0f;

int isInvincible = 0;

int bgIndex = 0;
float bgTimer = 0.0f;

// бонус HP
int hpBonusShown = 0;
float hpBonusTimer = 0.0f;
float hpBonusX = 0.0f;
float hpBonusY = 0.0f;

// ------------------------------------------------------------
// Инициализация
// ------------------------------------------------------------
void entities_init(void) {
    memset(enemies, 0, sizeof(enemies));
    memset(bullets, 0, sizeof(bullets));
    memset(enemyBullets, 0, sizeof(enemyBullets));
    memset(explosions, 0, sizeof(explosions));

    player.x = 200;
    player.y = 400;
    player.speed = 200;
    player.hp = 6;
}

// ------------------------------------------------------------
// Спавн пули игрока
// ------------------------------------------------------------
void bullet_spawn(float x, float y) {
    for (int i = 0; i < 64; i++) {
        if (!bullets[i].alive) {
            bullets[i].alive = 1;
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].speed = 400;
            return;
        }
    }
}

// ------------------------------------------------------------
// Спавн пули врага
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
// Спавн врага
// ------------------------------------------------------------
void entities_spawn_enemy(const char* type, float x, float y) {
    // до старта игры враги не спавнятся
    if (!gameStarted) return;

    for (int i = 0; i < 32; i++) {
        if (!enemies[i].alive) {
            Enemy* e = &enemies[i];
            e->alive = 1;
            e->x = x;
            e->y = y;
            e->speed = 50;
            strcpy(e->type, type);
            e->shootTimer = 0;
            e->shootInterval = 1.0f;

            // HP по типу врага
            if (strcmp(type, "basic") == 0) {
                e->hp = 3;
            } else if (strcmp(type, "fast") == 0) {
                e->hp = 2;
            } else if (strcmp(type, "heavy") == 0) {
                e->hp = 4;
            } else {
                e->hp = 1; // дефолт
            }

            return;
        }
    }
}

// ------------------------------------------------------------
// Показ бонуса HP
// ------------------------------------------------------------
void show_hp_bonus(float x, float y) {
    hpBonusShown = 1;
    hpBonusTimer = 0.0f;
    hpBonusX = x;
    hpBonusY = y;
}

// ------------------------------------------------------------
// Спавн взрыва
// ------------------------------------------------------------
void spawn_explosion(float x, float y) {
    for (int i = 0; i < 64; i++) {
        if (!explosions[i].alive) {
            explosions[i].alive = 1;
            explosions[i].x = x;
            explosions[i].y = y;
            explosions[i].timer = 0.0f;
            explosions[i].frame = 0;
            return;
        }
    }
}

void entities_shutdown(void) {}
