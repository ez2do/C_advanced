#ifndef __DIRECT_GRAPH_H__
#define __DIRECT_GRAPH_H__

#include "libfdr/jrb.h"

typedef struct{
	JRB edges;
	JRB vertices;
	JRB reverseVertices;
}Graph;

Graph createGraph();
void addVertex(Graph g, int id, char* name);
void addRVertex(Graph g, char *name, int id);
char* getVertex(Graph g, int id);
int getID(Graph g, char *name);
void addEdge(Graph g, int v1, int v2);
int hasEdge(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
int inDegree(Graph g, int v1, int *output);
int outDegree(Graph g, int v1, int *output);
int DAG(Graph g);
JRB BFS(Graph g, int start, int stop, void (*func)(int));
void printShortestPath(Graph g, int start, int stop);
void DFS(Graph g, int start, int stop, void (*func)(int u));
void dropGraph(Graph g);

#endif