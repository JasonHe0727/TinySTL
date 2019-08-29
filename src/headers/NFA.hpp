#ifndef NFA_HPP
#define NFA_HPP
#include "Digraph.hpp"
#include "String.hpp"

class NFA {
private:
	String regexp;
	Array<Char> re; // match transitions
	int numOfStates; // number of states
	Digraph G; // epsilon transitions
public:
	explicit NFA(const String& regexp);
	bool Recognizes(const String& text);
};

#endif // NFA_HPP
