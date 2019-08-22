#include "Test_Stack.hpp"
#include "Stack.hpp"
#include "Assert.hpp"

void Test_Stack::TestAll() {
	Test1();
}

void Test_Stack::Test1() {
	Stack<int> stack;
	for(int i = 0; i < 10; i++) {
		stack.Push(i);
	}

	ASSERT_EQUAL(stack.Size(), 10);

	int number = 9;
	while(not stack.IsEmpty()) {
		ASSERT_EQUAL(stack.Top(), number);
		stack.Pop();
		number--;
	}

	ASSERT_PASS;
}
