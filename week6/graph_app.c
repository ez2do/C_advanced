#include <stdio.h>
#include <stdlib.h>
#include "jrb_graph.h"

int main(){
	int i, n, m, p, output[10];
	Graph g = createGraph(10);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);
	addEdge(g, 2, 3);
	n = getAdjacentVertices(g, 1, output);

	if(n == 0)
		printf("No adjacent vertices of node 1\n");
	else{
		printf("Number of adjacent nodes of 1: %d\n", n);
		for(int i = 0; i < n; i++)
			printf("%d\t", output[i]);
	}

	m = getAdjacentVertices(g, 2, output);
	printf("\nNumber of adjacent nodes of 2: %d\n", m);
	for(int i = 0; i < m; i++)
		printf("%d\t", output[i]);

	p = getAdjacentVertices(g, 3, output);
	printf("\nNumber of adjacent nodes of 3: %d\n", p);
	for(int i = 0; i < p; i++)
		printf("%d\t", output[i]);

	printf("\n");
}