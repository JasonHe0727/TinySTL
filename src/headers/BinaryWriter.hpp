#ifndef BINARY_WRITER_HPP
#define BINARY_WRITER_HPP

#include <fstream>
#include <cstdint>
#include "String.hpp"

class BinaryWriter {
private:
	String path;
	std::ofstream stream;
public:
	BinaryWriter() = default;
	BinaryWriter(const BinaryWriter&) = delete;
	BinaryWriter& operator=(const BinaryWriter&) = delete;

	explicit BinaryWriter(const String& path);

	void Write(uint8_t value);
private:
	std::string StringToCStr(const String& s);
};

#endif // BINARY_WRITER_HPP
