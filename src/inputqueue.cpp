#pragma once
#include "inputqueue.h"

InputQueue::InputQueue() {

}

InputQueue::~InputQueue() {

}

void InputQueue::subscribe(std::function<void(InputEvent)> callback) {
	_subscribers.push_back(callback);
}

void InputQueue::gatherInputs() {

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