#ifndef ENTITIES_H
#define ENTITIES_H

#include "raylib.h"

// ------------------------------------------------------------
// Структуры
// ------------------------------------------------------------
typedef struct {
    float x, y;
    float speed;
    int hp;
} Player;

typedef struct {
    float x, y;
    float speed;
    int alive;
} Bullet;

typedef struct {
    float x, y;
    float dx, dy;
    float speed;
    int alive;
} EnemyBullet;

typedef struct {
    float x, y;
    float speed;
    int alive;
    char type[16];
    int hp;

    float shootTimer;
    float shootInterval;
} Enemy;

typedef struct {
    float x, y;
    float timer;
    int alive;
    int frame;
} Explosion;

// ------------------------------------------------------------
// Глобальные массивы сущностей
// ------------------------------------------------------------
extern Enemy enemies[32];
extern Player player;
extern Bullet bullets[64];
extern EnemyBullet enemyBullets[64];
extern Explosion explosions[64];

// ------------------------------------------------------------
// Глобальные игровые переменные
// ------------------------------------------------------------
extern int playerScore;

// состояние игры
extern int gameStarted;
extern int gameOver;

// таймеры
extern float startBlinkTimer;
extern float invincibleTimer;

// флаги
extern int isInvincible;

// фон
extern int bgIndex;
extern float bgTimer;
extern Texture2D texBG1;
extern Texture2D texBG2;

// текстуры игрока и врагов
extern Texture2D texPlayer;
extern Texture2D texEnemy1;
extern Texture2D texEnemy2;
extern Texture2D texEnemy3;

// взрывы
extern Texture2D texBoom[5];

// бонус HP
extern int hpBonusShown;
extern float hpBonusTimer;
extern float hpBonusX;
extern float hpBonusY;
extern Texture2D texHP;

// ------------------------------------------------------------
// API
// ------------------------------------------------------------
void entities_init(void);
void entities_update(float dt);
void entities_render(void);
void entities_shutdown(void);
void show_hp_bonus(float x, float y);
void spawn_explosion(float x, float y);

void bullet_spawn(float x, float y);
void enemy_bullet_spawn(float x, float y, float dx, float dy);
void entities_spawn_enemy(const char* type, float x, float y);

#endif
