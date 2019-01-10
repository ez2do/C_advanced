#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "libfdr/fields.h"

Graph globalGraph;

void printVertex(int u){
	printf("%s - ", getVertex(globalGraph, u));
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

int main(){
	Graph g = createGraph();
	globalGraph = g;
	IS is = new_inputstruct("map_info.txt");
	int part = 1;
	int i = 1;
	while(get_line(is) >= 0){
		if(is->NF == 0){
			part = 2;
			continue;
		}
		
		if(part == 1){
			char *line = strdup(is->text1);
			char *token = strtok(line, "=\n");
			while(token != NULL){
				int num = atoi(strdup(token + 1));
				token = strtok(NULL, "=\n");
				addVertex(g, num, trim(token));
				token = strtok(NULL, "=\n");
			}
		}

		if(part == 2){
			int source = atoi(trim(is->fields[0] + 1));
			for(int i = 2; i < is->NF; i++){
				int adjacentNode = atoi(is->fields[i] + 1);
				addEdge(g, source, adjacentNode);
			}
		}
	}
	printf("BFS:\n");
	BFS(g, 1, -1, printVertex);
	printf("\nDFS:\n");
	DFS(g, 1, -1, printVertex);
	printf("\n");
	int shortPath[100];
	int distance = shortestPath(g, 14, 3, shortPath);
	for(int i = 0; i < distance; i++)
		printVertex(shortPath[i]);
	printf("\n");

}