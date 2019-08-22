#include "Test_Trie.hpp"
#include "Trie.hpp"
#include "Assert.hpp"

void Test_Trie::TestAll() {
	Test1();
}

void Test_Trie::Test1() {
	Trie<int> tree(256);
	tree.Insert("she", 0);
	tree.Insert("sells", 1);
	tree.Insert("sea", 2);
	tree.Insert("shells", 3);
	tree.Insert("by", 4);
	tree.Insert("the", 5);
	tree.Insert("sea", 6);
	tree.Insert("shore", 7);

	if(auto i = tree["sea"]) {
		ASSERT_EQUAL(6, i.Get());
	} else {
		ASSERT_FAIL;
	}
	if(auto i = tree["by"]) {
		ASSERT_EQUAL(4, i.Get());
	} else {
		ASSERT_FAIL;
	}
	if(auto i = tree["shore"]) {
		ASSERT_EQUAL(7, i.Get());
	} else {
		ASSERT_FAIL;
	}
	ASSERT_PASS;
}
