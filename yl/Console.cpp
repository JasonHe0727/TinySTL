#include "Console.hpp"
#include <iostream>

void Console::Write(const String &string)
{
    for (int i = 0; i < string.Length(); i++)
    {
        uint8_t *str = Encoding::Utf16CharacterToUtf8(string[i]);
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

void Console::Write(const uint16_t &character)
{
    uint8_t *str = Encoding::Utf16CharacterToUtf8(character);
    while ((*str) != '\0')
    {
        putchar(*str);
        str++;
    }
}

void Console::WriteLine(const uint16_t &character)
{
    Write(character);
    std::cout << std::endl;
}

void Console::WriteLine()
{
    std::cout << std::endl;
}
