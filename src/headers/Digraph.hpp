#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP
#include "List.hpp"
#include "Array.hpp"

class Digraph {
private:
	int V;
	int E;
	Array<List<int>> adj;
public:
	Digraph(int V);
	inline int numOfVertices() const {
		return V;
	}
	inline int numOfEdges() const {
		return E;
	}
	void AddEdge(int v, int w);
	inline const List<int>& Adj(int index) const {
		return adj[index];
	}
};

#endif // DIGRAPH_HPP
