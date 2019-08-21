#ifndef STRING_ALGORITHMS_HPP
#define STRING_ALGORITHMS_HPP

#include "String.hpp"

class LSD {
public:
	static void Sort(Array<String>& array, int width, int radix);
};

class MSD {
public:
	static void Sort(Array<String>& array, int radix);
private:
	static int CharAt(const String& s, int width);
	static void Sort(Array<String>& array, int low, int high, int width, Array<String>& aux, int radix);
	static void InsertionSort(Array<String>& array, int low, int high, int width);
};
#endif // STRING_ALGORITHMS_HPP
