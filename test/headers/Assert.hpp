#ifndef ASSERT_HPP
#define ASSERT_HPP
#include <iostream>

#define ASSERT_EQUAL(x, y) if((x) != (y)) { std::cout << __PRETTY_FUNCTION__ << " \033[1;31mfail\033[0m" << std::endl; return; }
#define ASSERT_PASS std::cout << __PRETTY_FUNCTION__ << " \033[1;32mpass\033[0m" << std::endl;

#endif // ASSERT_HPP
