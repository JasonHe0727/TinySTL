#include <iostream>
#include "Console.hpp"
#include "Test_List.hpp"
#include "Test_String.hpp"
#include "Test_StringAlgorithms.hpp"
#include "Test_SortingAlgorithms.hpp"
#include "SortingAlgorithms.hpp"
#include "Stack.hpp"

using std::cout;
using std::endl;

int main()
{
	Test_List::TestAll();
	Test_String::TestAll();
	Test_StringAlgorithms::TestAll();
	Test_SortingAlgorithms::TestAll();

	Stack<int> stack;
	stack.Push(10);
	stack.Push(20);
	stack.Push(30);

	while(not stack.IsEmpty()) {
		Console::WriteIntLine(stack.Top());
		stack.Pop();
	}

    return 0;
}
