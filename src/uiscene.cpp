#include "ui.h"
#include <SDL2\SDL.h>

UIScene::UIScene(InputQueue& inputQueue) {
	inputQueue.subscribe(std::bind(&UIScene::onInputEvent, this, std::placeholders::_1));
}

UIScene::~UIScene() {

}

void UIScene::onInputEvent(InputEvent event) {
	// propagate event to each widget, 
	// it shall then decide what to make of it.
	SDL_Log("received event in uiSCene: %d", event.type);
}

void UIScene::render(SDL_Renderer* renderer) {
	// go through all child widgets and
	// call render on each of them.
}