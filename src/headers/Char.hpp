#ifndef CHAR_HPP
#define CHAR_HPP

#include <cstdint>

class Char {
private:
	uint16_t value;
public:
	Char(): value{0} {
	}

	Char(uint16_t value): value{value} {
	}

	friend inline bool operator==(const Char& left, const Char& right) {
		return left.value == right.value;
	}

	friend inline bool operator!=(const Char& left, const Char& right) {
		return left.value != right.value;
	}

	inline operator int() {
		return value;
	}

	int ToInt() const {
		return value;
	}
};

#endif // CHAR_HPP
