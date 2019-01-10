#ifndef __JRB_GRAPH__
#define __JRB_GRAPH__

#include "libfdr/jrb.h"

typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
void addVertex(Graph g, int id, char* name);
char* getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2, int distance);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);
JRB BFS(Graph g, int start, int stop, void (*func)(int));
int shortestPath(Graph g, int start, int stop, int* output);
void DFS(Graph g, int start, int stop, void (*func)(int u));
int getDistance(Graph g, int v1, int v2);

#endif