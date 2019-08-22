#include <iostream>
#include "Test_List.hpp"
#include "Test_String.hpp"
#include "Test_StringAlgorithms.hpp"
#include "Test_SortingAlgorithms.hpp"
#include "Test_Stack.hpp"
#include "Test_Queue.hpp"
#include "Test_Option.hpp"
#include "Test_Trie.hpp"
#include "Console.hpp"
#include "SortingAlgorithms.hpp"
#include "StringAlgorithms.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Option.hpp"
#include "Trie.hpp"

using std::cout;
using std::endl;

void TestAllCases();

void TestAllCases() {
	Test_List::TestAll();
	Test_String::TestAll();
	Test_StringAlgorithms::TestAll();
	Test_SortingAlgorithms::TestAll();
	Test_Stack::TestAll();
	Test_Queue::TestAll();
	Test_Option::TestAll();
	Test_Trie::TestAll();
}

int main()
{
	TestAllCases();

    return 0;
}
