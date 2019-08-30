#include "String.hpp"
#include "Exception.hpp"
#include "Encoding.hpp"
#include <cmath>

String::String()
        : length{0}, characters{nullptr}, refCount{new int(1)}, cachedHashCode{0}
{

}

String::String(const char *utf8Str)
        : length{0}, characters{nullptr}, refCount{new int(1)}, cachedHashCode{0}
{
    int count = Encoding::Utf8ToUtf16Count(utf8Str);
    if (count == -1)
    {
        throw Exception("illegal utf-8 characters input");
    }
    else
    {
        length = count;
        characters = new Char[length];
		uint16_t* utf16Str = new uint16_t[length];
        Encoding::Utf8ToUtf16(utf8Str, utf16Str);
		for(int i = 0; i < length; i++) {
			characters[i] = Char(utf16Str[i]);
		}
		delete[] utf16Str;
        refCount = new int(1);
        cachedHashCode = 0;
    }
}

String::String(const Array<Char>& array)
        : length{array.Size()}, characters{new Char[length]}, refCount{new int(1)}, cachedHashCode{0}
{
	for(int i = 0; i < length; i++) {
		characters[i] = array[i];
	}
}

String::String(const String &other)
{
    Copy(other);
}

String& String::operator=(const String &other) noexcept
{
    Copy(other);
    return *this;
}

String::String(String&& other)
	: length{other.length}, characters{other.characters}, refCount{other.refCount}, cachedHashCode{other.cachedHashCode} {
	other.length = 0;
	other.characters = nullptr;
	other.refCount = nullptr;
	other.cachedHashCode = 0;
}

String& String::operator=(String&& other) noexcept
{
	length = other.length;
	characters = other.characters;
	refCount = other.refCount;
	cachedHashCode = other.cachedHashCode;

	other.length = 0;
	other.characters = nullptr;
	other.refCount = nullptr;
	other.cachedHashCode = 0;

	return *this;
}

String::~String()
{
	if(refCount) {
		(*refCount)--;
		if ((*refCount) == 0)
		{
			delete[] characters;
			delete refCount;
		}
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
            hashCode = hashCode * 31 + characters[i].ToInt();
        }
        return cachedHashCode = hashCode;
    }
}

String String::Slice(int startIndex, int endIndex) const {
	String result;
	result.length = endIndex - startIndex;
	result.characters = new Char[result.length];
	for(int i = startIndex; i < endIndex; i++) {
		result.characters[i - startIndex] = operator[](i);
	}
	return result;
}

int String::IndexOf(const String& value) const {
	return IndexOf(value, 0);
}

int String::IndexOf(const String& value, int startIndex) const {
	for(int i = startIndex; i < Length(); i++) {
		bool success = true;
		for(int j = 0; j < value.Length(); j++) {
			if(operator[](i + j) != value[j]) {
				success = false;
				break;
			}
		}
		if(success) {
			return i;
		}
	}
	return (-1);
}

Array<String> String::Split(const String& separator) const {
	Array<int> sepList(length);
	Array<int> lengthList(length);
	int count = 0;
	int pos = 0;
	while (pos < Length()) {
		int index = IndexOf(separator, pos);
		if(index != -1) {
			sepList[count] = pos;
			lengthList[count] = index - pos;
			count++;
			pos = index + separator.Length();
		} else {
			break;
		}
	}
	if(pos < Length()) {
		sepList[count] = pos;
		lengthList[count] = Length() - pos;
		count++;
	}
	Array<String> items(count);
	for(int i = 0; i < count; i++) {
		items[i] = Slice(sepList[i], sepList[i] + lengthList[i]);
	}
	return items;
}

String String::Join(const String& separator, const Array<String>& values) {
	int count = 0;
	for(int i = 0; i < values.Length(); i++) {
		count = count + values[i].Length();
	}
	count = count + (values.Length() - 1) * separator.Length();

	String result;
	result.length = count;
	result.characters = new Char[count];
	int index = 0;
	for(int i = 0; i < values.Length(); i++) {
		if(i != 0) {
			for(int k = 0; k < separator.Length(); k++) {
				result.characters[index] = separator[k];
				index++;
			}
		}
		const String& value = values[i];
		for(int j = 0; j < value.Length(); j++) {
			result.characters[index] = value[j];
			index++;
		}
	}
	return result;
}

Array<Char> String::ToCharArray() const {
	Array<Char> array(length);
	for(int i = 0; i < length; i++) {
		array[i] = characters[i];
	}
	return array;
}

bool operator==(const String& x, const String& y) {
	if(&x == &y) {
		return true;
	} else {
		if(x.cachedHashCode != 0 && y.cachedHashCode != 0) {
			if(x.cachedHashCode != y.cachedHashCode) {
				return false;
			}
		}
		if(x.Length() != y.Length()) {
			return false;
		} else {
			int n = x.Length();
			for(int i = 0; i < n; i++) {
				if(x.characters[i] != y.characters[i]) {
					return false;
				}
			}
			return true;
		}
	}
}

bool operator!=(const String& x, const String& y) {
	return !(x == y);
}

bool operator>(const String& x, const String& y) {
	return x.CompareTo(y) > 0;
}

bool operator<(const String& x, const String& y) {
	return x.CompareTo(y) < 0;
}

bool operator>=(const String& x, const String& y) {
	return x.CompareTo(y) >= 0;
}

bool operator<=(const String& x, const String& y) {
	return x.CompareTo(y) <= 0;
}

int String::CompareTo(const String& other) const {
	if(this == &other) {
		return 0;
	} else {
		int minN = std::min(Length(), other.Length());
		for(int i = 0; i < minN; i++) {
			Char x = characters[i];
			Char y = other.characters[i];
			if(x > y) {
				return (1);
			} else if(x < y) {
				return (-1);
			}
		}
		if(Length() > other.Length()) {
			return 1;
		} else if(Length() < other.Length()) {
			return -1;
		} else {
			return 0;
		}
	}
}

String operator+(const String& x, const Char& y) {
	String res;
	res.length = x.Length() + 1;
	res.characters = new Char[res.length];
	for(int i = 0; i < x.Length(); i++) {
		res.characters[i] = x[i];
	}
	res.characters[x.Length()] = y;
	return res;
}

String String::Empty{};
