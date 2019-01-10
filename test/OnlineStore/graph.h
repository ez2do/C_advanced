#ifndef __JRB_GRAPH__
#define __JRB_GRAPH__

#include "libfdr/jrb.h"
#define INFINITY 9999999

typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
void addVertex(Graph g, int id, int weight);
int getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2, int length);
int getLength(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);
JRB BFS(Graph g, int start, int stop, void (*func)(int));
int shortestPath(Graph g, int start, int stop, int* output);
void DFS(Graph g, int start, int stop, void (*func)(int u));
int relax(Graph g, int u, int v, JRB parentList);
JRB dijkstra(Graph g, int start, int stop);
int shortestWeightedPath(Graph g, int start, int stop, int *path, int *length);

#endif