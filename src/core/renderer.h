#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"

void Renderer_Init(int width, int height, const char *title);
void Renderer_Begin(void);
void Renderer_End(void);
void Renderer_Shutdown(void);

#endif
