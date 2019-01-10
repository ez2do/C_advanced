#ifndef __DIRECT_GRAPH_H__
#define __DIRECT_GRAPH_H__

#include "libfdr/jrb.h"

typedef struct{
	JRB edges;
	JRB vertices;
}Graph;

Graph createGraph();
void addVertex(Graph g, int id, char* name);
char* getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2);
int hasEdge(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
int inDegree(Graph g, int v1, int *output);
int outDegree(Graph g, int v1, int *output);
JRB BFS(Graph g, int start, int stop, void (*func)(int));
int shortestPath(Graph g, int start, int stop, int *output);
void printShortestPath(Graph g, int start, int stop);
void DFS(Graph g, int start, int stop, void (*func)(int u));
int DAG(Graph g);
int topoSort(Graph g, int* output);
void dropGraph(Graph g);

#endif