#pragma once
#include "inputqueue.h"
#include <sdl2/sdl.h>
#include <string>
#include <vector>

/**
	Hierarchical model of UIWidgets
 */
class UIScene {

public:
	UIScene(InputQueue& inputQueue);
	virtual ~UIScene();
	virtual void render(SDL_Renderer* renderer);
	void onInputEvent(InputEvent event);
};

struct MouseWatchComp {
	int x, y, w, h;
	std::string name;
};

void registerMouseWatchComponent(int x, int y, int w, int h, const std::string& name);
void unregisterMouseWatchComponent(const std::string& name);
MouseWatchComp getMouseWatchCompByName(const std::string& name);

// Returns a vector of components which had a ui event detected
std::vector<std::string> pollUIEvents();