#include "StreamReader.hpp"
#include "List.hpp"
#include "StringBuilder.hpp"
#include "Encoding.hpp"

StreamReader::StreamReader(): path{}, stream{} {
}

StreamReader::StreamReader(const String& path)
	: path{path}, stream{StringToCStr(path)} {
	
}

Option<Char> StreamReader::Read() {
	int code = stream.get();
	if(stream.fail()) {
		return Option<Char>();
	} else {
		if (((code >> 7) & 0xFF) == 0x0)
		{
			return Char(code);
		}
		else if (((code >> 5) & 0xFF) == 0x6)
		{
			uint8_t code2 = stream.get();
			int32_t byte1 = (code & 0x1F) << 6;
			int32_t byte2 = code2 & 0x3F;
			uint16_t utf16 = byte1 | byte2;

			return Char(utf16);
		}
		else if (((code >> 4) & 0xFF) == 0xE)
		{
			uint8_t code2 = stream.get();
			uint8_t code3 = stream.get();

			int32_t byte1 = (code & 0x0F) << 12;
			int32_t byte2 = (code2 & 0x3F) << 6;
			int32_t byte3 = code3 & 0x3F;
			uint16_t utf16 = byte1 | byte2 | byte3;

			return Char(utf16);
		}
		else if (((code >> 3) & 0xFF) == 0x1E)
		{
			uint8_t code2 = stream.get();
			uint8_t code3 = stream.get();
			uint8_t code4 = stream.get();

			int32_t byte1 = (code & 0x07) << 18;
			int32_t byte2 = (code2 & 0x3F) << 12;
			int32_t byte3 = (code3 & 0x3F) << 6;
			int32_t byte4 = code4 & 0x3F;
			uint16_t utf16 = byte1 | byte2 | byte3 | byte4;

			return Char(utf16);
		}
		else if (((code >> 2) & 0xFF) == 0x3E)
		{
			uint8_t code2 = stream.get();
			uint8_t code3 = stream.get();
			uint8_t code4 = stream.get();
			uint8_t code5 = stream.get();

			int32_t byte1 = (code & 0x03) << 24;
			int32_t byte2 = (code2 & 0x3F) << 18;
			int32_t byte3 = (code3 & 0x3F) << 12;
			int32_t byte4 = (code4 & 0x3F) << 6;
			int32_t byte5 = code5 & 0x3F;
			uint16_t utf16 = byte1 | byte2 | byte3 | byte4 | byte5;

			return Char(utf16);
		}
		else if (((code >> 1) & 0xFF) == 0x7E)
		{
			uint8_t code2 = stream.get();
			uint8_t code3 = stream.get();
			uint8_t code4 = stream.get();
			uint8_t code5 = stream.get();
			uint8_t code6 = stream.get();

			int32_t byte1 = (code & 0x01) << 30;
			int32_t byte2 = (code2 & 0x3F) << 24;
			int32_t byte3 = (code3 & 0x3F) << 18;
			int32_t byte4 = (code4 & 0x3F) << 12;
			int32_t byte5 = (code5 & 0x3F) << 6;
			int32_t byte6 = code6 & 0x3F;
			uint16_t utf16 = byte1 | byte2 | byte3 | byte4 | byte5 | byte6;

			return Char(utf16);
		} else {
			return Option<Char>();
		}
	}
}

Option<String> StreamReader::ReadLine() {
	static Char END_LINE = Char('\n');
	StringBuilder builder;
	while(Option<Char> c = Read()) {
		if(c.Get() == END_LINE) {
			break;
		} else {
			builder.Append(c.Get());
		}
	}
	if(not stream.fail()) {
		return builder.ToString();
	} else {
		return Option<String>();
	}
}

std::string StreamReader::StringToCStr(const String& s) {
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
