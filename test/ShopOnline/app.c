#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "libfdr/jval.h"
#include "libfdr/fields.h"
#include "graph.h"



int main(){
	int option, id, n, u, v, id1, id2, relation, start, stop, length;
	char *name;
	int path[200], tmp[200];
	JRB ptr;

	Graph g = createGraph();
	IS p = new_inputstruct("products.txt");
	IS h = new_inputstruct("orderHistory.txt");
	IS buffer = new_inputstruct("orderHistory.txt");

	//add vertices info and weight
	JRB productInfo = make_jrb();
	while(get_line(p) > 0){
		id = strtol(p->fields[0], NULL, 10);
		name = strdup(p->fields[1]);
		jrb_insert_int(productInfo, id, new_jval_s(name));
		addVertex(g, id, INFINITY);
	}

	//add relation
	while(get_line(h) > 0){
		n = h->NF;
		for(int i = 0; i < n - 1; i++){
			for(int j = i + 1; j < n; j++){
				u = strtol(h->fields[i], NULL, 10);
				v = strtol(h->fields[j], NULL, 10);
				int l = getLength(g, u, v) == INFINITY ? 0 : getLength(g, u, v);
				addEdge(g, u, v, l + 1);
			}
		}
	}

	do{
		printf("1. Products list\n");
		printf("2. Order history\n");
		printf("3. Relationship degree\n");
		printf("4. Related list\n");
		printf("5. Relation path\n");
		printf("6. Exit\n");
		printf("Choose 1 option: \n");
		scanf("%d", &option);
		switch(option){
			case 1:
				jrb_traverse(ptr, productInfo){
					printf("Product id: %d\n", jval_i(ptr->key));
					printf("Product name: %s\n\n", jval_s(ptr->val));
				}
				break;
			case 2:
				while(get_line(buffer) > 0){
					n = buffer->NF;
					for(int i = 0; i < n; i++){
						id = strtol(buffer->fields[i], NULL, 10);
						ptr = jrb_find_int(productInfo, id);
						printf("%s ", jval_s(ptr->val));
					}
					printf("\n");
				}
				break;
			case 3:
				printf("Product 1 id: ");
				scanf("%d", &id1);
				printf("Product 2 id: ");
				scanf("%d", &id2);
				relation = getLength(g, id1, id2) == INFINITY ? 0 : getLength(g, id1, id2);
				printf("Relation level: %d\n", relation);
				break;
			case 4:

				break;
			case 5:
				printf("Start: ");
				scanf("%d", &start);
				printf("Stop: ");
				scanf("%d", &stop);
				int l = shortestPath(g, start, stop, tmp);
				for(int i = 0; i < l; i++)
					printf("%d ", tmp[i]);
				printf("\n");

				shortestWeightedPath(g, start, stop, path, &length);
				for(int i = 0; i < length; i++)
					printf("%d ", path[i]);
				printf("\n");
				break;
			case 6:
				break;
			default:
				printf("Invalid option. Try again\n");
				break;
		}
		printf("\n");
	}while(option != 6);
	jettison_inputstruct(p);
	jettison_inputstruct(h);
}