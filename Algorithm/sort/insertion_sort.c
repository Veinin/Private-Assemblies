#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int
main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "usage : ./insertion_sort [array_size]\n");	
		exit(0);
	}
	
	int i, N = atoi(argv[1]);
	int *array = malloc(sizeof(int) * N);

	printf("array :\n");
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++) {
		int number = rand() % 100;
		*(array + i) = number;
		printf("%d ", number);
	}

	printf("\nafter insertion sort : \n");
	insertion_sort(array, 0, N);
	for(i = 0; i < N; i++) {
		printf("%d ", *(array + i));
	}
	printf("\n");

	return 0;
}
