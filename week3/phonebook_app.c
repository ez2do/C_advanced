#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

int main(){
	PhoneBook *book = createPhoneBook();
	int option;
	char name[80];
	long number;

	do{
		printf("1. Add new entry\n");
		printf("2. Find number by name\n");
		printf("3. Print the phonebook\n");
		printf("4. Exit\n");
		scanf("%d", &option);
		switch(option){
			case 1:
				printf("Enter name: ");
				scanf(" %[^\n]s", name);
				printf("Enter number: ");
				scanf("%d", &number);
				addPhoneNumber(name, number, book);
				break;
			case 2:
				printf("Enter name: ");
				scanf(" %[^\n]s", name);
				PhoneEntry *wantedEntry = getPhoneNumber(name, book);
				if(wantedEntry != NULL)
					printf("Number of %s : %d\n", wantedEntry->name, wantedEntry->number);
				else
					printf("Not found\n");
				break;
			case 3:
				printPhoneBook(book);
				break;
			case 4:
				break;
			default:
				printf("Invalid option\n");
				break;
		}
	}
	while(option != 4);
}