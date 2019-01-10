#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_symbol_table.h"

int main(){
	SymbolTable *book = createSymbolTable();
	int option;
	char name[80];
	long number;

	do{
		printf("1. Add new address\n");
		printf("2. Find by name\n");
		printf("3. Print all items\n");
		printf("4. Exit\n");
		printf("Choose 1 option: ");
		scanf("%d", &option);

		switch(option){
			case 1:
				printf("Enter name: ");
				scanf(" %[^\n]s", name);
				printf("Enter number: ");
				scanf(" %d", &number);
				addEntry(name, &number, book, makePhoneEntry);
				printf("\n");
				break;
			case 2: 
				printf("Enter name: ");
				scanf(" %[^\n]s", name);
				Entry *finding_entry = getEntry(name, book, comparePhoneEntry);
				if(finding_entry == NULL)
					printf("Not found\n\n");
				else
					printf("Name: %20s, Number: %10d\n\n", name, *(long*)(finding_entry->value));
				break;
			case 3:
				printItems(book);
				printf("\n");
				break;
			case 4:
				break;
			default:
				printf("Invalid option\n\n");
				break;
		}
	} while(option != 4);
}