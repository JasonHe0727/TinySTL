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

	String slice = text.Slice(0, 2);
	Console::WriteLine(slice);

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

	String s = "To be or not to be, it is a question.";
	auto array = s.Split(" ");
	for(int i = 0; i < array.Length(); i++) {
		Console::WriteLine(array[i]);
	}
    return 0;
}
