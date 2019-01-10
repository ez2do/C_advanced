#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int int_compare(const void *a, const void *b){
	int m = *((int*)a);
	int n = *((int*)b);
	return m - n;
}

int search(void *buf, int size, int left, int right, void *item, int(*int_compare)(const void *a, const void *b)){
	if(left > right)	return -1;
	int i = (left + right) / 2;
	int result = int_compare(item, (char*)(buf + i * size));
	if(result == 0)		return i;
	else if(result < 0)
		return search(buf, size, left, i - 1, item, int_compare);
	else
		return search(buf, size, i + 1, right, item, int_compare);
}

//size is size of an item
void exch(void *buf, int size, int i, int j){
	void tmp = malloc(size);
	tmp = *((char*)(buf + i * size));
	*((char*)(buf + i *size)) = *((char*)(buf + j * size));
	*((char*)(buf + j * size)) = tmp;
}

int main(){
	int A[100];
	int n = 100, item = 5;
	srand(time(NULL));
	for(int i = 0; i < n; i++){
		A[i] = rand() % 10;
	}
	qsort(A, n, sizeof(int), int_compare);
	int pos = search(A, sizeof(int), 0, n - 1, &item, int_compare);
	printf("Position of %d is %d\n", item, pos);
}