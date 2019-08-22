#include "Test_StringAlgorithms.hpp"
#include "StringAlgorithms.hpp"
#include "Assert.hpp"
#include "Console.hpp"

void Test_StringAlgorithms::TestAll() {
	Test1();
	Test2();
}

void Test_StringAlgorithms::Test1() {
	Array<String> input = {
		"4PGC938",
		"2IYE230",
		"3CI0720",
		"1ICK750",
		"1OHV845",
		"4JZY524",
		"1ICK750",
		"3CIO720",
		"1OHV845",
		"1OHV845",
		"2RLA629",
		"2RLA629",
		"3ATW723"
	};
	LSD::Sort(input, 6, 256);

	ASSERT_EQUAL(input.Size(), 13);
	ASSERT_EQUAL(input[0], "1ICK750");
	ASSERT_EQUAL(input[1], "1ICK750");
	ASSERT_EQUAL(input[2], "1OHV845");
	ASSERT_EQUAL(input[3], "1OHV845");
	ASSERT_EQUAL(input[4], "1OHV845");
	ASSERT_EQUAL(input[5], "2IYE230");
	ASSERT_EQUAL(input[6], "2RLA629");
	ASSERT_EQUAL(input[7], "2RLA629");
	ASSERT_EQUAL(input[8], "3ATW723");
	ASSERT_EQUAL(input[9], "3CI0720");
	ASSERT_EQUAL(input[10], "3CIO720");
	ASSERT_EQUAL(input[11], "4JZY524");
	ASSERT_EQUAL(input[12], "4PGC938");

	ASSERT_PASS;
}

void Test_StringAlgorithms::Test2() {
	Array<String> words = {
		"she",
		"sells",
		"seashells",
		"by",
		"the",
		"sea",
		"shore",
		"the",
		"shells",
		"she",
		"sells",
		"are",
		"surely",
		"seashells"
	};

	MSD::Sort(words, 256);

	ASSERT_EQUAL(words[0], "are");
	ASSERT_EQUAL(words[1], "by");
	ASSERT_EQUAL(words[2], "sea");
	ASSERT_EQUAL(words[3], "seashells");
	ASSERT_EQUAL(words[4], "seashells");
	ASSERT_EQUAL(words[5], "sells");
	ASSERT_EQUAL(words[6], "sells");
	ASSERT_EQUAL(words[7], "she");
	ASSERT_EQUAL(words[8], "she");
	ASSERT_EQUAL(words[9], "shells");
	ASSERT_EQUAL(words[10], "shore");
	ASSERT_EQUAL(words[11], "surely");
	ASSERT_EQUAL(words[12], "the");
	ASSERT_EQUAL(words[13], "the");

	ASSERT_PASS;
}
