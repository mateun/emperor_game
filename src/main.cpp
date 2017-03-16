#include <stdio.h>
#include <sdl2/sdl.h>
#include "display.h"
#include "drawing.h"
#include "ui.h"
#include "topmenu.h"
#include <vector>
#include <string.h>

#undef main



int main(int argc, char** args) {

	
	
	SDL_Renderer* renderer = showWindow(100, 100, 800, 600, false);
	initTextDrawing();

	TTF_Font* font = createFont("arial.ttf");
	SDL_Texture* playerImg = createImage("player.bmp", renderer);
	
	bool buttonPressedThisFrame = false;
	while (1) {
		clearBackBuffer();

		drawImage(100, 400, playerImg, renderer);
		
		initTopMenu();

		// Check if the left mouse button was pressed
		// TODO refactor to remove this not nice loop here ...
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_MOUSEBUTTONUP) {
				buttonPressedThisFrame = true;
			}
			else {
				buttonPressedThisFrame = false;
			}
		}
		
		handleTopMenuFrame(renderer, buttonPressedThisFrame);
		
		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}