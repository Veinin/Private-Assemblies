#include "sort.h"

void
insertion_sort(int *array, int first, int last) {
	int i, j, temp;
	for(i = first + 1; i < last; i++) {
		temp = array[i];
		for(j = i - 1; j >= 0 && array[j] > temp; j--) {
			array[j + 1] = array[j];
		}
		array[j + 1] = temp;
	}
}
