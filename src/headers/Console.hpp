#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "String.hpp"

class Console
{
public:
    static void Write(const String &string);

    static void WriteLine(const String &string);

    static void Write(const uint16_t& character);

    static void WriteLine(const uint16_t& character);

	static void WriteInt(const int& i);

	static void WriteIntLine(const int& i);

    static void WriteLine();
};


#endif //CONSOLE_HPP
