#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "direct_graph.h"

Graph globalGraph;

void printVertex(int u){
	printf("%-5s", getVertex(globalGraph, u));
}

int main(){
	Graph g = createGraph();
	globalGraph = g;
    char *tmp;
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addVertex(g, 4, "V4");
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 0, 2);
    addEdge(g, 2, 3);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    int in[20];
    int out[20];
    printf("In degree of node %d: %d\n", 1, inDegree(g, 1, in));
    for(int i = 0; i < inDegree(g, 1, in); i++)
    	printf("%s  ", getVertex(g, in[i]));

    printf("\n");

    printf("Out degree of node %d: %d\n", 1, outDegree(g, 1, out));
    for(int i = 0; i < outDegree(g, 1, in); i++){
        tmp = getVertex(g, out[i]);
    	printf("%s  ", tmp);
    }
    printf("\n");
    printf("Shortest path from 0 to 3: ");
    printShortestPath(g, 0, 3);
    printf("BFS: ");
    BFS(g, 0, -1, printVertex);
    printf("\nDFS: ");
    DFS(g, 0, -1, printVertex);
    printf("\n");
    if (DAG(g)) printf("The graph is acycle\n");
    else printf("Have cycles in the graph\n");

    int topoArray[20];
    printf("Topo Sort:\n");
    int total = topoSort(g, topoArray);
    for(int i = 0; i < total; i++){
    	printf("%d  ", topoArray[i]);
    }
    printf("\n");

}