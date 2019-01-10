#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "direct_graph.h"

Graph createGraph(){
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
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
	if(node != NULL)
		return jval_s(node->val);
	else
		return NULL;
}

void addEdge(Graph g, int v1, int v2){
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

int hasEdge(Graph g, int v1, int v2){
	JRB node = jrb_find_int(g.edges, v1);
	if(node != NULL){
		if(jrb_find_int((JRB)jval_v(node->val), v2) != NULL)
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

int inDegree(Graph g, int id, int *output){
	int total = 0;
	JRB ptr;
	jrb_traverse(ptr, g.edges){
		if(jrb_find_int((JRB)jval_v(ptr->val), id) != NULL){
			output[total++] = jval_i(ptr->key);
		}
	}
	return total;
}

int outDegree(Graph g, int id, int *output){
	int total = 0;
	JRB node = jrb_find_int(g.edges, id);

	if(node != NULL){
		JRB tree = (JRB)jval_v(node->val);
		JRB ptr;
		jrb_traverse(ptr, tree){
			output[total++] = jval_i(ptr->key);
		}
	}
	return total;
}

JRB BFS(Graph g, int start, int stop, void (*func)(int u)){
	//make visited jrb, set all node unvisited
	JRB visited = make_jrb();
	JRB node;
	jrb_traverse(node, g.edges){
		jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
		JRB tree = (JRB)jval_v(node->val);
		JRB ptr;
		jrb_traverse(ptr, tree){
			if(!jrb_find_int(visited, jval_i(ptr->key))){
				jrb_insert_int(visited, jval_i(ptr->key), new_jval_i(0));
			}
		}
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
		JRB tree = (JRB)jval_v(node->val);
		JRB ptr;
		jrb_traverse(ptr, tree){
			if(!jrb_find_int(visited, jval_i(ptr->key))){
				jrb_insert_int(visited, jval_i(ptr->key), new_jval_i(0));
			}
		}
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

Graph dag_graph;
int dag_start, dag_check;

void dag_visit(int v){
	//if detect a node direct to the root node, it's mean the graph has a cycle
	if(hasEdge(dag_graph, v, dag_start))
		dag_check = 1;
}

int DAG(Graph g){
	dag_graph = g;
	JRB node;
	dag_check = 0;
	jrb_traverse(node, g.edges){
		dag_start = jval_i(node->key);
		DFS(g, dag_start, -1, dag_visit);
		if(dag_check == 1)
			return 0;
	}
	return 1;
}

int topoSort(Graph g, int* output){
	int total = 0;
	Dllist queue = new_dllist();

	int inNodes[20];
	int outNodes[20];

	//make inDegree Table
	JRB inDegreeTable = make_jrb();
	JRB node;
	jrb_traverse(node, g.edges){
		int n = inDegree(g, jval_i(node->key), inNodes);
		jrb_insert_int(inDegreeTable, jval_i(node->key), new_jval_i(n));
		if(n == 0)
			dll_append(queue, node->key);

		JRB tree = (JRB)jval_v(node->val);
		JRB ptr;
		jrb_traverse(ptr, tree){
			if(!jrb_find_int(inDegreeTable, jval_i(ptr->key))){
				n = inDegree(g, jval_i(ptr->key), inNodes);
				jrb_insert_int(inDegreeTable, jval_i(ptr->key), new_jval_i(n));
				if(n == 0)
					dll_append(queue, ptr->key);
			}
		}
	}

	while(!dll_empty(queue)){
		int u = jval_i(dll_first(queue)->val);
		dll_delete_node(dll_first(queue));
		output[total++] = u;

		int outNodeNumber = outDegree(g, u, outNodes);
		for(int i = 0; i < outNodeNumber; i++){
			JRB out = jrb_find_int(inDegreeTable, outNodes[i]);
			out->val = new_jval_i(jval_i(out->val) - 1);
			if(jval_i(out->val) == 0)
				dll_append(queue, out->key);
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