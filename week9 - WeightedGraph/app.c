#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "libfdr/jval.h"
#include "libfdr/fields.h"

int main(){
	Graph g = createGraph();
	for(int i = 0; i < 6; i++)
		addVertex(g, i + 1, INFINITY);
	IS is = new_inputstruct("data.txt");
	while(get_line(is) >= 0){
		addEdge(g, strtol(is->fields[0], NULL, 10), strtol(is->fields[1], NULL, 10), strtol(is->fields[2], NULL, 10));
	}

	int s, t, length, path[1000];
	printf("Start: ");
	scanf("%d", &s);
	printf("Stop: ");
	scanf("%d", &t);
	int weight = shortestWeightedPath(g, s, t, path, &length);
	if (weight == INFINITY)
   		printf("No path between %d and %d\n", s, t);
	else {
	   printf("Path between %d and %d:", s, t);
	   for(int i = length - 1; i >= 0; i--) printf("%4d", path[i]);
	   printf("\nTotal weight: %d\n", weight);
	}
}