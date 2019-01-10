#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "libfdr/jval.h"
#include "graph.h"
#include "symtab.h"

Graph createGraph(){
	Graph g = make_jrb();
	return g;
}

void addEdge(Graph g, int v1, int v2){
	Graph node = jrb_find_int(g, v1);

	if(node != NULL){
		Graph tree = (JRB)jval_v(node->val);
		jrb_insert_int(tree, v2, new_jval_i(v1));
	}
	else{
		Graph tree = make_jrb();
		jrb_insert_int(g, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_i(v1));
	}
}

int adjacent(Graph g, int v1, int v2){
	Graph tree = jrb_find_int(g, v1);
	if(tree != NULL){
		if(jrb_find_int(tree, v2) != NULL)
			return 1;
	}
	return 0;
}

int getAdjacentVertices(Graph g, int v, int *output){
	Graph node = jrb_find_int(g, v);
	if(node == NULL){
		return 0;
	}
	else{
		Graph tree = (JRB)jval_v(node->val);
		int total = 0;
		Graph ptr;
		jrb_traverse(ptr, tree){
			output[total++] = jval_i(ptr->key);
		}
		return total;
	}
}

void dropGraph(Graph g){
	Graph node;
	jrb_traverse(node, g){
		jrb_free_tree((JRB)jval_v(node->val));
	}
}

Entry *makeVisitedNode(void *key, void *val){
	Entry *new = malloc(sizeof(Entry));
	new->key = malloc(sizeof(int));
	memcpy(new->key, key, sizeof(int));
	new->value = malloc(sizeof(int));
	memcpy(new->value, val, sizeof(int));
	return new;
}

int compareNode(void *key1, void *key2){
	return *(int*)key1 - *(int*)key2;
}

//(*func)(int u): do sth when traverse to node u
void BFS(Graph g, int start, int stop, void (*func)(int u)){
	int total_adjacent = 0;
	int zero = 0;
	Graph node;
	SymbolTable *visited = createSymbolTable(makeVisitedNode, compareNode);

	jrb_traverse(node, g){
		int key = jval_i(node->key);
		addEntry(&key, &zero, visited);
	}

	Dllist queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	while(!dll_empty(queue)){
		//dequeue node u
		int u = jval_i(dll_first(queue)->val);
		dll_delete_node(dll_first(queue));

		//if not visited u -> do function
		Entry *entry = getEntry(&u, visited);
		if(*(int*)(entry->value) == 0){
			func(u);	//report u
			if(u == stop)
				break;
			*(int*)(entry->value) = 1;		//set u as visited
			int adjacent[20];
			int total_adjacent = getAdjacentVertices(g, *(int*)(entry->key), adjacent);
			Entry **check = malloc(sizeof(Entry*));
			for(int i = 0; i < total_adjacent; i++){
				*check = getEntry(&adjacent[i], visited);
				int value = *(int*)((*check)->value);
				if(value == 0){
					dll_append(queue, new_jval_i(adjacent[i]));
				}
			}
		}
	}
}