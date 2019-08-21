#include <iostream>
#include "Console.hpp"
#include "Test_List.hpp"
#include "Test_String.hpp"
#include "Test_StringAlgorithms.hpp"

using std::cout;
using std::endl;

int main()
{
	Test_List::TestAll();
	Test_String::TestAll();
	Test_StringAlgorithms::TestAll();
    return 0;
}
