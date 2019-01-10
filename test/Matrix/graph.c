#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "libfdr/jval.h"
#include "graph.h"

Graph createGraph(){
	Graph g;
	g.vertices = make_jrb();
	g.edges = make_jrb();
	return g;
}

void addVertex(Graph g, int id, char* name){
	JRB node = jrb_find_int(g.vertices, id);
	if(node != NULL)
		node->val = new_jval_s(name);
	else
		jrb_insert_int(g.vertices, id, new_jval_s(name));
}

char* getVertex(Graph g, int id){
	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL)
		return NULL;
	else
		return jval_s(node->val);
}

void addEdgeOneWay(Graph g, int v1, int v2){
	JRB node = jrb_find_int(g.edges, v1);

	if(node != NULL){
		JRB tree = (JRB)jval_v(node->val);
		if(!jrb_find_int(tree, v2))
			jrb_insert_int(tree, v2, new_jval_i(v1));
	}
	else{
		JRB tree = make_jrb();
		jrb_insert_int(g.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_i(v1));
	}
}

void addEdge(Graph g, int v1, int v2){
	addEdgeOneWay(g, v1, v2);
	addEdgeOneWay(g, v2, v1);
}

int adjacent(Graph g, int v1, int v2){
	JRB node = jrb_find_int(g.edges, v1);
	if(node != NULL){
		JRB tree = (JRB)jval_v(node->val);
		if(jrb_find_int(tree, v2) != NULL)
			return 1;
	}
	return 0;
}

int getAdjacentVertices(Graph g, int v, int *output){
	JRB node = jrb_find_int(g.edges, v);
	int total = 0;
	if(node != NULL){
		JRB tree = (JRB)jval_v(node->val);
		JRB ptr;
		jrb_traverse(ptr, tree){
			output[total++] = jval_i(ptr->key);
		}
	}
	return total;
}

void dropGraph(Graph g){
	jrb_free_tree(g.vertices);
	JRB node;
	jrb_traverse(node, g.edges){
		jrb_free_tree((JRB)jval_v(node->val));
	}
	jrb_free_tree(g.edges);
}

//(*func)(int u): do sth when traverse to node u
JRB BFS(Graph g, int start, int stop, void (*func)(int u)){
	//make visited jrb, set all node unvisited
	JRB visited = make_jrb();
	JRB node;
	jrb_traverse(node, g.edges){
		jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
	}

	//create the queue
	Dllist queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	//create previous node table
	JRB preNodeTab = make_jrb();

	while(!dll_empty(queue)){
		//dequeue the node
		int u = jval_i(dll_first(queue)->val);
		dll_delete_node(dll_first(queue));

		JRB visitStatus = jrb_find_int(visited, u);
		if(jval_i(visitStatus->val) == 0){
			func(u);
			if(u == stop)
				break;
			visitStatus->val = new_jval_i(1);
			int adjacent[20];
			int total = getAdjacentVertices(g, u, adjacent);
			for(int i = 0; i < total; i++){
				//if not visit node, enqueue node, set previous node to u
				visitStatus = jrb_find_int(visited, adjacent[i]);
				if(jval_i(visitStatus->val) == 0){
					dll_append(queue, new_jval_i(adjacent[i]));
					if(!jrb_find_int(preNodeTab, adjacent[i]))
						jrb_insert_int(preNodeTab, adjacent[i], new_jval_i(u));
				}
			}

		}
	}
	return preNodeTab;

}

void doNothing(int u){}

int shortestPath(Graph g, int start, int stop, int *output){
	int total = 0;
	JRB prevNodeTab = BFS(g, start, stop, doNothing);
	JRB stopNode = jrb_find_int(prevNodeTab, stop);
	if(stopNode == NULL){
		printf("No path!\n");
	}
	else{
		Dllist stack = new_dllist();
		dll_prepend(stack, new_jval_i(stop));
		int current = stop;
		JRB node;
		while(current != start){
			node = jrb_find_int(prevNodeTab, current);
			current = jval_i(node->val);
			dll_prepend(stack, new_jval_i(current));
		}

		Dllist ptr;
		dll_traverse(ptr, stack){
			output[total++] = jval_i(ptr->val);
		}
	}
	return total;
}

void printShortestPath(Graph g, int start, int stop){
	int path[200];
	int total = shortestPath(g, start, stop, path);
	for(int i = 0; i < total; i++)
		printf("%-5d", path[i]);
}

void DFS(Graph g, int start, int stop, void (*func)(int u)){
	//make visited JRB, set all node unvisited
	JRB visited = make_jrb();
	JRB node;
	jrb_traverse(node, g.edges){
		jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
	}

	//create stack
	Dllist stack = new_dllist();
	dll_prepend(stack, new_jval_i(start));

	while(!dll_empty(stack)){
		int u = jval_i(dll_first(stack)->val);
		dll_delete_node(dll_first(stack));

		//if not visit u, do function
		JRB visitStatus = jrb_find_int(visited, u);
		if(jval_i(visitStatus->val) == 0){
			if(u == stop)
				func(u);
			visitStatus->val = new_jval_i(1);
			int adjacent[20];
			int total = getAdjacentVertices(g, u, adjacent);
			for(int i = 0; i < total; i++){
				JRB adjacentVisit = jrb_find_int(visited, adjacent[i]);
				if(jval_i(adjacentVisit->val) == 0)
					dll_prepend(stack, new_jval_i(adjacent[i]));
			}
		}
	}

}