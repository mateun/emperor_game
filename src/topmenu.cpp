#include "topmenu.h"
#include "drawing.h"
#include "ui.h"
#include <sdl2/sdl.h>
#include <SDL2_ttf\SDL_ttf.h>
#include <vector>

struct DropDownComp {
	int x, y, w, h;
	std::string name;
};

struct HoverTexture{
	SDL_Texture* tex;
	SDL_Rect r;
};

static bool dropDownActive = false;
static DropDownComp dropDownComp = { 0, 0, 0, 0 };
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
	std::vector<HoverTexture> hoverTextures;

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

		
		// Don't render immediately, but put into hover textures list
		HoverTexture ht = { t, tr };
		hoverTextures.push_back(ht);

		if (buttonPressedThisFrame && !dropDownActive) {
			dropDownActive = true;
			dropDownComp.x = comp.x - 5;
			dropDownComp.y = comp.y + comp.h + 5;
			dropDownComp.w = comp.w + 100;
			dropDownComp.h = comp.h + 80;
			dropDownComp.name = comp.name;
		}

	}

	if (dropDownActive) {
		// Draw a drop down menu (seq2)
		// First the background:
		SDL_Surface* s = SDL_CreateRGBSurface(0, 30, 20, 32, 0, 0, 0, 0);
		SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 30, 30, 30));
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

	// Render hover rects (seq 3)
	for (HoverTexture t : hoverTextures) {
		SDL_RenderCopy(renderer, t.tex, NULL, &t.r);
		SDL_DestroyTexture(t.tex);
	}

	// Draw menu texts
	drawText(10, 5, renderer, font, "File");
	drawText(100, 5, renderer, font, "About");

	// Now the menu entries

	if (dropDownComp.name == "fileMenu" && dropDownActive) {
		drawText(dropDownComp.x + 5, dropDownComp.y + 5, renderer, font, "New map");
		drawText(dropDownComp.x + 5, dropDownComp.y + 35, renderer, font, "Save");
		drawText(dropDownComp.x + 5, dropDownComp.y + 65, renderer, font, "Exit");

		// Register the new entries as mousewatch components:
		registerMouseWatchComponent(10, dropDownComp.y + 2, 120, 20, "newMapMenu");
		registerMouseWatchComponent(10, dropDownComp.y + 33, 120, 20, "saveMenu");
		registerMouseWatchComponent(10, dropDownComp.y + 63, 120, 20, "exitMenu");
	}
}
