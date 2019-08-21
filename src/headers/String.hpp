#ifndef STRING_HPP
#define STRING_HPP

#include <cstdint>
#include "Array.hpp"
#include "Char.hpp"

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
    Char *characters;
    int *refCount;
    mutable int cachedHashCode;
public:
    String();

    String(const char *utf8Str);

    String(const String &other);

    String &operator=(const String &other) noexcept;

	String(String&& other);

	String& operator=(String&& other) noexcept;

    ~String();

    Char operator[](int index) const;

    int Length() const;

    int GetHashCode() const;

	String Slice(int startIndex, int endIndex) const;

	int IndexOf(const String& value) const;

	int IndexOf(const String& value, int startIndex) const;

	Array<String> Split(const String& separator) const;

	static String Join(const String& separator, const Array<String>& values);

	Array<Char> ToCharArray() const;

	friend bool operator==(const String& x, const String& y);

	friend bool operator!=(const String& x, const String& y);

    static String Empty;

private:
    void Copy(const String &other);
};


inline Char String::operator[](int index) const
{
    return characters[index];
}

inline int String::Length() const
{
    return length;
}

#endif //STRING_HPP
