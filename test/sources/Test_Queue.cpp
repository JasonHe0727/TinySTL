#include "Test_Queue.hpp"
#include "Assert.hpp"
#include "Queue.hpp"

void Test_Queue::TestAll() {
	Test1();
}

void Test_Queue::Test1() {
	Queue<int> queue;
	for(int i = 0; i < 10; i++) {
		queue.Enqueue(i);
	}

	ASSERT_EQUAL(queue.Size(), 10);
	int number = 0;
	while(not queue.IsEmpty()) {
		ASSERT_EQUAL(queue.Top(), number);
		queue.Dequeue();
		number++;
	}
	ASSERT_PASS;
}
