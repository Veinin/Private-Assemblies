#include "search.h"

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