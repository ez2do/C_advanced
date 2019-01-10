#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_memcpy(void *des, void *src, size_t n){
	const char* first = (char*)src;
	const char* last = (char*)src + n;
	const char* last_two = (char*)(src + n);
	printf("%p %p\n", last, last_two);
	char *result = (char*) des;
	while( first != last){
		*result++ = *first++;
	}
}

int main(){
	int A[] = {1,2,5,6,7,9,3,8,7};
	for(int i = 0; i < 9; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	int *arr_pointer = malloc(9 * sizeof(int));
	my_memcpy(arr_pointer, A, 9 * sizeof(int));
	//memcpy(arr_pointer, A, 9 * sizeof(int));
	for(int i = 0; i < 9; i++){
		printf("%d ", *(arr_pointer + i));
	}
	printf("\n");
}
