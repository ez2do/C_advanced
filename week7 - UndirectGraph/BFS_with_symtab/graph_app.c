#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void printVertex(int v){
	printf("\n%d", v);
}

int main(){
	Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 1);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 3, 1);
    addEdge(g, 3, 2);
    addEdge(g, 4, 5);
    addEdge(g, 5, 4);
    printf("\nBFS: start from node 1 to 4 : ");
    BFS(g, 1, 4, printVertex);
    printf("\n");
    printf("\nBFS: start from node 1 to all : ");
    BFS(g, 1, -1, printVertex);
    printf("\n");

}