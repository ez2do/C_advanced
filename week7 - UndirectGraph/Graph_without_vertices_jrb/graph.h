#ifndef __JRB_GRAPH__
#define __JRB_GRAPH__

#include "libfdr/jrb.h"
typedef JRB Graph;

Graph createGraph();
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);
JRB BFS(Graph g, int start, int stop, void (*func)(int));
void printShortestPath(JRB prevNodeTab, int start, int stop);
void DFS(Graph g, int start, int stop, void (*func)(int u));

#endif