#include "sort.h"

void
bubble_sort(int *array, int sz) {
	int i, j, temp;
	for(i = 0; i < sz; i++) {
		for(j = 0; j < sz - i - 1; j++) {
			if(array[j] > array[j + 1])
				SWAP(array[j], array[j + 1]);
		}
	}
}
