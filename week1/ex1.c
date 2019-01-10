#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


void exch(int *a, int pos1, int pos2)
{
	int temp;
	temp = a[pos1];
	a[pos1] = a[pos2];
	a[pos2] = temp;
}

int *createArray(int size)
{
	int *newarr;
	newarr = (int *)malloc(sizeof(int)*size);
	int i;
	time_t t;
	srand((unsigned)time(&t));
	for (i = 0; i < size; i += 1)
	{
      //*(newarr + i) = (int*)malloc(sizeof(int));
		int num = rand() % 11;
		*(newarr + i) = num;
      // arr[i] = rand() % 11;
	}
	return newarr;
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
		exch(arr,i,j);
		if(arr[i] == arr[rin]) exch(arr, ++p,i);
		if(arr[j] == arr[rin]) exch(arr, --q,j);
	}
	exch(arr,i,rin);
	j = i - 1;
	i += 1;
	for(int k = len; k <= p; k += 1) exch(arr,k, j--);
		for(int k = rin - 1; k >= q; k -= 1) exch(arr,k, i++);
			sort2(arr,len,j);
		sort2(arr,i,rin);

	}


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

	int *dumparray(int *src, int size)
	{
		int *arr = (int*)malloc(sizeof(int) * size);
		for(int i = 0; i < size; i += 1)
			arr[i] = src[i];
		return arr;
	}

	int main()
	{

		int *arr;
		arr = createArray(10000000);
  //printf("1");
		int *arr2;
		arr2 = dumparray(arr,10000000);
		printf("Enter to continue.....\n");getchar();
  //dumparray(20);
		int i;
		for(i = 0; i < 10000000; i += 1)
		{
      //arr2[i] = arr[i];
		}


		clock_t t; 
		t = clock(); 
		sort(arr,0,9999999);
		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC;
		printf("2p Sort: ");
		printf(" %lf s\n", time_taken);

		clock_t t2; 
		t2 = clock(); 
		sort2(arr2,0,9999999);
		t2 = clock() - t2;
		time_taken = ((double)t2)/CLOCKS_PER_SEC;
		printf("3p Sort: ");
		printf(" %lf s\n", time_taken);
	}
