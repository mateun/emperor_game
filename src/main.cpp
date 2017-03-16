#include <stdio.h>
#include <sdl2/sdl.h>
#include "display.h"
#include "drawing.h"
#include "ui.h"
#include <vector>
#include <string.h>

#undef main

struct DropDownComp {
	int x, y, w, h;
};

int main(int argc, char** args) {

	bool dropDownActive = false;
	
	SDL_Renderer* renderer = showWindow(100, 100, 800, 600, false);
	initTextDrawing();

	TTF_Font* font = createFont("Antonio-Regular.ttf");
	SDL_Texture* playerImg = createImage("player.bmp", renderer);
	SDL_Texture* topMenuPart = createImage("topmenu_part.bmp", renderer);
	registerMouseWatchComponent(10, 5, 30, 20, "fileMenu");
	registerMouseWatchComponent(100, 5, 30, 20, "aboutMenu");

	bool buttonPressedThisFrame = false;
	DropDownComp dropDownComp = { 0, 0, 0, 0 };
	while (1) {
		clearBackBuffer();

		drawImage(100, 400, playerImg, renderer);
		drawImage(0, 0, 800, 32, topMenuPart, renderer);

		// Check if the left mouse button was pressed
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_MOUSEBUTTONUP) {
				buttonPressedThisFrame = true;
				// As long as we don't know we have been over a watched 
				// component (e.g. a menu), we assume, we are not over a menu.
				dropDownActive = false;
			}
			else {
				buttonPressedThisFrame = false;
			}
		}
		
		std::vector<std::string> componentsWithEvents = pollUIEvents();

		
		
		for (std::string compName : componentsWithEvents) {
			
				printf("comp with Event: %s\n", compName.c_str());

				// draw a background rect under the respective component
				// The surface and texture should all be pre-generated, 
				// just leaving it here for simplicity.
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

				if (buttonPressedThisFrame && !dropDownActive) {
					dropDownActive = true;
					dropDownComp.x = comp.x - 5;
					dropDownComp.y = comp.y + comp.h + 5;
					dropDownComp.w = comp.w + 100;
					dropDownComp.h = comp.h + 200;
				}
				

				//if (dropDownActive) {
				//	// draw a drop down menu
				//	s = SDL_CreateRGBSurface(0, 30, 20, 32, 0, 0, 0, 0);
				//	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 80, 80, 80));
				//	t = SDL_CreateTextureFromSurface(renderer, s);
				//	SDL_FreeSurface(s);

				//	tr.x = comp.x - 5;
				//	tr.y = comp.y + comp.h + 5;
				//	tr.w = comp.w + 100;
				//	tr.h = comp.h + 200;

				//	SDL_RenderCopy(renderer, t, NULL, &tr);
				//	SDL_DestroyTexture(t);
				//}

				// end test

		}

		if (dropDownActive) {
				// draw a drop down menu
				SDL_Surface* s = SDL_CreateRGBSurface(0, 30, 20, 32, 0, 0, 0, 0);
				SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 80, 80, 80));
				SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
				SDL_FreeSurface(s);

				SDL_Rect tr;
				tr.x = dropDownComp.x;
				tr.y = dropDownComp.y;
				tr.w = dropDownComp.w;
				tr.h = dropDownComp.h;

				SDL_RenderCopy(renderer, t, NULL, &tr);
				SDL_DestroyTexture(t);
			
		}

		drawText(10, 5, renderer, font, "File");
		drawText(100, 5, renderer, font, "About");
		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}