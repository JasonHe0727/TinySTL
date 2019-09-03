#include "DirectedDFS.hpp"

DirectedDFS::DirectedDFS(const Digraph& G, int src): marked(G.numOfVertices()) {
	for(int i = 0; i < marked.Size(); i++) {
		marked[i] = false;
	}
	DFS(G, src);
}

DirectedDFS::DirectedDFS(const Digraph& G, const List<int>& sources): marked(G.numOfVertices())
{
	for(int s : sources) {
		if(not marked[s]) {
			DFS(G, s);
		}
	}
}

void DirectedDFS::DFS(const Digraph& G, int v) {
	marked[v] = true;
	for(int w : G.Adj(v)) {
		if(not marked[w]) {
			DFS(G, w);
		}
	}
}
