#ifndef ENCODING_HPP
#define ENCODING_HPP
#include <cstdint>

class Encoding
{
public:
    static int Utf8ToUtf16Count(const char *utf8);

    static void Utf8ToUtf16(const char *utf8, uint16_t *result);

    static uint8_t *Utf16CharacterToUtf8(uint16_t code);
};

#endif // ENCODING_HPP
