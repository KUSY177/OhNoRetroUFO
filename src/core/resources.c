#include "resources.h"
#include "raylib.h"
#include <stdio.h>

// ------------------------------------------------------------
// Текстуры
// ------------------------------------------------------------
Texture2D texPlayer;
Texture2D texEnemy1;
Texture2D texEnemy2;
Texture2D texEnemy3;

Texture2D texBoom[5];
Texture2D texHP;

Texture2D texBG1;
Texture2D texBG2;

// ------------------------------------------------------------
// Музыка
// ------------------------------------------------------------
Music musStart;
Music musBattle;
Music musLastHP;
Music musGameOver;

// ------------------------------------------------------------
// Загрузка ресурсов
// ------------------------------------------------------------
void resources_load(void) {

    // --- Текстуры игрока и врагов ---
    texPlayer = LoadTexture("assets/sprites/player.png");

    texEnemy1 = LoadTexture("assets/sprites/enemy1.png");
    texEnemy2 = LoadTexture("assets/sprites/enemy2.png");
    texEnemy3 = LoadTexture("assets/sprites/enemy3.png");

    // --- Взрывы ---
    texBoom[0] = LoadTexture("assets/sprites/boom1.png");
    texBoom[1] = LoadTexture("assets/sprites/boom2.png");
    texBoom[2] = LoadTexture("assets/sprites/boom3.png");
    texBoom[3] = LoadTexture("assets/sprites/boom4.png");
    texBoom[4] = LoadTexture("assets/sprites/boom5.png");

    // --- HP ---
    texHP = LoadTexture("assets/sprites/hp.png");

    // --- Фон ---
    texBG1 = LoadTexture("assets/sprites/space1.png");
    texBG2 = LoadTexture("assets/sprites/space2.png");

    // --- Музыка ---
    musStart    = LoadMusicStream("assets/sounds/start.mp3");
    musBattle   = LoadMusicStream("assets/sounds/battle.mp3");
    musLastHP   = LoadMusicStream("assets/sounds/lasthp.mp3");
    musGameOver = LoadMusicStream("assets/sounds/gameover.mp3");

    // --- Стартовая музыка ---
    PlayMusicStream(musStart);
}

// ------------------------------------------------------------
// Выгрузка ресурсов
// ------------------------------------------------------------
void resources_unload(void) {

    // --- Текстуры ---
    UnloadTexture(texPlayer);
    UnloadTexture(texEnemy1);
    UnloadTexture(texEnemy2);
    UnloadTexture(texEnemy3);

    for (int i = 0; i < 5; i++)
        UnloadTexture(texBoom[i]);

    UnloadTexture(texHP);

    UnloadTexture(texBG1);
    UnloadTexture(texBG2);

    // --- Музыка ---
    UnloadMusicStream(musStart);
    UnloadMusicStream(musBattle);
    UnloadMusicStream(musLastHP);
    UnloadMusicStream(musGameOver);
}
