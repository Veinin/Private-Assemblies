#include <stdbool.h>
#include <stdio.h>
#include "sort.h"

int
partition(int *array, int l, int r) {
	int i = l - 1, j = r, k = array[r];
	for( ; ; ) {
		while(array[++i] < k)

		while(array[--j] > k) if(j == l) break;

		if(i >= j)
			break;

		SWAP(array[i], array[j]);
	}
	SWAP(array[i], array[r]);

	return i;
}

void
quick_sort(int *array, int l, int r) {
	int i;
	if(r <= l) return;
	i = partition(array, l, r);
	quick_sort(array, l, i - 1);
	quick_sort(array, i + 1, r);
}
