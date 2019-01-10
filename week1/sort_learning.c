void insertion_sort(int a[], int n){
	for(int i = 0; i < n; i++){
		int j = i;
		int last = a[i]
		while(a[j - 1] > last && j > 0){
			a[j] = a[j - 1];
			j--;
		}
		a[j] = last;
	}
}

void selection_sort(int a[], int n){
	for(int i = 0; i < n; i++){
		min = i;
		for(int j = i + 1; j < n; j++){
			if(a[j] < a[min]){
				min = j;
			}
		}
		swap(&a[i], &a[min]);
	}
}

void merge(int a[], int low, int mid, int high){
	int B[high - low + 1];
	i = low;
	j = mid + 1;
	for(int k = 0; k <= high - low; k++){
		if(i > mid){
			B[k] = a[j];
			j++;
		}
		else if(j > high){
			B[k] = a[i];
			i++;
		}
		else{
			if(a[i] >= a[j]){
				B[k] = a[j];
				j++;
			}
			else{
				B[k] = a[i];
				i++;
			}
		}
	}

	for(int i = 0; i <= high - low; i++){
		a[i] = B[i];
	}

}

void merge_sort(int a[], int low, int high){
	if(low < high){
		int mid = (low + high) / 2;
		merge_sort(a, low, mid);
		merge_sort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
}

int partition_1(int a[], int left, int right){
	int key = a[right];
	int i = left;
	int j = right - 1;
	while(i < j){
		while(a[i] < key){
			i++;
		}
		while(a[j] > key){
			j--;
		}
		swap(&a[i], &a[j]);
	}
	swap(&a[i], &a[right]);
	return i;
}

int partition_2(int a[], int left, int right){
	int pivot = right;
	int i = left;
	for(int j = left; j < right; j++){
		if(a[j] < a[pivot]){
			swap(&a[i], &a[j]);
			i++;
		}
	}
	swap(&a[i], &a[pivot]);
	return i;
}

void quickSort(int a[], int left, int right){
	if(left < right){
		int pi = partition_2(a, left, right);
		quickSort(a, left, pi);
		quickSort(a, pi + 1, right);
	}
}