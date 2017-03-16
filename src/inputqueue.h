#pragma once
#include <vector>
#include <functional>


enum EventType {
	MOUSE_UP,
	MOUSE_DOWN,
	MOUSE_MOVE
};


struct InputEvent {
	int x;
	int y;
	EventType type;
};



class InputQueue {

public:
	InputQueue();
	~InputQueue();
	virtual void subscribe(std::function<void (InputEvent)>);
	virtual void updateSubscribers();
	virtual void gatherInputs();
	virtual void clearEvents();
	virtual void clearSubscribers();
	virtual int getNumberOfEventsInQueue();

protected:
	std::vector<InputEvent> _events;
	std::vector<std::function<void (InputEvent)>> _subscribers;
	
};