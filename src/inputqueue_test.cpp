#include "inputqueue_test.h"
#include "inputqueue.h"
#include <memory>

void MockInputQueue::gatherInputs() {
	InputEvent event;
	event.type = MOUSE_UP;
	event.x = 100;
	event.y = 12;
	_events.push_back(event);
}

bool InputQueueTest::runTests() {
	return testSubscription() &&
			testClear();
}

class SimpleSubber {



public:
	SimpleSubber(bool& result) : _testResult(result){}
	void onEvent(InputEvent e) {
		_testResult = true;
	}

private:
	bool& _testResult;
};

bool InputQueueTest::testSubscription() {
	std::unique_ptr<InputQueue> queue = std::make_unique<MockInputQueue>();
	bool testResult = false;
	queue->subscribe([&](InputEvent event) {
		if (event.type == MOUSE_UP)
			testResult = true;
	});

	queue->gatherInputs();
	queue->updateSubscribers();

	testResult = false;

	SimpleSubber simpleSubber(testResult);
	std::function<void(InputEvent)> fn = std::bind(&SimpleSubber::onEvent, &simpleSubber, std::placeholders::_1);
	queue->clearSubscribers();
	queue->subscribe(fn);
	queue->updateSubscribers();

	return testResult;
}

bool InputQueueTest::testClear() {
	std::unique_ptr<InputQueue> queue = std::make_unique<MockInputQueue>();
	queue->gatherInputs();

	if (queue->getNumberOfEventsInQueue() < 1)
		return false;

	queue->clearEvents();

	return queue->getNumberOfEventsInQueue() == 0;		
}