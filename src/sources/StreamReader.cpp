#include "StreamReader.hpp"
#include "List.hpp"

StreamReader::StreamReader(): path{}, stream{} {
}

StreamReader::StreamReader(const String& path)
	: path{path}, stream{} {
}

void StreamReader::StringToCStr(const String& s, char** result) {
	Array<Char> characters = s.ToCharArray();
	List<char> resChars;
	for(int i = 0; i < characters.Size(); i++) {
		uint8_t* c = Utf16CharacterToUtf8(characters[i]);
		while(c != '\0') {
			resChars.Add(static_cast<char>(c));
			c++;
		}
	}
}
