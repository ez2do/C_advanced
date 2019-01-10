#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "station_graph.h"

Graph createGraph(int sizemax){
	Graph g = make_jrb();
	return g;
}

void addEdge(Graph g, char *v1, char *v2){
	Graph node = jrb_find_str(g, v1);

	if(node != NULL){
		Graph tree = (JRB)jval_v(node->val);
		jrb_insert_str(tree, v2, new_jval_s(v1));
	}
	else{
		Graph tree = make_jrb();
		jrb_insert_str(g, v1, new_jval_v(tree));
		jrb_insert_str(tree, v2, new_jval_s(v1));
	}
}

int adjacent(Graph g, char *v1, char *v2){
	Graph tree = jrb_find_str(g, v1);
	if(tree != NULL){
		if(jrb_find_str(tree, v2) != NULL)
			return 1;
	}
	return 0;
}

int getAdjacentVertices(Graph g, char *v, char *output[]){
	Graph node = jrb_find_str(g, v);
	if(node == NULL){
		return 0;
	}
	else{
		Graph tree = (JRB)jval_v(node->val);
		int total = 0;
		Graph ptr;
		jrb_traverse(ptr, tree){
			strcpy(output[total++],(char*)jval_s(ptr->key));
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
