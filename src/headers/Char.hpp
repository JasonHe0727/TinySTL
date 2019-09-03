#ifndef CHAR_HPP
#define CHAR_HPP

#include <cstdint>
#include "Hash.hpp"

class Char {
private:
	uint16_t value;
public:
	Char(): value{0} {
	}

	explicit Char(uint16_t value): value{value} {
	}

	friend inline bool operator==(const Char& left, const Char& right) {
		return left.value == right.value;
	}

	friend inline bool operator!=(const Char& left, const Char& right) {
		return left.value != right.value;
	}

	friend inline bool operator>(const Char& left, const Char& right) {
		return left.value > right.value;
	}

	friend inline bool operator<(const Char& left, const Char& right) {
		return left.value < right.value;
	}

	friend inline bool operator>=(const Char& left, const Char& right) {
		return left.value >= right.value;
	}

	friend inline bool operator<=(const Char& left, const Char& right) {
		return left.value <= right.value;
	}

	friend inline Char operator+(const Char& left, const int& right) {
		return Char(left.value + right);
	}

	friend inline Char operator-(const Char& left, const int& right) {
		return Char(left.value - right);
	}

	inline int ToInt() const {
		return value;
	}
};

template <>
struct Hash<Char> {
	int operator()(const Char& input) const {
		return input.ToInt();
	}
};
#endif // CHAR_HPP
