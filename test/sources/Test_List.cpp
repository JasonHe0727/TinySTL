#include "Test_List.hpp"
#include "List.hpp"
#include "Assert.hpp"
#include "String.hpp"
#include <iostream>

using std::cout;
using std::endl;

void Test_List::TestAll() {
	Test1();
	Test2();
}

void Test_List::Test1() {
	List<int> list;
	for(int i = 0; i < 10; i++) {
		list.Add(i * i);
	}

	for(int i = 0; i < 10; i++) {
		ASSERT_EQUAL(list[i], i * i);
	}
	ASSERT_PASS;
}

void Test_List::Test2() {
	List<String> list2 = {"Life", "is", "beautiful"};
	ASSERT_EQUAL(list2[0], "Life");
	ASSERT_EQUAL(list2[1], "is");
	ASSERT_EQUAL(list2[2], "beautiful");

	ASSERT_PASS;
}
