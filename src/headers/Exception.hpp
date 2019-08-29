#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include "String.hpp"

class Exception : std::exception {
public:
	String message;

	Exception();
	Exception(const String& message);
};

class KeyNotFoundException : Exception {
};

class DuplicateKeyException : Exception {
};
#endif // EXCEPTION_HPP
