#include "Console.hpp"
#include <iostream>

void Console::Write(const String &string)
{
    for (int i = 0; i < string.Length(); i++)
    {
        uint8_t *str = Encoding::Utf16CharacterToUtf8(string[i].ToInt());
        while ((*str) != '\0')
        {
            putchar(*str);
            str++;
        }
    }
}

void Console::WriteLine(const String &string)
{
    Write(string);
    std::cout << std::endl;
}

void Console::Write(const Char &character)
{
    uint8_t *str = Encoding::Utf16CharacterToUtf8(character.ToInt());
    while ((*str) != '\0')
    {
        putchar(*str);
        str++;
    }
}

void Console::WriteLine(const Char &character)
{
    Write(character);
    std::cout << std::endl;
}

void Console::WriteInt(const int& i) {
	std::cout << i;
}

void Console::WriteIntLine(const int& i) {
	std::cout << i << std::endl;
}

void Console::WriteLine()
{
    std::cout << std::endl;
}
