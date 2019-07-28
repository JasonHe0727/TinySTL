#ifndef STRING_HPP
#define STRING_HPP


#include <cstdint>
#include <exception>

class Encoding
{
public:
    static int Utf8ToUtf16Count(const char *utf8);

    static void Utf8ToUtf16(const char *utf8, uint16_t *result);
};

class String
{
private:
    int length;
    uint16_t *characters;
    int *refCount;
public:
    String()
            : length{0}, characters{nullptr}, refCount{new int(1)}
    {

    }

    String(const char *utf8Str)
    {
        int count = Encoding::Utf8ToUtf16Count(utf8Str);
        if (count == -1)
        {
            throw std::exception("illegal utf-8 characters input");
        }
        else
        {
            length = count;
            characters = new uint16_t[length];
            Encoding::Utf8ToUtf16(utf8Str, characters);
            refCount = new int(1);
        }
    }

    String(const String &other)
    {
        Copy(other);
    }

    String &operator=(const String &other) noexcept
    {
        Copy(other);
        return *this;
    }

    const uint16_t &operator[](int index) const
    {
        return characters[index];
    }

    ~String()
    {
        (*refCount)--;
        if ((*refCount) == 0)
        {
            delete[] characters;
            delete refCount;
        }
    }
private:
    void Copy(const String &other)
    {
        if (this != (&other))
        {
            length = other.length;
            characters = new uint16_t[length];
            refCount = other.refCount;
            (*refCount)++;
        }
    }
};


#endif //STRING_HPP
