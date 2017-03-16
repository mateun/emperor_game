#pragma once
#include "inputqueue.h"
#include <SDL2\SDL.h>

InputQueue::InputQueue() {

}

InputQueue::~InputQueue() {

}

void InputQueue::subscribe(std::function<void(InputEvent)> callback) {
	_subscribers.push_back(callback);
}

void InputQueue::gatherInputs() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_MOUSEBUTTONUP) {
			InputEvent e;
			e.type = MOUSE_UP;
			e.x = event.motion.x;
			e.y = event.motion.y;
			_events.push_back(e);
		}
	}
}

void InputQueue::updateSubscribers() {
	for (InputEvent e : _events) {
		for (auto& fn : _subscribers) {
			fn(e);
		}
	}
}

void InputQueue::clearEvents() {
	_events.clear();
}

void InputQueue::clearSubscribers() {
	_subscribers.clear();
}

int InputQueue::getNumberOfEventsInQueue() {
	return _events.size();
}