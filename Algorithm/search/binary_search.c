#include <stdio.h>

int
binary_search(int array[], int low, int high, int key) {
	if(low > high)
		return -1;

	int mid = low + ((high - low) >> 1);
	if(array[mid] == key)
		return mid;

	if(array[mid] > key) {
		return binary_search(array, low, mid - 1, key);
	} else {
		return binary_search(array, mid + 1, high, key);
	}
}

int
main(void) {
	int idx, array[] = {1, 2, 3, 4, 6, 10};
	
	idx = binary_search(array, 0, 5, 4);
	printf("search index : %d\n", idx);

	idx = binary_search(array, 0, 5, 20);
	printf("search index : %d\n", idx);

	return 0;
}