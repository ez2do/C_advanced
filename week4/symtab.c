#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/*Entry *makeNode(void *name, void *number){
	Entry *new = malloc(sizeof(Entry));
	new->key = strdup((char*)name);
	new->value = malloc(sizeof(long));
	memcpy(new->value, number, sizeof(long));
	return new;
}

int compare(void *key1, void *key2){
	return strcmp((char*)key1, (char*)key2);
}*/

SymbolTable *createSymbolTable(
	Entry *(*makeNode)(void*, void*),
	int (*compare)(void*, void*)
){
	SymbolTable *tab = malloc(sizeof(SymbolTable));
	tab->entries = malloc(sizeof(Entry) * INITIAL_SIZE);
	tab->total = 0;
	tab->size = INITIAL_SIZE;
	tab->makeNode = makeNode;
	tab->compare = compare;
	return tab;
}

void dropSymbolTable(SymbolTable *tab){
	for(int i = 0; i < tab->total; i++){
		free(tab->entries);
	}
}

Entry *getEntry(void *key, SymbolTable *tab){
	for(int i = 0; i < tab->total; i++){
		if(tab->compare(key, tab->entries[i].key) == 0)
			return tab->entries + i;
	}
	return NULL;
}

void addEntry(void *key, void *value, SymbolTable *tab){
	Entry *target = getEntry(key, tab);
	if(target != NULL)
		target->value = value;
	else{
		if(tab->total >= tab->size){
			Entry *head = malloc(sizeof(Entry) * (INITIAL_SIZE + INCREMENTAL_SIZE));
			memcpy(head, tab->entries, sizeof(Entry) * tab->total);
			tab->entries = head;
		}
		Entry *new = tab->makeNode(key, value);
		tab->entries[tab->total] = *new;
		tab->total++;
	}
}

void printItems(SymbolTable *tab){
	for(int i = 0; i < tab->total; i++){
		Entry *current = tab->entries + i;
		printf("Name: %-20s, Number: %-10ld\n", (char*)current->key, *(long*)current->value);
	}
}