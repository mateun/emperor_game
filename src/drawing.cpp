#include "drawing.h"
#include <vector>
#include <SDL2_ttf\SDL_ttf.h>

static SDL_Surface* surface;

SDL_Texture* createImage(const char* fileName, SDL_Renderer* renderer) {
	surface = SDL_LoadBMP(fileName);
	if (!surface) {
		SDL_Log("Error: could not load bmp file %s %s", fileName, SDL_GetError());
		return 0;
	}

	SDL_SetColorKey(surface, SDL_TRUE, 0xffffffff);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log("Error: could not create texture %s", SDL_GetError());
		return 0;
	}

	SDL_FreeSurface(surface);
	return texture;
}

void drawImage(int x, int y, SDL_Texture* texture, SDL_Renderer* renderer) {
	SDL_Rect tgt;
	tgt.x = x;
	tgt.y = y;
	tgt.w = 32;
	tgt.h = 32;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, texture, NULL, &tgt);

}

void initTextDrawing() {
	if (TTF_Init() == -1) {
		SDL_Log("Error: could not init TTF %S", TTF_GetError());
		exit(2);
	}
}

TTF_Font* createFont(const char* fontName) {
	TTF_Font* f = TTF_OpenFont(fontName, 12);
	if (!f) {
		SDL_Log("Error: could not load font %s %s", fontName, TTF_GetError());
		return NULL;
	}
	return f;
}

void drawText(int x, int y, SDL_Renderer* renderer, TTF_Font* font, const char* text) {
	SDL_Surface* textSurface;
	SDL_Color color = { 255, 255, 255 };
	if (!(textSurface = TTF_RenderText_Solid(font, text, color))) {
		SDL_Log("Error: could not render text! %s", TTF_GetError());
	}
	else {
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect tgt = { x, y, textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, tex, NULL, &tgt);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(tex);
	}
}

void drawTopMenu(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect tgt;
	tgt.x = 0;
	tgt.y = 0;
	tgt.w = 800;
	tgt.h = 32;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, texture, NULL, &tgt);
}

void drawImage(int x, int y, int w, int h, SDL_Texture* texture, SDL_Renderer* renderer) {
	SDL_Rect tgt;
	tgt.x = x;
	tgt.y = y;
	tgt.w = w;
	tgt.h = h;

	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, texture, NULL, &tgt);
}