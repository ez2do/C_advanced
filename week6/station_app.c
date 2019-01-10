#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station_graph.h"
#include "libfdr/fields.h"
#include "libfdr/jrb.h"

int main(){
	int option;
	char station[3];
	char **output = malloc(10 * sizeof(char*));
	for(int i = 0; i < 10; i++)
		output[i] = malloc(3 * sizeof(char));
	Graph station_network = createGraph(0);

	IS is = new_inputstruct("state_info.txt");
	while(get_line(is) >= 0){
		for(int i = 1; i < is->NF; i++){
			addEdge(station_network, strdup(is->fields[0]), strdup(is->fields[i]) );
		}
	}
	do{
		printf("1. Find adjacent station by name\n");
		printf("2. Exit\n");
		printf("Choose 1 option: ");
		scanf("%d", &option);
		switch(option){
			case 1:
				printf("Enter station name (2 capital letter): ");
				scanf(" %s", station);
				getAdjacentVertices(station_network, station, output);
				for(int i = 0; i < 10; i++)
					printf("%s\t", output[i]);
				printf("\n");
				free(output);
				output = malloc(10 * sizeof(char*));
				for(int i = 0; i < 10; i++)
					output[i] = malloc(3 * sizeof(char));
				continue;
			case 2:
				continue;
			default:
				printf("Invalid option. Try again.\n");
				continue;
		}
	}while(option != 2);
}