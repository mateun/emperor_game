#include "topmenu.h"
#include "drawing.h"
#include <sdl2/sdl.h>
#include <vector>

struct DropDownComp {
	int x, y, w, h;
	std::string name;
};

static bool dropDownActive = false;
static DropDownComp dropDownComp = { 0, 0, 0, 0 };

void handleTopMenu(SDL_Renderer* renderer, bool buttonPressedThisFrame) {

	if (buttonPressedThisFrame) {
		// We defensively assume that the cursor was not over a menu.
		dropDownActive = false;
	}

	std::vector<std::string> componentsWithEvents = pollUIEvents();
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

		SDL_RenderCopy(renderer, t, NULL, &tr);
		SDL_DestroyTexture(t);

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
		// Draw a drop down menu.
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

		// Now the menu entries
		TTF_Font* font = createFont("arial.ttf");	// TODO this should not always be created here..!
		if (dropDownComp.name == "fileMenu") {
			drawText(dropDownComp.x + 5, dropDownComp.y + 5, renderer, font, "New map");
			drawText(dropDownComp.x + 5, dropDownComp.y + 35, renderer, font, "Save");
			drawText(dropDownComp.x + 5, dropDownComp.y + 65, renderer, font, "Exit");
		}

	}
}
