#include "String.hpp"

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
//            throw std::exception("illegal utf-8 characters input");
            return -1;
        }
    }
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
            throw std::exception("illegal utf-8 characters input");
        }
    }
}
