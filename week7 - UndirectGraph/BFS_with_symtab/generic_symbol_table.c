#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_symbol_table.h"


SymbolTable *createSymbolTable(){
	SymbolTable *new = malloc(sizeof(SymbolTable));
	new->entries = malloc(sizeof(Entry) * INITIAL_SIZE);
	new->total = 0;
	new->size = INITIAL_SIZE;
	return new;
}

Entry *getEntry(void *name, SymbolTable *book, int comparePhoneEntry(void *key1, void *key2) ){
	for(int i = 0; i < book->total; i++){
		Entry *current = book->entries + i;
		if(comparePhoneEntry(current->key, name) == 0)
			return current;
	}
	return NULL;
}

void addEntry(void *name, void *number, SymbolTable *book, Entry* (*makePhoneEntry)(void *name, void *number) ){
	Entry *target = getEntry(name, book, comparePhoneEntry);
	if(target != NULL)
		target->value = number;

	else{
		if(book->total >= book->size){
			Entry *headEntry = malloc(sizeof(Entry) * (book->size + INITIAL_SIZE));
			memcpy(headEntry, book->entries, sizeof(Entry) * book->total);
			free(book->entries);
			book->entries = headEntry;
		}

		Entry *new = makePhoneEntry(name, number);
		*(book->entries + book->total) = *new;
		book->total++;
	}
}

void printItems(SymbolTable *book){
	for(int i = 0; i < book->total; i++){
		Entry *current = book->entries + i;
		printf("Name: %20s, Number: %10d\n", current->key, *(long*)(current->value));
	}
}