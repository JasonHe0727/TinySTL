#ifndef STRINGLIBRARY_EXCEPTION_HPP
#define STRINGLIBRARY_EXCEPTION_HPP

#include "String.hpp"

class Exception {
public:
    String message;

    Exception(String message);
};

class IndexOutOfRangeException : public Exception {
public:
    IndexOutOfRangeException();
};

#endif //STRINGLIBRARY_EXCEPTION_HPP
