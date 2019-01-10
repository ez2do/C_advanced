#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"

Entry *makeVisitedNode(void *key, void *val){
	Entry *new = malloc(sizeof(Entry));
	new->key = (int*)key;
	new->value = (int*)val;
	return new;
}

int compareNode(void *key1, void *key2){
	return *(int*)key1 - *(int*)key2;
}

int main(){
	SymbolTable *table = createSymbolTable(makeVisitedNode, compareNode);
	int a = 5;
	int b = 6;
	int key2 = 8;
	int val2 = 7;
	addEntry(&a, &b, table);
	addEntry(&key2, &val2, table);
	int A[] = {5, 8};
	Entry **x = malloc(sizeof(Entry*));
	for(int i = 0; i < 2; i++){
		*x = getEntry(&A[i], table);
		printf("%p\n", *x);
		int n = *(int*)((*x)->key);
		int m = *(int*)((*x)->value);
		printf("%d - %d\n", *(int*)((*x)->key), *(int*)((*x)->value));
		printf("%d - %d\n", n, m);
	}
}
