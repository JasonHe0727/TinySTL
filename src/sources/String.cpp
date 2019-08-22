#include "String.hpp"
#include "Exception.hpp"
#include <cmath>

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
			characters[i] = utf16Str[i];
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

String::String(String&& other) {
	Copy(other);
}

String& String::operator=(String&& other) noexcept
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
