// Graph ADT interface ... COMP9024 21T3
#include <stdbool.h>

typedef struct GraphRep* Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
	Vertex v;
	Vertex w;
} Edge;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void changeEdge(Graph g, Vertex v, Vertex w, int c);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);