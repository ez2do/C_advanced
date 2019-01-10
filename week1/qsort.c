#include <stdio.h>
#include <stdlib.h>

int descendent(const void* a, const void* b){
	return -(*(int*)a - *(int*)b);
}

int ascendent(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

void printArray(int a[], int size){
	for(int i = 0; i < size; i++){
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

int main(){
	int A[] = {3,4,56,3,4,3,32,8,3,24,2,1,97,33,75,524};
	int n = sizeof(A)/sizeof(int);
	printArray(A, n);
	printf("Descendent order: ");
	qsort(A, n, sizeof(int), descendent);
	printArray(A, n);
	printf("Ascendent order: ");
	qsort(A, n, sizeof(int), ascendent);
	printArray(A, n);
}