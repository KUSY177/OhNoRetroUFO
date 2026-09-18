#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Инициализация модуля ввода
void Input_Init(void);

// Обработка событий (если нужно)
void Input_ProcessEvent(void);

// Обновление состояния клавиш и мыши
void Input_Update(void);

// Проверка выхода
bool Input_ShouldQuit(void);

// Клавиша удерживается
bool Input_IsKeyDown(int key);

// Клавиша нажата в этом кадре (edge trigger)
bool Input_IsKeyPressed(int key);

// Кнопка мыши нажата в этом кадре
bool Input_IsMousePressed(int button);

#endif
