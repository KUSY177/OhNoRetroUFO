#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct {
    float x, y;
    float speed;
} Player;

typedef struct {
    int alive;
    float x, y;
    char type[32];
} Enemy;

extern Player player;      // <--- ВАЖНО
extern Enemy enemies[32];

void entities_init(void);
void entities_update(float dt);
void entities_render(void);
void entities_spawn_enemy(const char* type, float x, float y);
void entities_shutdown(void);

#endif
