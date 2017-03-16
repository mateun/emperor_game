#include "topmenu.h"
#include "drawing.h"
#include "ui.h"
#include <sdl2/sdl.h>
#include <SDL2_ttf\SDL_ttf.h>
#include <vector>

struct ActiveComp {
	int x, y, w, h;
	std::string name;
};

struct HoverTexture{
	SDL_Texture* tex;
	SDL_Rect r;
};

static bool dropDownActive = false;
static ActiveComp activeComp = { 0, 0, 0, 0 };
static TTF_Font* font = NULL;
static SDL_Texture* topMenuPart = NULL; 

void initTopMenu() {
	registerMouseWatchComponent(10, 5, 30, 20, "fileMenu");
	registerMouseWatchComponent(100, 5, 30, 20, "aboutMenu");
}

/**
	Menu rendering sequence: 
		- top menu bar
		- drop down menu
		- hover rects
		- menu texts
*/

void handleTopMenuFrame(SDL_Renderer* renderer, bool buttonPressedThisFrame) {

	if (font == NULL) 
		font = createFont("arial.ttf");

	if (topMenuPart == NULL)
		topMenuPart = createImage("topmenu_part.bmp", renderer);

	if (buttonPressedThisFrame) {
		// We defensively assume that the cursor was not over a menu.
		dropDownActive = false;
	}

	// render top menu bar (seq 1)
	drawImage(0, 0, 800, 32, topMenuPart, renderer);

	std::vector<std::string> componentsWithEvents = pollUIEvents();
	HoverTexture hoverTexture = {};

	for (std::string compName : componentsWithEvents) {

		printf("comp with Event: %s\n", compName.c_str());

		// draw a background rect under the respective component
		// The surface and texture should all be pre-generated, 
		// just leaving it here for simplicity.
		SDL_Surface* s = SDL_CreateRGBSurface(0, 30, 20, 32, 0, 0, 0, 0);
		SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 60, 60, 60));
		SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
		SDL_FreeSurface(s);

		MouseWatchComp comp = getMouseWatchCompByName(compName.c_str());
		SDL_Log("comp x: %d", comp.x);
		SDL_Rect tr;
		tr.x = comp.x - 5;
		tr.y = comp.y - 2;
		tr.w = comp.w + 10;
		tr.h = comp.h + 6;

		
	}

	if (buttonPressedThisFrame) {
		if (!dropDownActive) {
			dropDownActive = true;
			
		}
		else {
			SDL_Log("button pressed, while dropdown is active!");
		}
	}



}
