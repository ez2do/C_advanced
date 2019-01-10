#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "libfdr/fields.h"
#include "direct_graph.h"

int readData(Graph g, char *fileName){
	int n, m, id, u, v;
	char *name;
	IS is = new_inputstruct(fileName);
	if(is == NULL){
		printf("File %s does not exist\n", fileName);
		return 0;
	}
	else{
		while(get_line(is) > 0){
			if(is->line == 1){
				n = strtol(is->fields[0], NULL, 10);
				m = strtol(is->fields[1], NULL, 10);
			}
			else if(is->line >= 2 && is->line <= n + 1){
				name = strdup(is->fields[0]);
				id = strtol(is->fields[1], NULL, 10);
				addVertex(g, id, name);
			}
			else{
				u = strtol(is->fields[0], NULL, 10);
				v = strtol(is->fields[1], NULL, 10);
				addEdge(g, u, v);
			}
		}
		return 1;
	}
}

int main(int argc, char *argv[]){
	Graph g = createGraph();
	int id, available;
	char *name;
	if(argc == 2){
		if(strcmp(argv[1], "help") == 0)
			printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
		else if(strcmp(argv[1], "about") == 0)
			printf("C advanced 20142 final exam.\n");
		else	printf("Invalid command. Print ./pr help for more support\n");
	}
	else if(argc == 4){
		if(strcmp(argv[1], "i2n") == 0){
			available = readData(g, argv[2]);
			if(available == 1){
				id = strtol(argv[3], NULL, 10);
				name = getVertex(g, id);
				if(name != NULL)
					printf("%s\n", name);
				else
					printf("Id %d does not exist\n",id);
			}
		}

		else if(strcmp(argv[1], "n2i") == 0){
			available = readData(g, argv[2]);
			if(available == 1){
				name = argv[3];
				JRB ptr;
				jrb_traverse(ptr, g.vertices){
					if(strcmp(jval_s(ptr->val), name) == 0){
						printf("%d\n", jval_i(ptr->key));
						exit(1);
					}
				}
				printf("Text %s does not exist\n", name);
			}
		}

		else
			printf("Invalid command\n");
	}

	else if(argc == 5){
		int inNode1[200];
		int inNode2[200];
		available = readData(g, argv[2]);
		if(available != 1)
			exit(1);
		if(strcmp(argv[1], "cc") == 0){
			int i = strtol(argv[3], NULL, 10);
			int j = strtol(argv[4], NULL, 10);
			int n1 = inDegree(g, i, inNode1);
			int n2 = inDegree(g, j, inNode2);
			for(int i = 0; i < n1; i++){
				for(int j = 0; j < n2; j++){
					if(inNode1[i] == inNode2[j])
						printf("%s\n", getVertex(g, inNode1[i]));
				}
			}
		}
		else
			printf("Invalid command\n");
	}
	dropGraph(g);
}