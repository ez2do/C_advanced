#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "libfdr/jval.h"
#include "libfdr/fields.h"
#include "graph.h"

int main(int argc, char *argv[]){
	Graph g = createGraph();
	int n, m, e;

	//create product table
	JRB productInfo = make_jrb();
	IS products = new_inputstruct("sanpham.txt");
	while(get_line(products) > 0){
		if(products->line == 1)
			n = strtol(products->fields[0], NULL, 10);
		else{
			int id = strtol(products->fields[1], NULL, 10);
			char *name = strdup(products->fields[0]);
			jrb_insert_int(productInfo, id , new_jval_s(name));
		}
	}

	JRB storageInfo = make_jrb();
	JRB capacity = make_jrb();
	IS storage = new_inputstruct("khohang.txt");
	while(get_line(storage) > 0){
		if(storage->line == 1)
			m = strtol(storage->fields[0], NULL, 10);
		else if(storage->line == (m * n + m + 2))
			e = strtol(storage->fields[0], NULL, 10);
		else if(storage->NF == 2){
			int id;
			if(storage->line % (m + 1) == 2){
				char *storeName = strdup(storage->fields[0]);
				id = strtol(storage->fields[1], NULL, 10);
				jrb_insert_int(storageInfo, id, new_jval_s(storeName));
				addVertex(g, id, 0);
			}
			else if(storage->line % (m + 1) == 3){
				int product_id = strtol(storage->fields[0], NULL, 10);
				int quantity = strtol(storage->fields[1], NULL, 10);
				JRB tree = make_jrb();
				jrb_insert_int(capacity, id, new_jval_v(tree));
				jrb_insert_int(tree, product_id, new_jval_i(quantity));
			}
			else{
				int product_id = strtol(storage->fields[0], NULL, 10);
				int quantity = strtol(storage->fields[1], NULL, 10);
				JRB ptr = jrb_find_int(capacity, id);
				JRB tree = (JRB)jval_v(ptr->val);
				jrb_insert_int(tree, product_id, new_jval_i(quantity));
			}
		}
		else{
			int u = strtol(storage->fields[0], NULL, 10);
			int v = strtol(storage->fields[1], NULL, 10);
			int len = strtol(storage->fields[2], NULL, 10);
			addEdge(g, u, v, len);
		}
	}

	if(argc == 2){
		if(strcmp(argv[1], "-t") == 0)
			printf("C-Advanced, HK20182\n");
		else
			printf("Invalid command\n");
	}

	else if(argc == 3){
		if(strcmp(argv[1], "-s") == 0){
			JRB ptr;
			jrb_traverse(ptr, productInfo){
				printf("%s %d\n", jval_s(ptr->val), jval_i(ptr->key));
			}
		}

		else
			printf("Invalid command\n");
	}

	else if(argc == 4){
		if(strcmp(argv[1], "-w") == 0){
			int u = strtol(argv[2], NULL, 10);
			int v = strtol(argv[3], NULL, 10);
			if(getVertex(g, u) == INFINITY || getVertex(g, v) == INFINITY)
				printf("%d\n", -1);
			else
				printf("%d\n", getLength(g, u, v));
		}

		if(strcmp(argv[1], "-h") == 0){
			int product_id = strtol(argv[2], NULL, 10);
			int storage_id = strtol(argv[3], NULL, 10);
			int output[20];
			int total = getAdjacentVertices(g, storage_id, output);

			char *storeName = jval_s(jrb_find_int(storageInfo, storage_id)->val);
			char *productName = jval_s(jrb_find_int(productInfo, product_id)->val);
			JRB ptr = jrb_find_int(capacity, storage_id);
			JRB tree = (JRB)jval_v(ptr->val);
			int quantity = jval_i(jrb_find_int(tree, product_id)->val);
			printf("%s\n", storeName);
			printf("%s %d\n", productName, quantity);
			if(total != 0){
				printf("---Cac kho hang ke la:\n");
				for(int i = 0; i < total; i++){
					int storage_id = output[i];
					char *sName = jval_s(jrb_find_int(storageInfo, storage_id)->val);
					char *pName = jval_s(jrb_find_int(productInfo, product_id)->val);
					JRB ptr = jrb_find_int(capacity, storage_id);
					JRB tree = (JRB)jval_v(ptr->val);
					int quantity = jval_i(jrb_find_int(tree, product_id)->val);
					printf("%s\n", sName);
					printf("%s %d\n", pName, quantity);
				}
			}

		}
	}

}