#ifndef STRING_HPP
#define STRING_HPP

#include "Array.hpp"
#include "Char.hpp"
#include "Hash.hpp"

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

	explicit String(const Array<Char>& array);

    String(const String &other);

    String &operator=(const String &other) noexcept;

	String(String&& other);

	String& operator=(String&& other) noexcept;

    ~String();

    Char operator[](int index) const;

    int Length() const;

	int Size() const;

    int GetHashCode() const;

	String Slice(int startIndex, int endIndex) const;

	int IndexOf(const String& value) const;

	int IndexOf(const String& value, int startIndex) const;

	Array<String> Split(const String& separator) const;

	static String Join(const String& separator, const Array<String>& values);

	Array<Char> ToCharArray() const;

	friend bool operator==(const String& x, const String& y);

	friend bool operator!=(const String& x, const String& y);
	
	friend bool operator<(const String& x, const String& y);

	friend bool operator>(const String& x, const String& y);

	friend bool operator<=(const String& x, const String& y);

	friend bool operator>=(const String& x, const String& y);

	int CompareTo(const String& other) const;

	friend String operator+(const String& x, const Char& y);

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

inline int String::Size() const
{
    return length;
}

template <>
struct Hash<String> {
	int operator()(const String& input) const {
		return input.GetHashCode();
	}
};

#endif //STRING_HPP
