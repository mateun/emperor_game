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

		
		//pollWindowEvent();

		
		
		drawImage(100, 400, playerImg, renderer);
		

		//drawTopMenu(renderer, topMenuPart);
		drawImage(0, 0, 800, 32, topMenuPart, renderer);
		

		std::vector<std::string> componentsWithEvents = pollUIEvents();
		for (std::string compName : componentsWithEvents) {
			if ("fileMenu" == compName) {
				printf("comp with Event: %s\n", compName.c_str());

				// test
				SDL_Surface* s = SDL_CreateRGBSurface(0, 30, 20, 32, 0, 0, 0, 0);
				SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 80, 80, 80));
				SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
				SDL_FreeSurface(s);
				SDL_Rect tr;
				tr.x = 5;
				tr.y = 5;
				tr.w = 40;
				tr.h = 25;
				SDL_RenderCopy(renderer, t, NULL, &tr);
				SDL_DestroyTexture(t);
				// end test

			}
		}

		drawText(10, 5, renderer, font, "File");


		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}