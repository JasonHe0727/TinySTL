#include "File.hpp"
#include "StreamReader.hpp"
#include "StreamWriter.hpp"
#include "List.hpp"

Array<String> File::ReadAllLines(const String& path) {
	StreamReader reader(path);
	List<String> list;
	while(auto line = reader.ReadLine()) {
		list.Add(line.Get());
	}
	Array<String> lines;
	for(int i = 0; i < list.Size(); i++) {
		lines[i] = list[i];
	}
	return lines;
}

void File::WriteAllLines(const String& path, const Array<String>& lines) {
	StreamWriter writer(path);
	for(int i = 0; i < lines.Size(); i++) {
		const String& line = lines[i];
		writer.WriteLine(line);
	}
}
