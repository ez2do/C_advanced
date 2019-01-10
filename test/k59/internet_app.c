#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "libfdr/fields.h"
#include "libfdr/jrb.h"
#include "libfdr/jval.h"

Graph globalGraph;

int main(){
	Graph g = createGraph();
	globalGraph = g;

	IS is = new_inputstruct("ip.txt");
	int part = 0; //part = 1 to get ip address, part = 2 to get distance
	while(get_line(is) >= 0){
		if(is->NF == 1){
			part++;
			int n = atoi(is->text1);
			continue;
		}
		if(part == 1){
			int num = atoi(is->fields[0]);
			char *ip = strdup(is->fields[1]);
			addVertex(g, num, ip);
		}
		if(part == 2){
			int v1, v2, distance;
			v1 = atoi(is->fields[0]);
			v2 = atoi(is->fields[1]);
			distance = atoi(is->fields[2]);
			addEdge(g, v1, v2, distance);
		}
	}

	int option;
	do{
		printf("1. Print my name\n");
		printf("2. Print IP list\n");
		printf("3. Distance between 2 adjacent addresses\n");
		printf("4. Shortest path between 2 addresses\n");
		printf("5. Print adjacent of 1 address\n");
		printf("6. Extract data of 2 addresses\n");
		printf("7. Exit\n");
		printf("Choose 1 option: ");
		scanf("%d", &option);

		JRB node, tree, ptr;
		int node1, node2, distance = 0, total;
		int output[30];
		switch(option){
			case 1:
				printf("Tuan Anh pro no limit!\n");
				continue;
			case 2:
				jrb_traverse(node, g.vertices){
					printf("%d %s\n", jval_i(node->key), jval_s(node->val));
				}
				continue;
			case 3:
				printf("Node1: ");
				scanf("%d", &node1);
				printf("Node2: ");
				scanf("%d", &node2);
				distance = getDistance(g, node1, node2);
				printf("%d\n", distance);
				continue;
			case 4:
				printf("Node1: ");
				scanf("%d", &node1);
				printf("Node2: ");
				scanf("%d", &node2);
				total = shortestPath(g, node1, node2, output);
				for(int i = 0; i < total - 1; i++)
					distance += getDistance(g, output[i], output[i+1]);
				printf("%d\n", distance);
				for(int i = 0; i < total; i++)
					printf("%s\n", getVertex(g, output[i]));
				continue;
			case 5:
				printf("Node: ");
				scanf("%d", &node1);
				total = getAdjacentVertices(g, node1, output);
				for(int i = 0; i < total; i++)
					printf("%s\n", getVertex(g, output[i]));
				continue;
			case 6:
				printf("Node1: ");
				scanf("%d", &node1);
				printf("Node2: ");
				scanf("%d", &node2);
				printf("2\n");
				printf("%s\n%s\n", getVertex(g, node1), getVertex(g, node2));
				printf("1\n");
				printf("%d %d %d\n", node1, node2, getDistance(g, node1, node2));
				continue;
			case 7:
				continue;
			default:
				printf("Invalid option\n");
				continue;
		}
	}while(option != 7);
	jettison_inputstruct(is);
	dropGraph(g);
}