#include "sort.h"

void
bubble_sort(int *array, int n) {
	int i, j, temp;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(array[j] > array[j + 1])
				SWAP(array[j], array[j + 1]);
		}
	}
}
