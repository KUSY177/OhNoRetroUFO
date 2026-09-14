#ifndef ENTITIES_H
#define ENTITIES_H

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

extern Enemy enemies[32];
extern Player player;
extern Bullet bullets[64];
extern EnemyBullet enemyBullets[64];
extern Explosion explosions[64];

extern int playerScore;

void entities_init(void);
void entities_update(float dt);
void entities_render(void);
void entities_shutdown(void);

void bullet_spawn(float x, float y);
void enemy_bullet_spawn(float x, float y, float dx, float dy);
void entities_spawn_enemy(const char* type, float x, float y);

#endif
