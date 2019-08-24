#ifndef STRINGBUILDER_HPP
#define STRINGBUILDER_HPP
#include "String.hpp"
#include "List.hpp"

class StringBuilder {
private:
	List<Char> buffer;
public:
	StringBuilder() = default;
	StringBuilder(const StringBuilder&) = delete;
	StringBuilder operator=(const StringBuilder&) = delete;

	const Char& operator[](int index) const;
	int Size() const;

	void Append(const Char& c);
	void Append(const String& s);
	void Pop();

	String ToString() const;
};

inline const Char& StringBuilder::operator[](int index) const {
	return buffer[index];
}

inline int StringBuilder::Size() const {
	return buffer.Size();
}

#endif //STRINGBUILDER_HPP
