#include "Digraph.hpp"

Digraph::Digraph(int V): V{V}, E{0}, adj(V) {
}
void Digraph::AddEdge(int v, int w) {
	adj[v].Add(w);
	E++;
}
