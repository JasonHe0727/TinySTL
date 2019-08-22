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
	static bool Less(const String& v, const String& w, int width);
};

class KMP {
private:
	String pattern;
	Array<Array<int>> dfa;
public:
	KMP();
	KMP(const String& pattern, int radix);
	KMP(const KMP&) = delete;
	KMP& operator=(const KMP&) = delete;
	int Search(const String& text) const;
};

class BoyerMoore {
private:
	String pattern;
	Array<int> right;
public:
	BoyerMoore();
	BoyerMoore(const String& pattern, int radix);
	int Search(const String& text) const;
};
#endif // STRING_ALGORITHMS_HPP
