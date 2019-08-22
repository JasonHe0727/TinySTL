#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "String.hpp"
#include "Option.hpp"

class Console
{
public:
    static void Write(const String &string);

    static void WriteLine(const String &string);

    static void Write(const Char& character);

    static void WriteLine(const Char& character);

	static void WriteInt(const int& i);

	static void WriteIntLine(const int& i);

    static void WriteLine();

	static Option<int> ReadInt();

	static Option<double> ReadDouble();
};


#endif //CONSOLE_HPP
