#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "phonebook.h"

Entry *makePhoneNode(void *name, void *number){
	Entry *new = malloc(sizeof(Entry));
	new->key = strdup((char*)name);
	new->value = malloc(sizeof(long));
	memcpy(new->value, number, sizeof(long));
	return new;
}

int comparePhoneNode(void *key1, void *key2){
	return strcmp((char*)key1, (char*)key2);
}

PhoneBook *createPhoneBook(){
	PhoneBook *new = createSymbolTable(makePhoneNode, comparePhoneNode);
	return new;
}

void dropPhoneBook(PhoneBook *book){
	dropSymbolTable(book);
}

Entry *getPhoneEntry(void *key, PhoneBook *book){
	Entry *target = getEntry(key, book);
	return target;
}

void addPhoneEntry(void *key, void *value, PhoneBook *book){
	addEntry(key, value, book);
}

void printPhoneItems(PhoneBook *book){
	printItems(book);
}