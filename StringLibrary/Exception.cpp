#include "Exception.hpp"

Exception::Exception(String message) : message{message} {

}

IndexOutOfRangeException::IndexOutOfRangeException() : Exception("Index was outside the bounds of the array") {

}