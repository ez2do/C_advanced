#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jval.h"

void exch(Jval A[], int i, int j){
	Jval tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

void sort_gen(Jval A[], int l, int r, int(compare*)(Jval*, Jval*)){
	if( l >= r) return;
	int i = l - 1;
	int j = r;
	do{
		do ++i; while(compare(A[i], A[r]) <  0);
		do --j; while(compare(A[j], A[r]) > 0);
		if(i < j){
			exch(A, i, j);
		}
	} while(i < j);
	exch(A, i, right);
	sort_gen(A, l, i - 1);
	sort_gen(A, i + 1, r);
}

int search_gen(Jval A[], int l, int r, Jval item, int(compare*)(Jval, Jval)){
	if (l > r)	return -1;
	int i = (l + r) / 2;
	int result = compare(item, A[i]);
	if(result == 0)	return i;
	else if(result < 0)
		return search_gen(A, l, i - 1, item, compare);
	else
		return search_gen(A, i + 1, r, item, compare);
}

int compare_i(Jval *a, Jval *b){
	return a.i - b.i;
}

void sort_i(Jval A[], int l, int r){
	sort_gen(A, l, r, compare_i);
}

int search_i(Jval A[], int l, int r, int x){
	search_gen(A, l, r, new_jval_i(x), compare_i);
}

Jval *create_array_i(int n){
	Jval *array = (Jval*)malloc(n * sizeof(Jval));
	srand(time(NULL));
	for(int i = 0; i < n; i++)
		array[i] = new_jval_i(rand());
	return array;
}