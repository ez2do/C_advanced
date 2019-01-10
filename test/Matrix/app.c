#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "libfdr/jval.h"
#include "libfdr/fields.h"
#include "graph.h"

int countWay = 0;

void OneMoreWay(int u){
	countWay++;
}

int main(){
	int n, l, option, countNodes, countEdges, int_node, tmp;
	char string[5], node[10];
	int adjacent[20];
	int matrix1[100][100];
	int matrix2[100][100];
	Graph g = createGraph();
	IS is = new_inputstruct("data.txt");
	while(get_line(is) > 0){
		n = is->NF;
		l = is->line;
		for(int i = 0; i < n; i++){
			int num = strtol(is->fields[i], NULL, 10);
			matrix1[l - 1][i] = num;
			if(num == 0){
				char *str1 = strdup(string);
				char *str2 = strdup(string);
				sprintf(str1, "%d", l - 1);
				sprintf(str2, "%d", i);
				addVertex(g, 10 * (l - 1) + i, strcat(str1, str2));
			}
		}
	}

	for(int i = 0; i < n + 2; i++){
		matrix2[0][i] = 1;
		matrix2[i][0] = 1;
		matrix2[n + 1][i] = 1;
		matrix2[i][n + 1] = 1;
	}

	for(int i = 1; i < n + 1; i++){
		for(int j = 1; j < n + 1; j++){
			matrix2[i][j] = matrix1[i - 1][j - 1];
		}
	}

	for(int i = 1; i < n + 1; i++){
		for(int j = 1; j < n + 1; j++){
			if(matrix2[i][j] == 0){
				countNodes++;
				if(matrix2[i - 1][j] == 0){
					addEdge(g, 10 * (i - 1) + (j - 1), 10 * (i - 2) + (j - 1));
					countEdges++;
				}
				if(matrix2[i + 1][j] == 0){
					addEdge(g, 10 * (i - 1) + (j - 1), 10 * i + j - 1);
					countEdges++;
				}
				if(matrix2[i][j - 1] == 0){
					addEdge(g, 10 * (i - 1) + j - 1, 10 * (i - 1) + j - 2);
					countEdges++;
				}
				if(matrix2[i][j + 1] == 0){
					countEdges++;
					addEdge(g, 10 * (i - 1) + (j - 1), 10 * (i - 1) + j);
				}
			}
		}
	}

	do{
		printf("1. Print the matrix\n");
		printf("2. Number of Vertices and Edges\n");
		printf("3. Find adjacent list of a node\n");
		printf("4. Nodes with greatest number of adjacent\n");
		printf("5. Isolated nodes\n");
		printf("6. Shortest path between 2 nodes\n");
		printf("7. All paths between 2 nodes\n");
		printf("8. Exit\n");
		printf("Choose 1 option: ");
		scanf("%d", &option);

		switch(option){
			case 1:
				for(int i = 0; i < n; i++){
					for(int j = 0; j < n; j++){
						printf("%d ", matrix1[i][j]);
					}
					printf("\n");
				}
				break;

			case 2:
				countEdges = countEdges / 2;
				printf("Number of nodes: %d\n", countNodes);
				printf("Number of edges: %d\n", countEdges);
				break;

			case 3:
				printf("Node: ");
				getchar();
				fgets(node, 10, stdin);
				int_node = strtol(node, NULL, 10);
				int len = getAdjacentVertices(g, int_node, adjacent);
				if(len == 0)
					printf("There are 0 adjacent node\n");
				for(int i = 0; i < len; i++)
					printf("%s ", getVertex(g, adjacent[i]));
				printf("\n");
				break;

			case 4:
			{
				int max = 0;
				int total = 0;
				int output[20];
				int adj[20];
				JRB ptr;
				jrb_traverse(ptr, g.vertices){
					tmp = getAdjacentVertices(g, jval_i(ptr->key), adj);
					if(tmp == max)
						output[total++] = jval_i(ptr->key);
					else if(tmp > max){
						total = 0;
						max = tmp;
						output[total++] = jval_i(ptr->key);
					}
				}
				printf("Nodes with maximum degree of %d:\n", max);
				for(int i = 0; i < total; i++){
					printf("%s ", getVertex(g, output[i]));
				}
				printf("\n");
				break;
			}
			case 5:
			{
				int isolate[20];
				int tmp[20];
				int total = 0;
				JRB ptr;
				jrb_traverse(ptr, g.vertices){
					if(getAdjacentVertices(g, jval_i(ptr->key), tmp) == 0)
						isolate[total++] = jval_i(ptr->key);
				}
				printf("There are %d isolated nodes\n", total);
				for(int i = 0; i < total; i++)
					printf("%s ", getVertex(g, isolate[i]));
				printf("\n");
				break;
			}
			case 6:{
				char node1[10], node2[10];
				int i_node1, i_node2;
				int total = 0;
				int path[20];
				printf("Node 1: ");
				scanf("%s", node1);
				printf("Node 2: ");
				scanf("%s", node2);
				i_node1 = strtol(node1, NULL, 10);
				i_node2 = strtol(node2, NULL, 10);
				total = shortestPath(g, i_node1, i_node2, path);
				for(int i = 0; i < total; i++)
					printf("%s ", getVertex(g, path[i]));
				printf("\n");
				break;
			}
			case 7:{
				countWay = 0;
				char node1[10], node2[10];
				int i_node1, i_node2;
				printf("Node 1: ");
				scanf("%s", node1);
				printf("Node 2: ");
				scanf("%s", node2);
				i_node1 = strtol(node1, NULL, 10);
				i_node2 = strtol(node2, NULL, 10);
				DFS(g, i_node1, i_node2, OneMoreWay);
				printf("Number of way: %d\n", countWay);
				break;
			}
			case 8:
				break;
			default:
				printf("Invalid option. Try again\n");
				break;
		}
	}while(option != 8);
}