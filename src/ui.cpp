#include "ui.h"
#include <map>
#include "drawing.h"

struct MouseWatchComp {
	int x, y, w, h;
	const char* name;
};

static std::map<const char*, MouseWatchComp> mouseWatchComponents;

void registerMouseWatchComponent(int x, int y, int w, int h, const char* name) {
	MouseWatchComp mouseWatchComp = { x, y, w, h, name };
	mouseWatchComponents[name] = mouseWatchComp;
}

std::vector<std::string> pollUIEvents() {
	std::vector<std::string> detectedComponents;
	SDL_Event event;
	int x = 0, y = 0;

	//while (SDL_PollEvent(&event) != 0) {
		//if (event.type == SDL_MOUSEMOTION) {
			// Check for hover event.
			// i.e. we check if the mouse is over any 
			// of the registered mouse watch components.
			//x = event.motion.x;
			//y = event.motion.y;

			

			
			
		//}
	//}

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	//SDL_Log("x/y: %d %d", x, y);

	for (auto const& comp : mouseWatchComponents) {
		if (comp.second.x <= x && (x <= comp.second.x + comp.second.w) &&
			comp.second.y <= y && (y <= comp.second.y + comp.second.h)) {
			SDL_Log("hovering over component: %s", comp.second.name);
			detectedComponents.push_back(comp.second.name);
		}
	}


	return detectedComponents;
	
}