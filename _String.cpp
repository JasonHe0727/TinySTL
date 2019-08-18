#include "String.hpp"
#include <string.h>

//String::String() : characters{nullptr}, length{0}
//{
//
//}
//
//String::String(const char *s)
//{
//
//}
//
//String::String(const String &s)
//        : characters{CopyString(s.characters, s.length)}, length{length}
//{
//
//}
//
//String::String(String &&s) noexcept
//        : characters{s.characters}, length{s.length}
//{
//    s.characters = nullptr;
//    s.length = 0;
//}
//
//String::~String()
//{
//
//}
//
//Char *String::CopyString(const Char *input, int length)
//{
//    Char *characters = new Char[length];
//    for (int i = 0; i < length; i++)
//    {
//        characters[i] = input[i];
//    }
//    return characters;
//}
//
//String &String::operator=(String other) noexcept
//{
//    characters = other.characters;
//    length = other.length;
//    other.characters = nullptr;
//    other.length = 0;
//    return *this;
//}
//
//int String::CountUtf8ToUtf16Length(const char *s)
//{
//    int i = 0;
//    int n = strlen(s);
//    int count = 0;
//    while (i < n)
//    {
//        int code = s[i];
//        if (((code >> 7) & 0xFF) == 0x0)
//        {
//            i = i + 1;
//        }
//        else if (((code >> 5) & 0xFF) == 0x6)
//        {
//            i = i + 2;
//        }
//        else if (((code >> 4) & 0xFF) == 0xE)
//        {
//            i = i + 3;
//        }
//        else if (((code >> 3) & 0xFF) == 0x1E)
//        {
//            i = i + 4;
//        }
//        else if (((code >> 2) & 0xFF) == 0x3E)
//        {
//            i = i + 5;
//        }
//        else if (((code >> 1) & 0xFF) == 0x7E)
//        {
//            i = i + 6;
//        }
//        else
//        {
//            break;
//        }
//        count++;
//    }
//    return count;
//}
