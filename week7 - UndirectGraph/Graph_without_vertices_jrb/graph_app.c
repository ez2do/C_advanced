#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void printVertex(int v){
	printf("%-5d", v);
}

int main(){
	Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    printf("\nBFS: start from node 1 to 4 : ");
    BFS(g, 1, 4, printVertex);
    printf("\nShortest path from 1 to 4: ");
    printShortestPath(g, 1, 4);
    printf("\nBFS: start from node 1 to all : ");
    BFS(g, 1, -1, printVertex);
    printf("\nDFS: from node 1 to all: ");
    DFS(g, 1, -1, printVertex);
    printf("\n");

}