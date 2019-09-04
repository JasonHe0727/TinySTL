#include "BinaryWriter.hpp"
#include "Encoding.hpp"

BinaryWriter::BinaryWriter(const String& path)
	: path{path}, stream{StringToCStr(path)} {
	
}

void BinaryWriter::Write(uint8_t value) {
	stream.put(value);
}

std::string BinaryWriter::StringToCStr(const String& s) {
	std::string result;
	for(int i = 0; i < s.Size(); i++) {
		uint8_t* c = Encoding::Utf16CharacterToUtf8(static_cast<uint16_t>(s[i].ToInt()));
		while((*c) != '\0') {
			result.push_back(static_cast<char>(*c));
			c++;
		}
	}
	return result;
}
