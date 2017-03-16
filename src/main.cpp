#include <stdio.h>
#include <sdl2/sdl.h>
#include "display.h"
#include "drawing.h"
#include "ui.h"
#include "topmenu.h"
#include "inputqueue_test.h"
#include <vector>
#include <string.h>

#undef main



int main(int argc, char** args) {

	InputQueueTest iqTest;
	if (iqTest.runTests() == false) {
		SDL_Log("Tests failed, not starting up!");
		exit(1);
	}
	else {
		SDL_Log("Basic startup tests ok, starting map editor");
	}

	
	
	SDL_Renderer* renderer = showWindow(100, 100, 800, 600, false);

	InputQueue inputQueue;
	UIScene uiScene(inputQueue);
	
	initTextDrawing();
	TTF_Font* font = createFont("arial.ttf");
	SDL_Texture* playerImg = createImage("player.bmp", renderer);
	
	bool buttonPressedThisFrame = false;
	while (1) {
		clearBackBuffer();

		inputQueue.gatherInputs();
		inputQueue.updateSubscribers();

		uiScene.render(renderer);

		// dummy image for testing purpose
		drawImage(100, 400, playerImg, renderer);
		
		
		inputQueue.clearEvents();
		displayBackBuffer();
	}

	disposeWindow();
	
	getchar();
	return 0;
}