#pragma once
#include <sdl2/sdl.h>

SDL_Renderer* showWindow(int x, int y, int w, int h, bool fullScreen);
void disposeWindow();
void pollWindowEvent();
void clearBackBuffer();
void displayBackBuffer();