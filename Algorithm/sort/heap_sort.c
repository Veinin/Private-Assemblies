#include <stdio.h>
#include "sort.h"

static void
printf(int array, int hsz) {
	int depth = hsz / 2;
}

void
max_heapify(int *array, int root, int hsz) {
	int l = 2 * root + 1;
	int r = 2 * root + 2;
	int largest = root;

	if(l < hsz && array[l] > array[root]) 
		largest = l;

	if(r < hsz && array[r] > array[root])
		largest = r;
	
	if(largest != root) {
		SWAP(array[root], array[largest]);
		max_heapify(array, largest, hsz);
	}
}

void
heap_sort(int *array, int hsz) {
	int i;
	for(i = (hsz - 1) / 2; i >= 0; i--) {
		max_heapify(array, i, hsz);	
	}

	for(i = hsz - 1; i >= 0; i--) {
		SWAP(array[0], array[i]);
		max_heapify(array, 0, i);
	}
}
