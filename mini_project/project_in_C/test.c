#include <stdio.h>
#include <stdlib.h>
#include "libfdr/fields.h"
#include "libfdr/jval.h"
#include "libfdr/jrb.h"

int main(){
	JRB bus_line = make_jrb();
	IS route_is = new_inputstruct("route_data.txt");
	while(get_line(route_is) > 0){
		int n = route_is->NF;
/*		//add edge
		for(int i = 1; i < n - 1; i++){
			int u = strtol(route_is->fields[i], NULL, 10);
			int v = strtol(route_is->fields[i + 1], NULL, 10);
			double length = matrix[u - 1][v - 1];
			addEdge(g, u, v, length);
		}*/

		//add bus line info
		int *station_list = malloc(sizeof(int) * n);
		station_list[0] = n - 1;
		for(int j = 1; j < n; j++){
			station_list[j] = strtol(route_is->fields[j], NULL, 10);
		}
		printf("Number of bus: %d, Name of bus: %ld\n", n - 1, strtol(route_is->fields[0], NULL, 10));
		jrb_insert_int(bus_line, strtol(route_is->fields[0], NULL, 10), new_jval_v(station_list));
	}

	JRB tmp;
	jrb_traverse(tmp, bus_line){
		int *arr = (int*)jval_v(tmp->val);
		int n = arr[0];
		printf("%d -",  jval_i(tmp->key));
		for(int i = 1; i < n + 1; i++)
			printf(" %d", arr[i]);
		printf("\n");
		}
}