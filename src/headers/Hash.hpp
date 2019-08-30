#ifndef HASH_HPP
#define HASH_HPP

template <typename T>
struct Hash {
	int operator()(const T& input) const;
};

template <>
struct Hash<int> {
	int operator()(const int& input) const {
		if(input >= 0) {
			return input;
		} else {
			return -input;
		}
	}
};

#endif // HASH_HPP
