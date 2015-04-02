#include "sort.h"

void
selection_sort(int *arr, int len) {
	int i, j, min, temp;
	for(i = 0; i < len; i++) {
		min = i;
		for(j = i + 1; j < len; j++) {
			if(arr[j] < arr[min])
				min = j;
		}

		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
