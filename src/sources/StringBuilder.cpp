#include "StringBuilder.hpp"

void StringBuilder::Append(const Char& c) {
	buffer.Add(c);
}

void StringBuilder::Append(const String& s) {
	for(int i = 0; i < s.Size(); i++) {
		buffer.Add(s[i]);
	}
}

void StringBuilder::Pop() {
	buffer.Pop();
}

String StringBuilder::ToString() const {
	Array<Char> characters(buffer.Size());
	for(int i = 0; i < buffer.Size(); i++) {
		characters[i] = buffer[i];
	}
	return String(characters);
}
