#include "StreamWriter.hpp"
#include "Encoding.hpp"

StreamWriter::StreamWriter(): path{}, stream{} {
}

StreamWriter::StreamWriter(const String& path)
	: path{path}, stream{StringToCStr(path)} {
	
}

void StreamWriter::WriteChar(const Char& c) {
	uint8_t* utf8Str = Encoding::Utf16CharacterToUtf8(static_cast<uint16_t>(c.ToInt()));
	while((*utf8Str) != '\0') {
		stream.put(static_cast<uint8_t>(*utf8Str));
		utf8Str++;
	}
}

void StreamWriter::Write(const String& s) {
	for(int i = 0; i < s.Size(); i++) {
		WriteChar(s[i]);
	}
}

void StreamWriter::WriteLine(const String& s) {
	for(int i = 0; i < s.Size(); i++) {
		WriteChar(s[i]);
	}
	stream << std::endl;
}

std::string StreamWriter::StringToCStr(const String& s) {
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
