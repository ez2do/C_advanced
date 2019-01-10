#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "phonebook.h"

int main(){
	SymbolTable *book = createPhoneBook(makePhoneNode, comparePhoneNode);
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
				addPhoneEntry(name, &number, book);
				printf("\n");
				break;
			case 2: 
				printf("Enter name: ");
				scanf(" %[^\n]s", name);
				Entry *finding_entry = getPhoneEntry(name, book);
				if(finding_entry == NULL)
					printf("Not found\n\n");
				else
					printf("Name: %20sNumber: %10d\n\n", name, *(long*)(finding_entry->value));
				break;
			case 3:
				printPhoneItems(book);
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