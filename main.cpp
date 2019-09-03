#include <iostream>
#include "Test_List.hpp"
#include "Test_String.hpp"
#include "Test_StringAlgorithms.hpp"
#include "Test_SortingAlgorithms.hpp"
#include "Test_Stack.hpp"
#include "Test_Queue.hpp"
#include "Test_Option.hpp"
#include "Test_Trie.hpp"
#include "Test_Dictionary.hpp"
#include "Console.hpp"
#include "SortingAlgorithms.hpp"
#include "StringAlgorithms.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Option.hpp"
#include "Trie.hpp"
#include "StreamReader.hpp"
#include "StreamWriter.hpp"
#include "Dictionary.hpp"

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
	Test_Dictionary::TestAll();
}

int main()
{
	TestAllCases();

	String pattern = "NEEDLE";
	String text = "FINDINAHAYSTACKNEEDLE";

	KMP kmp{pattern, 256};
	int loc = kmp.Search(text);

	Console::WriteLine(loc);

	BoyerMoore bm{pattern, 256};
	loc = bm.Search(text);

	Console::WriteLine(loc);

	// StreamReader reader("high歌.txt");
	// while(auto line = reader.ReadLine()) {
	// 	Console::WriteLine(line.Get());
	// }

	// StreamWriter writer("关雎（节选）.txt");

	// writer.WriteLine("求之不得，寤寐思服。");
	// writer.WriteLine("悠哉悠哉，辗转反侧。");
	
	// Dictionary<String, int> map;

	// map.Add("A", 10);
	// map.Add("B", 20);
	// map.Add("C", 30);
	// map.Add("D", 40);
	// map.Add("E", 50);

	// for(const String& key : map.Keys()) {
	// 	Console::WriteLine(key);
	// }

    return 0;
}
