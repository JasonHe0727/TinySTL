#ifndef DIRECTED_DFS_HPP
#define DIRECTED_DFS_HPP
#include "Array.hpp"
#include "Digraph.hpp"

class DirectedDFS {
private:
	Array<bool> marked;
	void DFS(const Digraph& G, int v););
public:
	DirectedDFS(const Digraph& G, int src);
};

#endif // DIRECTED_DFS_HPP
