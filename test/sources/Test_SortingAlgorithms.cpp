#include "Test_SortingAlgorithms.hpp"
#include "String.hpp"
#include "Assert.hpp"
#include "SortingAlgorithms.hpp"

void Test_SortingAlgorithms::TestAll() {
	Test1();
}

void Test_SortingAlgorithms::Test1() {
	Array<Char> characters = String("SORTEXAMPLE").ToCharArray();
	Insertion::Sort(characters);
	ASSERT_EQUAL(String{ characters }, "AEELMOPRSTX");
	ASSERT_PASS;
}
