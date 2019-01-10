#ifndef __SYMTAB_H_
#define __SYMTAB_H_

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct{
	void *key;
	void *value;
} Entry;

typedef struct{
	Entry *entries;
	int total, size;
	Entry *(*makeNode)(void *key, void *value);
	int (*compare)(void *key1, void *key2);
}SymbolTable;

void dropSymbolTable(SymbolTable *tab);

SymbolTable *createSymbolTable(
	Entry *(*makeNode)(void *key, void *value),
	int (*compare)(void *key1, void *key2) 
);
void addEntry(void *key, void *value, SymbolTable *tab);

Entry *getEntry(void *key, SymbolTable *tab);

void printItems(SymbolTable *book);

#endif