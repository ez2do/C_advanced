#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"
#include "jrb_graph.h"

Graph createGraph(int sizemax){
	Graph g = make_jrb();
	return g;
}

void addEdgeOneWay(Graph g, int v1, int v2){
	Graph node = jrb_find_int(g, v1);

	if(node != NULL){
		Graph tree = (JRB)jval_v(node->val);
		if(!jrb_find_int(tree, v2))
			jrb_insert_int(tree, v2, new_jval_i(v1));
	}
	else{
		Graph tree = make_jrb();
		jrb_insert_int(g, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_i(v1));
	}
}

void addEdge(Graph g, int v1, int v2){
	addEdgeOneWay(g, v1, v2);
	addEdgeOneWay(g, v2, v1);
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
	jrb_free_tree(g);
}