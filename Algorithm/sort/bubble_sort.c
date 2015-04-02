#include "sort.h"

void
bubble_sort(int *array, int n) {
	int i, j, temp;
	for(i = 0; i < n; i++) {
		for(j = 1; j < n - i; j ++) {
			if(array[j - 1] > array[j])
				SWAP(array[j - 1], array[j]);
		}
	}
}
