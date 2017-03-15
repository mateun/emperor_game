#include "display.h"

static SDL_Window* window;
static SDL_Renderer* renderer;

SDL_Renderer* showWindow(int x, int y, int w, int h, bool fullScreen) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL init failed: %s", SDL_GetError());
		exit(1);
	}

	SDL_Log("SDL initialized");

	if (SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_BORDERLESS, &window, &renderer) != 0) {
		SDL_Log("Window creation failed: %s", SDL_GetError());
		exit(1);
	}

	return renderer;
	
}

void pollWindowEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		exit(0);
	}
}

void clearBackBuffer() {
	SDL_RenderClear(renderer);

}

void displayBackBuffer() {
	SDL_RenderPresent(renderer);
}

void disposeWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}