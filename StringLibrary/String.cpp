#include "String.hpp"
#include "Exception.hpp"

int codepoint_len(const uint32_t cp) {
    int len = 0;
    for (utf_t **u = utf; *u; ++u) {
        if ((cp >= (*u)->beg) && (cp <= (*u)->end)) {
            break;
        }
        ++len;
    }
    if (len > 4) /* Out of bounds */
        exit(1);

    return len;
}

int utf8_len(const char ch) {
    int len = 0;
    for (utf_t **u = utf; *u; ++u) {
        if ((ch & ~(*u)->mask) == (*u)->lead) {
            break;
        }
        ++len;
    }
    if (len > 4) { /* Malformed leading byte */
        exit(1);
    }
    return len;
}

char *to_utf8(const uint32_t cp) {
    static char ret[5];
    const int bytes = codepoint_len(cp);

    int shift = utf[0]->bits_stored * (bytes - 1);
    ret[0] = (cp >> shift & utf[bytes]->mask) | utf[bytes]->lead;
    shift -= utf[0]->bits_stored;
    for (int i = 1; i < bytes; ++i) {
        ret[i] = (cp >> shift & utf[0]->mask) | utf[0]->lead;
        shift -= utf[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}

uint32_t to_cp(const char chr[4]) {
    int bytes = utf8_len(*chr);
    int shift = utf[0]->bits_stored * (bytes - 1);
    uint32_t codep = (*chr++ & utf[bytes]->mask) << shift;

    for (int i = 1; i < bytes; ++i, ++chr) {
        shift -= utf[0]->bits_stored;
        codep |= ((char) *chr & utf[0]->mask) << shift;
    }

    return codep;
}

Char::Char(const char chr[4]) {
    int bytes = utf8_len(*chr);
    int shift = utf[0]->bits_stored * (bytes - 1);
    uint32_t codep = (*chr++ & utf[bytes]->mask) << shift;

    for (int i = 1; i < bytes; ++i, ++chr) {
        shift -= utf[0]->bits_stored;
        codep |= ((char) *chr & utf[0]->mask) << shift;
    }

    this->code = codep;
}

char *Char::str() {
    static char ret[5];
    const int bytes = codepoint_len(code);

    int shift = utf[0]->bits_stored * (bytes - 1);
    ret[0] = (code >> shift & utf[bytes]->mask) | utf[bytes]->lead;
    shift -= utf[0]->bits_stored;
    for (int i = 1; i < bytes; ++i) {
        ret[i] = (code >> shift & utf[0]->mask) | utf[0]->lead;
        shift -= utf[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}

String::String() : characters{nullptr}, _length{0} {

}

String::String(const char *s) : characters{nullptr}, _length{0} {
    const char *p = s;
    while (*p != '\0') {
        _length++;
        int len = utf8_len(*p);
        p += len;
    }
    characters = new Char[_length];
    int index = 0;
    while (*s != '\0') {
        int len = utf8_len(*s);
        characters[index] = Char(s);
        s += len;
        index++;
    }
}

String::String(const String &s) : characters{new Char[s._length]}, _length{_length} {
    for (int i = 0; i < _length; i++) {
        characters[i] = s.characters[i];
    }
}

String::String(String &&s) : characters{s.characters}, _length{s._length} {
    s.characters = nullptr;
    s._length = 0;
}

String::~String() {
    if (characters) {
        delete[] characters;
    }
}

String &String::operator=(String s) {
    characters = s.characters;
    _length = s._length;
    s.characters = nullptr;
    s._length = 0;
    return *this;
}

Char &String::at(int index) const {
    if (index < _length) {
        return characters[index];
    } else {
        throw IndexOutOfRangeException();
    }
}

bool String::operator==(const String &s) const {
    if (_length == s.length()) {
        for (int i = 0; i < s.length(); i++) {
            if (characters[i] != s.characters[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}


bool String::operator!=(const String &s) const {
    return !(*this == s);
}


String String::substr(int start, int length) {
    if (start + length <= _length) {
        String result;
        result.characters = new Char[length];
        result._length = length;
        for (int i = 0; i < length; i++) {
            result.characters[i] = characters[start + i];
        }
        return result;
    } else {
        throw IndexOutOfRangeException();
    }
}

String String::substr(int start) {
    return substr(start, size() - start);
}

String String::operator+=(const String &other) const {
    String res;
    res._length = size() + other.size();
    res.characters = new Char[size() + other.size()];
    for (int i = 0; i < size(); i++) {
        res.characters[i] = characters[i];
    }
    for (int i = 0; i < other.size(); i++) {
        res.characters[size() + i] = other.characters[i];
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    for (int i = 0; i < s._length; i++) {
        out << s.characters[i].str();
    }
    return out;
}

String operator+(const String &lhs, const String &rhs) {
    return lhs += rhs;
}