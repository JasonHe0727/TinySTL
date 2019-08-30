#include "Test_Dictionary.hpp"
#include "Assert.hpp"
#include "Dictionary.hpp"

void Test_Dictionary::TestAll() {
	Test1();
}

void Test_Dictionary::Test1() {
	Dictionary<String, int> map;
	map.Add("A", 10);
	map.Add("B", 20);
	map.Add("C", 30);
	map.Add("D", 40);
	map.Add("E", 50);

	ASSERT_EQUAL(map.Size(), 5);
	ASSERT_EQUAL(map["D"], 40);

	map.Remove("D");
	ASSERT_EQUAL(map.Size(), 4);
	ASSERT_EQUAL(map["E"], 50);

	ASSERT_PASS;
}
