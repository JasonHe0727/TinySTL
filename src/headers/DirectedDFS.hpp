#ifndef DIRECTED_DFS_HPP
#define DIRECTED_DFS_HPP
#include "Array.hpp"
#include "Digraph.hpp"
#include "List.hpp"

class DirectedDFS {
private:
	Array<bool> marked;
	void DFS(const Digraph& G, int v);
public:
	DirectedDFS(const Digraph& G, int src);
	DirectedDFS(const Digraph& G, const List<int>& sources);
	inline bool Marked(int v) const {
		return marked[v];
	}
};

#endif // DIRECTED_DFS_HPP
