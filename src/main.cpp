#include <stdio.h>
#include <sdl2/sdl.h>
#include "display.h"
#include "drawing.h"
#include "ui.h"
#include <vector>
#include <string.h>

#undef main

int main(int argc, char** args) {
	
	SDL_Renderer* renderer = showWindow(100, 100, 800, 600, false);
	initTextDrawing();

	TTF_Font* font = createFont("Antonio-Regular.ttf");
	SDL_Texture* playerImg = createImage("player.bmp", renderer);
	SDL_Texture* topMenuPart = createImage("topmenu_part.bmp", renderer);
	registerMouseWatchComponent(10, 10, 50, 50, "fileMenu");

	while (1) {
		std::vector<const char*> componentsWithEvents = pollUIEvents();
		for (const char* compName : componentsWithEvents) {
			if (strcmp("fileMenu", compName) == 0) {
				
			}
		}
		//pollWindowEvent();

		clearBackBuffer();
		// draw some sprites
		drawImage(100, 400, playerImg, renderer);
		//drawTopMenu(renderer, topMenuPart);
		drawImage(0, 0, 800, 32, topMenuPart, renderer);
		drawText(10, 10, renderer, font, "File");

		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}