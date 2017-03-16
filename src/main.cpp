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
	SDL_Texture* topMenuPart = createImage("topmenu_part.bmp", renderer);
	registerMouseWatchComponent(10, 5, 30, 20, "fileMenu");
	registerMouseWatchComponent(100, 5, 30, 20, "aboutMenu");

	bool buttonPressedThisFrame = false;
	while (1) {
		clearBackBuffer();

		drawImage(100, 400, playerImg, renderer);
		drawImage(0, 0, 800, 32, topMenuPart, renderer);

		// Check if the left mouse button was pressed
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_MOUSEBUTTONUP) {
				buttonPressedThisFrame = true;
			}
			else {
				buttonPressedThisFrame = false;
			}
		}
		
		handleTopMenu(renderer, buttonPressedThisFrame);
		

		drawText(10, 5, renderer, font, "File");
		drawText(100, 5, renderer, font, "About");
		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}