#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
using std::wstring;

class IndexOutOfRangeException
{
public:
    IndexOutOfRangeException();
};

class KeyNotFoundException
{
public:
    KeyNotFoundException();
};

class ArgumentException
{
public:
    ArgumentException(wstring message);
    const wstring& Message() const;

private:
    wstring message;
};

class InvalidOperationException
{

public:
    InvalidOperationException(wstring message);
    const wstring& Message() const;

private:
    wstring message;
};
#endif // EXCEPTION_H
