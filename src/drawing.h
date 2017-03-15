#pragma once
#include <sdl2/sdl.h>
#include <SDL2_ttf\SDL_ttf.h>

SDL_Texture* createImage(const char* fileName, SDL_Renderer*);
void drawImage(int x, int y, SDL_Texture*, SDL_Renderer*);
void drawImage(int x, int y, int w, int h, SDL_Texture* texture, SDL_Renderer* renderer);
void initTextDrawing();
TTF_Font* createFont(const char* fileName);
void drawText(int x, int y, SDL_Renderer* renderer, TTF_Font* font, const char* text);


void drawTopMenu(SDL_Renderer* renderer, SDL_Texture* texture);