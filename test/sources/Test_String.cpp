#include "Test_String.hpp"
#include "Assert.hpp"
#include "String.hpp"
#include <iostream>

void Test_String::TestAll() {
	Test1();
	Test2();
	Test3();
	Test4();
}

void Test_String::Test1() {
    String text{"你好, C++!"};
	ASSERT_EQUAL(text.Length(), 8);
	ASSERT_PASS;
}

void Test_String::Test2() {
    String text{"你好, C++!"};
	String slice = text.Slice(0, 2);
	ASSERT_EQUAL(slice, "你好");
	ASSERT_PASS;
}

void Test_String::Test3() {
	String s = "To be, or not to be, that is the question.";
	auto array = s.Split(" ");

	ASSERT_EQUAL(array.Length(), 10);
	ASSERT_EQUAL(array[0], "To");	
	ASSERT_EQUAL(array[1], "be,");	
	ASSERT_EQUAL(array[2], "or");	
	ASSERT_EQUAL(array[3], "not");	
	ASSERT_EQUAL(array[4], "to");	
	ASSERT_EQUAL(array[5], "be,");	
	ASSERT_EQUAL(array[6], "that");	
	ASSERT_EQUAL(array[7], "is");	
	ASSERT_EQUAL(array[8], "the");	
	ASSERT_EQUAL(array[9], "question.");	

	ASSERT_PASS;
}

void Test_String::Test4() {
	Array<String> words = {"GET", "OUT", "OF", "HERE"};
	String sentence = String::Join("!!", words);
	ASSERT_EQUAL(sentence, "GET!!OUT!!OF!!HERE");

	ASSERT_PASS;
}
