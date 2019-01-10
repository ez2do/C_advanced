#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *make_phone_num(int base[], int size){
	char *A = malloc(size * sizeof(int));
	srand(time(NULL));
	for(int i = 0; i < size; i++){
		int j = rand() % 10;
		*(A + i) = base[j];
	}
	return A;
}

void printToFile(char *a, int size, FILE *fout){
	for(int i = 0; i < size; i++){
		fputc(*(a + i), fout);
	}
	fputs("\n", fout);
}

#define SIZE 100
int main(){
	FILE *fout = fopen("number.txt", "w");
	int base[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for(int i = 0; i < SIZE; i++){
		char *A = make_phone_num(base, 10);
		printToFile(A, 10, fout);
	}
	fclose(fout);
}