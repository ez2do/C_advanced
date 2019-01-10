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

void addVertex(Graph g, int id, double weight){
	JRB node = jrb_find_int(g.vertices, id);
	if(node != NULL)
		node->val = new_jval_d(weight);
	else
		jrb_insert_int(g.vertices, id, new_jval_d(weight));
}

double getVertex(Graph g, int id){
	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL)
		return (double)INFINITY;
	else
		return jval_d(node->val);
}

void addEdgeOneWay(Graph g, int v1, int v2, double length){
	JRB node = jrb_find_int(g.edges, v1);

	if(node != NULL){
		JRB tree = (JRB)jval_v(node->val);
		if(!jrb_find_int(tree, v2))
			jrb_insert_int(tree, v2, new_jval_d(length));
	}
	else{
		JRB tree = make_jrb();
		jrb_insert_int(g.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_d(length));
	}
}

void addEdge(Graph g, int v1, int v2, double length){
	addEdgeOneWay(g, v1, v2, length);
	addEdgeOneWay(g, v2, v1, length);
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
			func(u);
			if(u == stop)
				break;
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

double getLength(Graph g, int v1, int v2){
	int distance = 0;
	JRB node = jrb_find_int(g.edges, v1);
	if(node == NULL)
		return (double)INFINITY;
	else{
		JRB tree = jrb_find_int((JRB)jval_v(node->val), v2);
		if(tree == NULL)
			return (double)INFINITY;
		else
			return jval_d(tree->val);
	}
}

int relax(Graph g, int u, int v, JRB parentList){
	double l = getLength(g, u, v);
	JRB fromNode = jrb_find_int(g.vertices, u);
	JRB toNode = jrb_find_int(g.vertices, v);
	double d = jval_d(fromNode->val) + l;
	if(d < jval_d(toNode->val)){
		toNode->val = new_jval_d(d);
		JRB parent_v = jrb_find_int(parentList, v);
		parent_v->val = new_jval_i(u);
		return 1; //find shorter path
	}
	return 0; //can not update shorter path
}

void orderedEnqueue(Dllist queue, int u, Graph g){
	Dllist ptr;
	if(!dll_empty(queue)){
		//insert head
		int head = jval_i(dll_first(queue)->val);
		if(getVertex(g, head) > getVertex(g, u))
			dll_prepend(queue, new_jval_i(u));
		else{
			dll_traverse(ptr, queue){
				if(getVertex(g, jval_i(ptr->val)) > getVertex(g, u))
					break;		
			}
			dll_insert_b(ptr, new_jval_i(u));
		}
	}
	else
		dll_prepend(queue, new_jval_i(u));
}

Dllist dequeue(Dllist queue){
	Dllist ptr;
	Dllist item = dll_first(queue);
	dll_delete_node(dll_first(queue));
	return item;
}

JRB dijkstra(Graph g, int start, int stop){
	JRB startNode = jrb_find_int(g.vertices, start);
	if(startNode == NULL)
		return NULL;
	else{
		JRB parentList = make_jrb();
		JRB ptr;
		jrb_traverse(ptr, g.vertices){
			ptr->val = new_jval_d((double)INFINITY);
			jrb_insert_int(parentList, jval_i(ptr->key), new_jval_i(-1));
		}
		startNode->val = new_jval_d(0.0);

		Dllist queue = new_dllist();
		orderedEnqueue(queue, start, g);
		while(!dll_empty(queue)){
			Dllist node = dequeue(queue);
			int u = jval_i(node->val);
			if(u == stop)
				return parentList;
			int output[100];
			int total = getAdjacentVertices(g, u, output);
			for(int i = 0; i < total; i++){
				int updatable = relax(g, u, output[i], parentList);
				if(updatable == 1)
					orderedEnqueue(queue, output[i], g);
			}
		}
		return NULL;
	}
}

double shortestWeightedPath(Graph g, int start, int stop, int *path, int *length){
	JRB parentList = dijkstra(g, start, stop);
	if(parentList == NULL)
		return (double)INFINITY;
	else{
		int tmp[200];
		JRB stopNode = jrb_find_int(parentList, stop);
		if(stopNode == NULL)
			return (double)INFINITY;
		else{
			int n = 0;
			tmp[n++] = stop;
			double total_weight = 0.0;
			JRB currentNode = stopNode;
			do{
				tmp[n++] = jval_i(currentNode->val);
				currentNode = jrb_find_int(parentList, jval_i(currentNode->val));
			}while(jval_i(currentNode->val) != -1);
			*length = n;

			for(int i = n - 1; i >= 0; i--)
				path[n - 1 - i] = tmp[i];

			for(int i = 0; i < n - 1; i++){
				total_weight += getLength(g, path[i], path[i+1]);
			}
			return total_weight;
		}
	}
}