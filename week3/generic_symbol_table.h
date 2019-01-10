#ifndef GENERIC_SYMBOL_TABLE_H_
#define GENERIC_SYMBOL_TABLE_H_

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct{
	void *key;
	void *value;
}Entry;

typedef struct{
	Entry *entries;
	int total, size;
} SymbolTable;

Entry (*makeNode)(void*, void*); //pass key and value
int (*compare)(void*, void*);

SymbolTable *createSymbolTable();

//free memory for each entry allocated when drop the table
void dropSymbolTable(SymbolTable *tab);

void addEntry(void *key, void *value, SymbolTable *book, Entry* (*makeNode)(void*, void*));

Entry *getEntry(void *key, SymbolTable *book, int (*compare)(void*, void*));

void printItems(SymbolTable *book);

Entry *makePhoneEntry(void *name, void *number);

int comparePhoneEntry(void *key1, void *key2);

#endif