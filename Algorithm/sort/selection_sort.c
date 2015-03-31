#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void
selection_sort(int *arr, int len) {
	int i, j, min, temp;
	for(i = 0; i < len; i++) {
		min = i;
		for(j = i + 1; j < len; j++) {
			if(arr[j] < arr[min])
				min = j;
		}

		if(i != j) {
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

int
main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("usage : ./selection_sort [array_size]\n");
		return 0;
	}

	int i, len = atoi(argv[1]);
	int *a = malloc(sizeof(int) * len);

	printf("array : \n");
	srand((unsigned)time(NULL));
	for(i = 0; i < len; i++) {
		int number = rand() % 100;
		a[i] = number;
		printf("%d ", number);
	}

	printf("\nafter selection sort:\n");

	selection_sort(a, len);
	for(i = 0; i < len; i++) {
		printf("%d ", *(a + i));
	}
	printf("\n");

	return 0;
}
