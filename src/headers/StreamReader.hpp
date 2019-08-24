#ifndef STREAM_READER_HPP
#define STREAM_READER_HPP
#include <cstdint>
#include <fstream>
#include "String.hpp"
#include "Option.hpp"

class StreamReader {
private:
	String path;
	std::ifstream stream;
public:
	StreamReader();
	explicit StreamReader(const String& path);
	StreamReader(const StreamReader&) = delete;
	StreamReader& operator=(const StreamReader&) = delete;

	Option<Char> Read();
	Option<String> ReadLine();
private:
	void StringToCStr(const String& s, char** result);
};

#endif // STREAM_READER_HPP
