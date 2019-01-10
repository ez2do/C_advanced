#ifndef __JRB_GRAPH__
#define __JRB_GRAPH__

#include "libfdr/jrb.h"
typedef JRB Graph;

Graph createGraph();
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);
void BFS(Graph g, int start, int stop, void (*func)(int));
/*
start is the first vertex to visit
stop is vertex to be visited at the end, if stop = -1, all the vertex 
will be visited
func is a pointer to the function that process on the visited vertices
*/

#endif