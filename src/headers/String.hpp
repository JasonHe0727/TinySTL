#ifndef STRING_HPP
#define STRING_HPP


#include <cstdint>
#include <exception>

class Encoding
{
public:
    static int Utf8ToUtf16Count(const char *utf8);

    static void Utf8ToUtf16(const char *utf8, uint16_t *result);

    static uint8_t *Utf16CharacterToUtf8(uint16_t code);
};

class String
{
private:
    int length;
    uint16_t *characters;
    int *refCount;
    mutable int cachedHashCode;
public:
    String();

    String(const char *utf8Str);

    String(const String &other);

    String &operator=(const String &other) noexcept;

    ~String();

    const uint16_t &operator[](int index) const;

    int Length() const;

    int GetHashCode() const;

    static String Empty;
private:
    void Copy(const String &other);
};


inline const uint16_t &String::operator[](int index) const
{
    return characters[index];
}

inline int String::Length() const
{
    return length;
}

String String::Empty = String();
#endif //STRING_HPP
