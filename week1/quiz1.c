#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void exch(int *a, int pos1, int pos2)
{
	int temp;
	temp = a[pos1];
	a[pos1] = a[pos2];
	a[pos2] = temp;
}

int *createArray(int p[], int base_size, int size){
	int *A = malloc(size * sizeof(int));
	time_t t;
	srand((unsigned)time(&t));
	for(int i = 0; i < size; i++){
		int j = rand() % base_size;
		*(A + i) = p[j];
	}
	return A;
}

int *dumpArray(int *source, int size){
	int *arr = malloc(size * sizeof(int));
	memcpy(arr, source, size);
	return arr;
}

//quick sort using 2-way partition
//lomuto, slower than hoare partition

/*int partition_2_way(int a[], int left, int right){
	int pivot = right;
	int i = left;
	for(int j = left; j < right; j++){
		if(a[j] < a[pivot]){
			//swap(&a[i], &a[j]);
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
		}
	}
	//swap(&a[i], &a[pivot]);
	int tmp = a[i];
	a[i] = a[pivot];
	a[pivot] = tmp;
	return i;
}

void qSort_2_way(int a[], int left, int right){
	if(left < right){
		int pi = partition_2_way(a, left, right);
		qSort_2_way(a, left, pi - 1);
		qSort_2_way(a, pi + 1, right);
	}
}*/

//hoare partition
void qSort_2_way(int a[], int left, int right){
	if( left >= right) return;
	int i = left - 1;
	int j = right;
	do{
		do ++i; while(a[i] < a[right]);
		do --j; while(a[j] > a[right]);
		if(i < j){
			exch(a, i, j);
		}
	} while(i < j);
	exch(a, i, right);
	qSort_2_way(a, left, i - 1);
	qSort_2_way(a, i + 1, right);
}

//quick sort using 3-way partition
void qSort_3_way(int a[], int left, int right){
	if(left >= right)	return;
	int i = left - 1;
	int j = right;
	int p = left - 1;
	int q = right;
	while(1){
		while(a[++i] < a[right]);
		while(a[--j] > a[right])
			if(j == left) break;
		if(i >= j)	break;
		exch(a, i, j);
		if(a[i] == a[right])	exch(a, ++p, i);
		if(a[j] == a[right])	exch(a, j, --q);
	}
	exch(a, i, right);
	j = i - 1;
	i = i + 1;
	for(int k = left; k <= p; k++)	exch(a, k, j--);
	for(int k = right - 1; k >= q; k--)	exch(a, k, i++);
	qSort_3_way(a, left, j);
	qSort_3_way(a, i, right);
}

int print_Array(int a[], int n){
	int pos = -1;
	for(int i = 0; i < n; i++){
		printf("%d ", a[i]);
		if(a[i] == 4009)
			pos = i;
	}
	printf("\n");
	return pos;
}

//Dinh's code

void sort(int arr[],int len,int rin){
	if( rin <= len) return;
	int i = len; 
	int j = rin + 1;
	int pivot = arr[len];
	do
	{
		do i += 1; while( arr[i] < pivot ) ;
		do j -= 1; while( arr[j] > pivot ) ;
		if(i < j)
		{
			int temp ;
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}while(i < j);
	int temp;
	temp = arr[len];
	arr[len] = arr[j];
	arr[j] = temp;
	sort(arr,len,j - 1);
	sort(arr,j + 1,rin); 

}

void sort2(int arr[],int len, int rin){
	if( rin <= len) return;
	int i = len - 1; 
	int j = rin;
	int p = len - 1;
	int q = rin;
	while(1)
	{
		while( arr[++i] < arr[rin] ) ;
		while( arr[--j] > arr[rin] ) 
			if(j == len) break;
		if(i >= j) break;
		//exch(arr,i,j);
		swap(&arr[i], &arr[j]);
		if(arr[i] == arr[rin]) //exch(arr, ++p,i);
		swap(&arr[i], &arr[rin]);
		if(arr[j] == arr[rin]) //exch(arr, --q,j);
		swap(&arr[j], &arr[rin]);
	}
	//exch(arr,i,rin);
	swap(&arr[i], &arr[rin]);
	j = i - 1;
	i += 1;
	for(int k = len; k <= p; k += 1) //exch(arr,k, j--);
		swap(&arr[k], &arr[j--]);
		for(int k = rin - 1; k >= q; k -= 1) //exch(arr,k, i++);
			swap(&arr[k], &arr[i++]);
		sort2(arr,len,j);
		sort2(arr,i,rin);

	}

	void sort3(int arr[],int len, int rin){
		if( rin <= len) return;
		int i = len - 1; 
		int j = rin;
		int p = len - 1;
		int q = rin;
		while(1)
		{
			while( arr[++i] < arr[rin] ) ;
			while( arr[--j] > arr[rin] ) 
				if(j == len) break;
			if(i >= j) break;
			exch(arr,i,j);
			if(arr[i] == arr[rin]) 
				exch(arr, ++p,i);
			if(arr[j] == arr[rin]) 
				exch(arr, --q,j);
		}
		exch(arr,i,rin);
		j = i - 1;
		i += 1;
		for(int k = len; k <= p; k += 1) 
			exch(arr,k, j--);
		for(int k = rin - 1; k >= q; k -= 1) 
			exch(arr,k, i++);
		sort3(arr,len,j);
		sort3(arr,i,rin);

		}

//qsort
int compare(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}


#define SMALL_NUMBER 10
#define LARGE_NUMBER 100000000

		int main(){
			int base_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			int *A1, *A2;
			A1 = createArray(base_array, 10, SMALL_NUMBER);
			A2 = createArray(base_array, 10, LARGE_NUMBER);
			int *A2_clone_1 = dumpArray(A2, LARGE_NUMBER);
			int *A2_clone_2 = dumpArray(A2, LARGE_NUMBER);
			int *A2_clone_3 = dumpArray(A2, LARGE_NUMBER);
			int *A2_clone_4 = dumpArray(A2, LARGE_NUMBER);
			int *A2_clone_5 = dumpArray(A2, LARGE_NUMBER);

	//A1 before sorting
			print_Array(A1, SMALL_NUMBER);

	//Sort A1
			qSort_3_way(A1, 0, SMALL_NUMBER - 1);
			//sort2(A1, 0, SMALL_NUMBER - 1);
			print_Array(A1, SMALL_NUMBER);
			printf("\n");

	//Sort A2
			clock_t start, end;

			start = clock();
			qSort_3_way(A2_clone_3, 0, LARGE_NUMBER - 1);
			end = clock();
			printf("Quick sort 3 way run in %f seconds.\n", ((double)(end - start))/CLOCKS_PER_SEC);

			start = clock();
			sort2(A2, 0, LARGE_NUMBER - 1);
			end = clock();
			printf("Dinh Quick sort 3 way with swap run in %f seconds.\n", ((double)(end - start))/CLOCKS_PER_SEC);

			start = clock();
			sort3(A2_clone_1, 0, LARGE_NUMBER - 1);
			end = clock();
			printf("Dinh Quick sort 3 way without swap run in %f seconds.\n", ((double)(end - start))/CLOCKS_PER_SEC);

			start = clock();
			sort(A2_clone_2, 0, LARGE_NUMBER - 1);
			end = clock();
			printf("Quick sort 2 way run in %f seconds.\n", ((double)(end - start))/CLOCKS_PER_SEC);
			
			start = clock();
			qSort_2_way(A2_clone_4, 0, LARGE_NUMBER - 1);
			end = clock();
			printf("My Quick sort 2 way run in %f seconds.\n", ((double)(end - start))/CLOCKS_PER_SEC);		
		
			start = clock();
			qsort(A2_clone_5, LARGE_NUMBER, sizeof(int), compare);
			end = clock();
			printf("Qsort of C run in %f seconds.\n", (double)(end - start)/CLOCKS_PER_SEC);
		}