#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct{
	int *matrix;
	int maxsize;
}Graph;

Graph *createGraph(int sizemax);

void addEdge(Graph *graph, int v1, int v2);

int adjacent(Graph *graph, int v1, int v2); //return 1 if adjacent, else 0

//return the number of adjacent vertices and put them in the output array
int getAdjacentVertices(Graph *graph, int v1, int *output);

void dropGraph(Graph *graph);

#endif