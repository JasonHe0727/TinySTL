#include "Test_Option.hpp"
#include "String.hpp"
#include "Option.hpp"
#include "Assert.hpp"

void Test_Option::TestAll() {
	Test1();
}

void Test_Option::Test1() {
	if(Option<String> a = String("DIGITAL PAPER")) {
		ASSERT_EQUAL(a.Get(), "DIGITAL PAPER");
	}
	ASSERT_PASS;
}
