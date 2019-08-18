#include "String.hpp"
#include "Exception.hpp"

int Encoding::Utf8ToUtf16Count(const char *utf8)
{
    int i = 0;
    int count = 0;
    while (utf8[i] != '\0')
    {
        uint8_t code = utf8[i];
        if (((code >> 7) & 0xFF) == 0x0)
        {
            i++;
            count++;
        }
        else if (((code >> 5) & 0xFF) == 0x6)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x1F) << 6;
            int32_t byte2 = code2 & 0x3F;
            uint16_t utf16 = byte1 | byte2;

            count++;
        }
        else if (((code >> 4) & 0xFF) == 0xE)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x0F) << 12;
            int32_t byte2 = (code2 & 0x3F) << 6;
            int32_t byte3 = code3 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3;
            count++;
        }
        else if (((code >> 3) & 0xFF) == 0x1E)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            uint8_t code4 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x07) << 18;
            int32_t byte2 = (code2 & 0x3F) << 12;
            int32_t byte3 = (code3 & 0x3F) << 6;
            int32_t byte4 = code4 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3 | byte4;

            count++;
        }
        else if (((code >> 2) & 0xFF) == 0x3E)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            uint8_t code4 = utf8[i];
            i++;
            uint8_t code5 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x03) << 24;
            int32_t byte2 = (code2 & 0x3F) << 18;
            int32_t byte3 = (code3 & 0x3F) << 12;
            int32_t byte4 = (code4 & 0x3F) << 6;
            int32_t byte5 = code5 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3 | byte4 | byte5;

            count++;
        }
        else if (((code >> 1) & 0xFF) == 0x7E)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            uint8_t code4 = utf8[i];
            i++;
            uint8_t code5 = utf8[i];
            i++;
            uint8_t code6 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x01) << 30;
            int32_t byte2 = (code2 & 0x3F) << 24;
            int32_t byte3 = (code3 & 0x3F) << 18;
            int32_t byte4 = (code4 & 0x3F) << 12;
            int32_t byte5 = (code5 & 0x3F) << 6;
            int32_t byte6 = code6 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3 | byte4 | byte5 | byte6;

            count++;
        }
        else
        {
            return -1;
        }
    }
    return count;
}

void Encoding::Utf8ToUtf16(const char *utf8, uint16_t *result)
{
    int i = 0;
    int index = 0;
    while (utf8[i] != '\0')
    {
        uint8_t code = utf8[i];
        if (((code >> 7) & 0xFF) == 0x0)
        {
            i++;
            result[index] = code;
            index++;
        }
        else if (((code >> 5) & 0xFF) == 0x6)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x1F) << 6;
            int32_t byte2 = code2 & 0x3F;
            uint16_t utf16 = byte1 | byte2;
            result[index] = utf16;
            index++;
        }
        else if (((code >> 4) & 0xFF) == 0xE)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x0F) << 12;
            int32_t byte2 = (code2 & 0x3F) << 6;
            int32_t byte3 = code3 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3;
            result[index] = utf16;
            index++;
        }
        else if (((code >> 3) & 0xFF) == 0x1E)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            uint8_t code4 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x07) << 18;
            int32_t byte2 = (code2 & 0x3F) << 12;
            int32_t byte3 = (code3 & 0x3F) << 6;
            int32_t byte4 = code4 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3 | byte4;

            result[index] = utf16;
            index++;
        }
        else if (((code >> 2) & 0xFF) == 0x3E)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            uint8_t code4 = utf8[i];
            i++;
            uint8_t code5 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x03) << 24;
            int32_t byte2 = (code2 & 0x3F) << 18;
            int32_t byte3 = (code3 & 0x3F) << 12;
            int32_t byte4 = (code4 & 0x3F) << 6;
            int32_t byte5 = code5 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3 | byte4 | byte5;

            result[index] = utf16;
            index++;
        }
        else if (((code >> 1) & 0xFF) == 0x7E)
        {
            i++;
            uint8_t code2 = utf8[i];
            i++;
            uint8_t code3 = utf8[i];
            i++;
            uint8_t code4 = utf8[i];
            i++;
            uint8_t code5 = utf8[i];
            i++;
            uint8_t code6 = utf8[i];
            i++;
            int32_t byte1 = (code & 0x01) << 30;
            int32_t byte2 = (code2 & 0x3F) << 24;
            int32_t byte3 = (code3 & 0x3F) << 18;
            int32_t byte4 = (code4 & 0x3F) << 12;
            int32_t byte5 = (code5 & 0x3F) << 6;
            int32_t byte6 = code6 & 0x3F;
            uint16_t utf16 = byte1 | byte2 | byte3 | byte4 | byte5 | byte6;

            result[index] = utf16;
            index++;
        }
        else
        {
            throw Exception("illegal utf-8 characters input");
        }
    }
}

uint8_t *Encoding::Utf16CharacterToUtf8(uint16_t code)
{
    static uint8_t result[7];
    for (int i = 0; i < 7; i++)
    {
        result[i] = '\0';
    }
    if (code > 0x0000 && code <= 0x007F)
    {
        result[0] = code;
    }
    else if (code >= 0x0080 && code <= 0x07FF)
    {
        uint8_t byte1 = 0xC0 | ((code >> 6) & 0x1F);
        uint8_t byte2 = 0x80 | (code & 0x3F);
        result[0] = byte1;
        result[1] = byte2;
    }
    else if (code >= 0x0800 && code <= 0xFFFF)
    {
        uint8_t byte1 = 0xE0 | ((code >> 12) & 0x0F);
        uint8_t byte2 = 0x80 | ((code >> 6) & 0x3F);
        uint8_t byte3 = 0x80 | (code & 0x3F);
        result[0] = byte1;
        result[1] = byte2;
        result[2] = byte3;
    }
    else if (code >= 0x00010000 && code <= 0x001FFFFF)
    {
        uint8_t byte1 = 0xF0 | ((code >> 18) & 0x07);
        uint8_t byte2 = 0x80 | ((code >> 12) & 0x3F);
        uint8_t byte3 = 0x80 | ((code >> 6) & 0x3F);
        uint8_t byte4 = 0x80 | (code & 0x3F);
        result[0] = byte1;
        result[1] = byte2;
        result[2] = byte3;
        result[3] = byte4;
    }
    else if (code >= 0x00200000 && code <= 0x03FFFFFF)
    {
        uint8_t byte1 = 0xF8 | ((code >> 24) & 0x03);
        uint8_t byte2 = 0x80 | ((code >> 18) & 0x3F);
        uint8_t byte3 = 0x80 | ((code >> 12) & 0x3F);
        uint8_t byte4 = 0x80 | ((code >> 6) & 0x3F);
        uint8_t byte5 = 0x80 | (code & 0x3F);
        result[0] = byte1;
        result[1] = byte2;
        result[2] = byte3;
        result[3] = byte4;
        result[4] = byte5;
    }
    else if (code >= 0x04000000 && code <= 0x7FFFFFFF)
    {
        uint8_t byte1 = 0xFC | ((code >> 30) & 0x01);
        uint8_t byte2 = 0x80 | ((code >> 24) & 0x3F);
        uint8_t byte3 = 0x80 | ((code >> 18) & 0x3F);
        uint8_t byte4 = 0x80 | ((code >> 12) & 0x3F);
        uint8_t byte5 = 0x80 | ((code >> 6) & 0x3F);
        uint8_t byte6 = 0x80 | (code & 0x3F);
        result[0] = byte1;
        result[1] = byte2;
        result[2] = byte3;
        result[3] = byte4;
        result[4] = byte5;
        result[5] = byte6;
    }
    return result;
}

String::String()
        : length{0}, characters{nullptr}, refCount{new int(1)}, cachedHashCode{0}
{

}

String::String(const char *utf8Str)
{
    int count = Encoding::Utf8ToUtf16Count(utf8Str);
    if (count == -1)
    {
        throw Exception("illegal utf-8 characters input");
    }
    else
    {
        length = count;
        characters = new uint16_t[length];
        Encoding::Utf8ToUtf16(utf8Str, characters);
        refCount = new int(1);
        cachedHashCode = 0;
    }
}

String::String(const String &other)
{
    Copy(other);
}

String &String::operator=(const String &other) noexcept
{
    Copy(other);
    return *this;
}

String::~String()
{
    (*refCount)--;
    if ((*refCount) == 0)
    {
        delete[] characters;
        delete refCount;
    }
}

void String::Copy(const String &other)
{
    if (this != (&other))
    {
        length = other.length;
		characters = other.characters;
        refCount = other.refCount;
        cachedHashCode = other.cachedHashCode;
        (*refCount)++;
    }
}

int String::GetHashCode() const
{
    if (cachedHashCode != 0)
    {
        return cachedHashCode;
    }
    else
    {
        int hashCode = 0;
        for (int i = 0; i < length; i++)
        {
            hashCode = hashCode * 31 + characters[i];
        }
        return cachedHashCode = hashCode;
    }
}

String String::Empty{};
