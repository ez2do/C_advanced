#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/fields.h"
#include "bt_lib/inc/btree.h"
#include "libfdr/jval.h"

#define dsize 20

int main(){
	int option;
	char *name = malloc(30 * sizeof(char));
	char *number = malloc(dsize * sizeof(char));
	int size;

	int b = btinit();
	printf("%d\n", b);
	BTA *btfile = btcrt("phonebook", 0, 0);
	IS is1 = new_inputstruct("name.txt");
	IS is2 = new_inputstruct("number.txt");

	while(get_line(is1) >= 0 && get_line(is2) >= 0){
		strncpy(name, is1->text1, strlen(is1->text1) - 1);
		strcpy(number, is2->text2);
		printf("%-20s%s\n", name, number);
		btins(btfile, strdup(name), strdup(number), dsize);
		memset(name, 0, 30 * sizeof(char));
		memset(number, 0, dsize * sizeof(char));
	}

	do{
		printf("1. Add new entry to phonebook\n");
		printf("2. Search by name\n");
		printf("3. Delete an entry\n");
		printf("4. Update info\n");
		printf("5. Print the phonebook\n");
		printf("6. Exit\n");
		printf("Choose 1 option: ");
		scanf("%d", &option);

		switch(option){
			case 1:
				printf("Name: ");
				scanf(" %[^\n]s", name);
				printf("Number: ");
				scanf(" %[^\n]s", number);
				btins(btfile, strdup(name), strdup(number), dsize);
				continue;
			case 2:
				printf("Name: ");
				scanf(" %[^\n]s", name);
				btsel(btfile, name, number, dsize, &size);
				printf("%s\n", number);
				continue;
			case 3:
				printf("Name: ");
				scanf(" %[^\n]s", name);
				btdel(btfile, name);
				continue;
			case 4:
				printf("Name: ");
				scanf(" %[^\n]s", name);
				printf("New number: ");
				scanf(" %[^\n]s", number);
				btupd(btfile, name, number, dsize);
				continue;
			case 5:
			printf("%d\n", size);
				btpos(btfile, 1);
				for(int i = 1;btseln(btfile, name, number, dsize, &size) == 0; i++){
					printf("%-20s\t%10s\n", name, number);
				}
				continue;
			case 6:
				continue;
			default:
				printf("Invalid option. Try again.\n");
				continue;
		}
	}while(option != 6);
	jettison_inputstruct(is1);
	jettison_inputstruct(is2);
	btcls(btfile);
}