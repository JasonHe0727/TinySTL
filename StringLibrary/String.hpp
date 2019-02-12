#ifndef STRINGLIBRARY_STRING_HPP
#define STRINGLIBRARY_STRING_HPP

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <vector>
#include <iostream>
#include <bits/functexcept.h>

typedef struct {
    char mask;    /* char data will be bitwise AND with this */
    char lead;    /* start bytes of current char in utf-8 encoded character */
    uint32_t beg; /* beginning of codepoint range */
    uint32_t end; /* end of codepoint range */
    int bits_stored; /* the number of bits from the codepoint that fits in char */
} utf_t;

static utf_t *utf[] = {
        /*             mask        lead        beg      end       bits */
        [0] = new utf_t{0b00111111, (char) 0b10000000, 0, 0, 6},
        [1] = new utf_t{0b01111111, (char) 0b00000000, 0000, 0177, 7},
        [2] = new utf_t{0b00011111, (char) 0b11000000, 0200, 03777, 5},
        [3] = new utf_t{0b00001111, (char) 0b11100000, 04000, 0177777, 4},
        [4] = new utf_t{0b00000111, (char) 0b11110000, 0200000, 04177777, 3},
        new utf_t{0},
};

/* All lengths are in bytes */
int codepoint_len(const uint32_t cp); /* len of associated utf-8 char */
int utf8_len(const char ch);          /* len of utf-8 encoded char */

char *to_utf8(const uint32_t cp);

uint32_t to_cp(const char chr[4]);

class Int;

class Char;

class String;

class Char {
private:
    uint32_t code;
public:
    Char() : code{0} {

    }

    Char(const char chr[4]);

    Char(uint32_t code) : code{code} {

    }

    explicit operator uint32_t() const {
        return code;
    }

    char *str();

    bool operator==(const Char &c) const {
        return code == c.code;
    }

    bool operator!=(const Char &c) const {
        return code != c.code;
    }

    friend std::ostream &operator<<(std::ostream &out, Char &c) {
        out << c.str();
        return out;
    }

};

class String {
private:
    Char *characters;
    int _length;

public:
    /*
     * default constructor
     */
    String();

    /*
     * c-style string
     */
    String(const char *s);

    /*
     * copy constructor
     */
    String(const String &s);

    /*
     * move constructor
     */
    String(String &&s);

    ~String();

    int length() const { return _length; }

    int size() const { return _length; }

    String &operator=(String s);

    Char &at(int index) const;

    bool operator==(const String &s) const;

    bool operator!=(const String &s) const;

    String substr(int start, int length);

    String substr(int start);

    String operator+=(const String &other) const;

    friend std::ostream &operator<<(std::ostream &out, const String &s);
};

String operator+(const String &lhs, const String &rhs);

#endif //STRINGLIBRARY_STRING_HPP