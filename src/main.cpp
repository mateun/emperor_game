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
	registerMouseWatchComponent(100, 5, 30, 20, "aboutMenu");


	while (1) {
		clearBackBuffer();

		drawImage(100, 400, playerImg, renderer);
		drawImage(0, 0, 800, 32, topMenuPart, renderer);
		
		std::vector<std::string> componentsWithEvents = pollUIEvents();
		for (std::string compName : componentsWithEvents) {
			
				printf("comp with Event: %s\n", compName.c_str());

				// draw a background rect under the respective component
				SDL_Surface* s = SDL_CreateRGBSurface(0, 30, 20, 32, 0, 0, 0, 0);
				SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 80, 80, 80));
				SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
				SDL_FreeSurface(s);

				MouseWatchComp comp = getMouseWatchCompByName(compName.c_str());
				SDL_Log("comp x: %d", comp.x);

				SDL_Rect tr;
				tr.x = comp.x - 5;
				tr.y = comp.y - 2;
				tr.w = comp.w + 10;
				tr.h = comp.h + 6;
				
				SDL_RenderCopy(renderer, t, NULL, &tr);
				SDL_DestroyTexture(t);
				// end test

		}

		drawText(10, 5, renderer, font, "File");
		drawText(100, 5, renderer, font, "About");


		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}