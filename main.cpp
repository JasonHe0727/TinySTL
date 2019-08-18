#include <iostream>
#include "String.hpp"
#include "Console.hpp"
#include "List.hpp"

using std::cout;
using std::endl;

int main()
{
    String text{"你好, C++!"};
    cout << "string length: " << text.Length() << endl;
    Console::WriteLine(text);

	List<int> list;
	for(int i = 0; i < 10; i++) {
		list.Add(i * i);
	}

	for(int i = 0; i < 10; i++) {
		Console::WriteIntLine(list[i]);
	}

	List<String> list2 = {"Life", "is", "beautiful"};
	for(int i = 0; i < list2.Count(); i++) {
		Console::Write(list2[i]);
		Console::Write(" ");
	}
	Console::WriteLine();
    return 0;
}
