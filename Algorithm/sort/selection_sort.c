#include "sort.h"

void
selection_sort(int *arr, int sz) {
	int i, j, min, temp;
	for(i = 0; i < sz; i++) {
		min = i;
		for(j = i + 1; j < sz; j++) {
			if(arr[j] < arr[min])
				min = j;
		}

		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
