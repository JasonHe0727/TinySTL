#include "NFA.hpp"
#include "Stack.hpp"
#include "DirectedDFS.hpp"
#include "List.hpp"

NFA::NFA(const String& regexp)
	: regexp{regexp}, re{regexp.ToCharArray()}
	, numOfStates{re.Length()}, G(numOfStates + 1) {
	Stack<int> ops;

	for(int i = 0; i < numOfStates + 1; i++) {
		int lp = i;
		if(re[i] == Char('(') || re[i] == Char('|')) {
			ops.Push(i);
		} else if(re[i] == Char(')')) {
			int _or = ops.Top();
			ops.Pop();
			if(re[_or] == Char('|')) {
				lp = ops.Top();
				ops.Pop();
				G.AddEdge(lp, _or + 1);
				G.AddEdge(_or, i);
			} else {
				lp = _or;
			}
		}

		if(i < numOfStates - 1 && re[i + 1] == Char('*')) { // lookahead
			G.AddEdge(lp, i + 1);
			G.AddEdge(i + 1, lp);
		}
		if(re[i] == Char('(') || re[i] == Char('*') || re[i] == Char(')')) {
			G.AddEdge(i, i + 1);
		}
	}
}

bool NFA::Recognizes(const String& text) {
	List<int> pc;
	DirectedDFS dfs(G, 0);
	for(int v = 0; v < G.numOfVertices(); v++) {
		if(dfs.Marked(v)) {
			pc.Add(v);
		}
	}
	for(int i = 0; i < text.Length(); i++) {
		List<int> match;
		for(int v : pc) {
			if(v < numOfStates) {
				if(re[v] == text[i] || re[v] == Char('.')) {
					match.Add(v + 1);
				}
			}
		}
		pc = List<int>();
		dfs = DirectedDFS(G, match);
		for(int v = 0; v < G.numOfVertices(); v++) {
			if(dfs.Marked(v)) {
				pc.Add(v);
			}
		}
	}
	for(int v : pc) {
		if(v == numOfStates) {
			return true;
		}
	}
	return false;
}
