#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph createGraph(int sizemax){
	Graph G;
	G.matrix = (int*) malloc(sizeof(int) * sizemax * sizemax);
	G.maxsize = sizemax;
	for(int i = 0; i < sizemax; i++){
		for(int j = 0; j < sizemax; j++){
			*(G.matrix + i * sizemax + j) = 0;
		}
	}
	return G;
}

void addEdge(Graph g, int v1, int v2){
	*(g.matrix + v1 * g.maxsize + v2) = 1;
}

int adjacent(Graph g, int v1, int v2){
	return *(g.matrix + v1 * g.maxsize + v2);
}

int getAdjacentVertices(Graph g, int v1, int *output){
	int total = 0;
	for(int j = 0; j < g.maxsize; j++){
		if(*(g.matrix + v1 * g.maxsize + j) == 1){
			*(output + total) = j;
		}
	}
	return total;
}

void dropGraph(Graph g){
	free(g.matrix);
	free(&g);
}