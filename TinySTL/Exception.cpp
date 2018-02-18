#include "Exception.hpp"

IndexOutOfRangeException::IndexOutOfRangeException()
{
}

KeyNotFoundException::KeyNotFoundException()
{
}

ArgumentException::ArgumentException(std::wstring message)
    : message{message}
{
}

const std::wstring& ArgumentException::Message() const
{
    return message;
}

InvalidOperationException::InvalidOperationException(std::wstring message)
    : message{message}
{
}

const std::wstring& InvalidOperationException::Message() const
{
    return message;
}
