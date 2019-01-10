#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "direct_graph.h"
#include "libfdr/fields.h"
#include "libfdr/jrb.h"
#include "libfdr/jval.h"

int main(int argc, char **argv){
	Graph g;
	int n, m;
	IS is = new_inputstruct("book_reference.txt");
	while(get_line(is) >= 0){
		printf("%d\n", is->line);
		if(is->line == 1){
			n = strtol(is->fields[0], NULL, 10);
			m = strtol(is->fields[1], NULL, 10);
			continue;
		}
		if(is->line >= 2 && is->line < n + 2){
			char *name = strdup(is->fields[0]);
			int id = strtol(is->fields[1], NULL, 10);
			printf("%d - %s\n", id, name);
			addVertex(g, id, name);
			addRVertex(g, name, id);
		}
		else{
			int v1 = atoi(is->fields[0]);
			int v2 = atoi(is->fields[1]);
			printf("%d %d\n", v1, v2);
			addEdge(g, v1, v2);
		}
	}
	//Part 1
	if(argc == 2){
		//help
		if(strcmp(argv[1], "help") == 0)
			printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
		if(strcmp(argv[1], "about") == 0)
			printf("C advanced 20142 final exam.\n");
	}
	//Part 2
}