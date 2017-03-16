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
	return testSubscription();
}

bool InputQueueTest::testSubscription() {
	std::unique_ptr<InputQueue> queue = std::make_unique<MockInputQueue>();
	bool testResult = false;
	queue->subscribe([&](InputEvent event) {
		if (event.type == MOUSE_UP)
			testResult = true;
	});

	queue->gatherInputs();
	queue->updateSubscribers();

	return testResult;
}