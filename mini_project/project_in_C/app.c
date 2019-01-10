#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libfdr/jval.h"
#include "libfdr/jrb.h"
#include "libfdr/fields.h"
#include "libfdr/dllist.h"
#include "graph.h"

#define BUS_NUMBER 877

char * trim(char * s) {
    int l = strlen(s);

    while(isspace(s[l - 1])) --l;
    while(* s && isspace(* s)) ++s, --l;

    return strndup(s, l);
}

int getCount(JRB node, JRB station_count){
	JRB tmp = jrb_find_int(station_count, jval_i(node->key));
	if(tmp == NULL)
		return 0;
	else
		return jval_i(tmp->val);
}

void priorityEnqueue(Dllist queue, JRB node, JRB station_count){
	Dllist ptr;
	if(!dll_empty(queue)){
		int head = getCount((JRB)jval_v(dll_first(queue)->val), station_count);
		if(head < getCount(node, station_count))
			dll_prepend(queue, new_jval_v(node));
		else{
			dll_traverse(ptr, queue){
				if(getCount((JRB)jval_v(ptr->val), station_count) < getCount(node, station_count))
					break;
			}
			dll_insert_b(ptr, new_jval_v(node));
		}
	}
	else
		dll_prepend(queue, new_jval_v(node));
}

void queueCheck(int station, Dllist queue){
	Dllist tmp;
	dll_traverse(tmp, queue){
		if(jval_i(tmp->val) == station){
			dll_delete_node(tmp);
			break;
		}
	}
}

void neccesaryBusTaken(int *path, int length, JRB station_route, JRB bus_line, int *num, int *busTaken){
	int j = 0;
	JRB station_count = make_jrb();
	Dllist queue = new_dllist();			//queue for path
	Dllist priorityQueue = new_dllist();
	for(int i = 0; i < length; i++){
		dll_prepend(queue, new_jval_i(path[i]));
		JRB tmp_node = jrb_find_int(station_route, path[i]);
		int *list = (int*)jval_v(tmp_node->val);
		//list[0] is the number of bus line go through that station
		for(int k = 1; k < list[0] + 1; k++){
			JRB count_node = jrb_find_int(station_count, list[k]);
			if(count_node == NULL)
				jrb_insert_int(station_count, list[k], new_jval_i(1));
			else{
				count_node->val = new_jval_i(jval_i(count_node->val) + 1);
			}
		}
	}
	JRB ptr;
	jrb_traverse(ptr, station_count){
		priorityEnqueue(priorityQueue, ptr, station_count);
	}
	while(!dll_empty(queue)){
		Dllist item = dequeue(priorityQueue);
		JRB pri_tmp = (JRB)jval_v(item->val);
		int line = jval_i(pri_tmp->key);
		JRB search_node = jrb_find_int(bus_line, line);
		int *arr = (int*)jval_v(search_node->val);
		for(int i = 1; i < arr[0] + 1; i++){
			queueCheck(arr[i], queue);
		}
		busTaken[j++] = line;
	}
	*num = j;
}


int main(){
	Graph g = createGraph();

	//create station id - name table
	JRB station_name = make_jrb();
	IS name_is = new_inputstruct("station_name.txt");
	while(get_line(name_is) >= 0){
		//insert id - name as key - value
		int id = strtol(name_is->fields[0], NULL, 10);
		char *s = strdup(name_is->text1);
		char *token = strtok(s, "/");
		token = strtok(NULL, "\n");
		jrb_insert_int(station_name, id, new_jval_s(token));
	}
	
	//create the graph edges from the bus line data(connect edges) and matrix(length info)
	//load the matrix
	double matrix[BUS_NUMBER][BUS_NUMBER];
	IS is = new_inputstruct("distance.txt");
	while(get_line(is) >= 0){
		int i = strtol(is->fields[0], NULL, 10);
		int j = strtol(is->fields[1], NULL, 10);
		double d;
		sscanf(is->fields[2], "%lf", &d);
		matrix[i - 1][j - 1] = d;
	}

	//add edges + bus line info
	JRB bus_line = make_jrb();
	IS route_is = new_inputstruct("route_data.txt");
	while(get_line(route_is) > 0){
		int n = route_is->NF;
		//add edge
		for(int i = 1; i < n - 1; i++){
			int u = strtol(route_is->fields[i], NULL, 10);
			int v = strtol(route_is->fields[i + 1], NULL, 10);
			double length = matrix[u - 1][v - 1];
			addEdge(g, u, v, length);
		}

		//add bus line info
		int *station_list = malloc(sizeof(int) * n);
		station_list[0] = n - 1;
		for(int j = 1; j < n; j++){
			station_list[j] = strtol(route_is->fields[j], NULL, 10);
		}
		jrb_insert_int(bus_line, strtol(route_is->fields[0], NULL, 10), new_jval_v(station_list));
	}

	JRB station_route = make_jrb();
	IS station_is = new_inputstruct("station_route.txt");
	while(get_line(station_is) > 0){
		int m = station_is->NF;
		int *route_list = malloc(sizeof(int) * m);
		route_list[0] = m - 1;
		for(int i = 1; i < m; i++)
			route_list[i] = strtol(station_is->fields[i], NULL, 10);
		jrb_insert_int(station_route, strtol(station_is->fields[0], NULL, 10), new_jval_v(route_list));
	}

	for(int i = 0; i < BUS_NUMBER; i++)
	addVertex(g, i + 1, (double)INFINITY);

	int s, t, length, path[1000];
	int option, id, found;
	JRB tmp, id_node;
	char name[100];
	char *token;
	JRB bus_info;
	int *arr;
	int bus_name, bus_number;
	int num;
	int busTaken[100];

	do{
		printf("\n1. Print all station\n");
		printf("2. Find station by id\n");
		printf("3. Find station by name\n");
		printf("4. Find route of bus line\n");
		printf("5. Find path\n");
		printf("6. Exit\n");
		printf("Choose 1 option: ");
		scanf("%d", &option);

		switch(option){
			case 1:
				jrb_traverse(tmp, station_name){
					printf("%d - %s\n", jval_i(tmp->key), jval_s(tmp->val));
				}
				break;
			case 2:
				printf("Enter id: ");
				scanf("%d", &id);
				id_node = jrb_find_int(station_name, id);
				if(id_node == NULL)
					printf("The station id %d is not exist\n", id);
				else
					printf("%s\n", jval_s(id_node->val));
				break;
			case 3:
				printf("Enter name: ");
				scanf(" %[^\n]s", name);
				found = 0;
				jrb_traverse(tmp, station_name){
					/*printf("%s - %s\n", name, jval_s(tmp->val));*/
					if(strcmp(name, trim(jval_s(tmp->val))) == 0){
						found = 1;
						printf("%d ", jval_i(tmp->key));
					}		
				}
				if(found == 0)
					printf("Can not find this station");
				printf("\n");
				break;
			case 4:
				printf("Enter bus number: ");
				scanf("%d", &bus_name);
				bus_info = jrb_find_int(bus_line, bus_name);
				if(!bus_info)
					printf("Can not found this bus line\n");
				else{
					arr = (int*)jval_v(bus_info->val);
					bus_number = arr[0];
					JRB begin = jrb_find_int(station_name, arr[1]);
					printf("%s(%d)", jval_s(begin->val), arr[1]);
					for(int i = 2; i < bus_number + 1; i++){
						JRB current_bus = jrb_find_int(station_name, arr[i]);
						printf("-> %s(%d) ", jval_s(current_bus->val), arr[i]);
					}
					printf("\n");
				}

				break;
			case 5:
				printf("Start: ");
				scanf("%d", &s);
				printf("Stop: ");
				scanf("%d", &t);
				double weight = shortestWeightedPath(g, s, t, path, &length);
				if (weight == (double)INFINITY)
			   		printf("No path between %d and %d\n", s, t);
				else {
				   JRB Start = jrb_find_int(station_name, path[0]);
				   JRB Stop = jrb_find_int(station_name, t);
				   printf("Path between %s(%d) and %s(%d):\n", jval_s(Start->val), s, jval_s(Stop->val), t);
				   printf("%s(%d) ", jval_s(Start->val), s);
				   for(int i = 1; i < length; i++){
				   		JRB Node = jrb_find_int(station_name, path[i]);
				   		if(Node == NULL)
				   			printf("Some error occur\n");
				   		else{
				   			printf("-> %s(%d) ", jval_s(Node->val), jval_i(Node->key));
				   		}
				   }
				   printf("\nTotal weight: %f km\n", weight);

				   neccesaryBusTaken(path, length, station_route, bus_line, &num, busTaken);
				   printf("Bus taken:");
				   for(int i = 0; i < num; i++)
				   		printf(" %d", busTaken[i]);
				   	printf("\n");
				}
				break;
			case 6:
				break;
			default:
				printf("Invalid option! Try again\n");
				break;
		}
	}while(option != 6);
	jettison_inputstruct(name_is);
	jettison_inputstruct(is);
	jettison_inputstruct(route_is);
	jettison_inputstruct(station_is);
}