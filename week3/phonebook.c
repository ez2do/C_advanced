#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

PhoneEntry *newEntry(char *name, long number){
	PhoneEntry *new = malloc(sizeof(PhoneEntry));
	strcpy(new->name, name);
	new->number = number;
	return new;
}

PhoneBook *createPhoneBook(){
	PhoneBook *newPB = malloc(sizeof(PhoneBook));
	newPB->entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE); //have to malloc at first
	newPB->total = 0;
	newPB->size = INITIAL_SIZE;
	return newPB;
}

void dropPhoneBook(PhoneBook *book){
	free(book->entries);
	book->entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
	book->total = 0;
	book->size = INITIAL_SIZE;
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook *book){
	for(int i = 0; i < book->total; i++){
		PhoneEntry *currentTarget = (book->entries) + i;
		if(strcmp(name, currentTarget->name) == 0)
			return currentTarget;
	}
	return NULL;
}

void addPhoneNumber(char *name, long number, PhoneBook *book){
	PhoneEntry *target = getPhoneNumber(name, book);
	if(target != NULL){
		target->number = number;
	}
	else{
		if(book->total >= book->size){
			//increase size if phonebook is full
			PhoneEntry *headEntry = malloc((book->size + INCREMENTAL_SIZE) * sizeof(PhoneEntry));
			memcpy(headEntry, book->entries, book->total * sizeof(PhoneEntry));
			free(book->entries);
			book->entries = headEntry;
		}

		PhoneEntry *new = newEntry(name, number);
		PhoneEntry *index = book->entries + book->total; //shift to the end of phonebook
		*index = *new; //use * to deference of pointer, new change by time so use pointer will be bug
		book->total++;
	}
}

void printPhoneBook(PhoneBook *book){
	for(int i = 0; i < book->total; i++){
		PhoneEntry *current = book->entries + i;
		printf("%d. Name: %-20s Number: %-10d\n", i + 1, current->name, current->number);
	}
}