#ifndef STREAM_WRITER_HPP
#define STREAM_WRITER_HPP

#include <fstream>
#include "String.hpp"

class StreamWriter {
private:
	String path;
	std::ofstream stream;
public:
	StreamWriter();
	explicit StreamWriter(const String& path);
	StreamWriter(const StreamWriter&) = delete;
	StreamWriter& operator=(const StreamWriter&) = delete;

	void WriteChar(const Char& c);
	void Write(const String& s);
	void WriteLine(const String& s);
private:
	std::string StringToCStr(const String& s);
};
#endif // STREAM_WRITER_HPP
