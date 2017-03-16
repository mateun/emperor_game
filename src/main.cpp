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
	registerMouseWatchComponent(10, 5, 30, 20, "fileMenu");

	while (1) {
		clearBackBuffer();

		std::vector<std::string> componentsWithEvents = pollUIEvents();
		for (std::string compName : componentsWithEvents) {
			if ("fileMenu" == compName) {
				printf("comp with Event: %s\n", compName.c_str());
			}
		}
		
		//pollWindowEvent();

		
		
		drawImage(100, 400, playerImg, renderer);
		//drawTopMenu(renderer, topMenuPart);
		drawImage(0, 0, 800, 32, topMenuPart, renderer);
		drawText(10, 5, renderer, font, "File");

		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}