#ifndef FILE_HPP
#define FILE_HPP
#include "Array.hpp"
#include "String.hpp"

class File {
public:
	static Array<String> ReadAllLines(const String& path);
	static void WriteAllLines(const String& path, const Array<String>& lines);
};

#endif // FILE_HPP
