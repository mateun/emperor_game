#pragma once
#include "inputqueue.h"

class MyTest {

public:
	virtual bool runTests() = 0;
};

class InputQueueTest : MyTest {

public:
	virtual bool runTests();

private:
	bool testSubscription();
	bool testClear();
	
};

class MockInputQueue : public InputQueue {

public:
	virtual void gatherInputs();
};