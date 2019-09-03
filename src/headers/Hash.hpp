#ifndef HASH_HPP
#define HASH_HPP

#include <cstdint>

template <typename T>
struct Hash {
	int operator()(const T& input) const;
};

template <>
struct Hash<int32_t> {
	int operator()(const int32_t& input) const {
		if(input >= 0) {
			return input;
		} else {
			return -input;
		}
	}
};

template <>
struct Hash<int64_t> {
	int operator()(const int64_t& input) const {
		return static_cast<int>(input ^ (input >> 32));
	}
};

#endif // HASH_HPP
