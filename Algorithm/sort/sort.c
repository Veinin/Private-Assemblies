#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

int
main(int argc, char *argv[]) {
	if(argc !=3) {
		fprintf(stderr, "usage : ./main [sorttype] [quantity]\n");
		printf("sort type : \n1.selection sort \n2.insertion sort \n3.bubble sort \n4.shell sort \n5.quick sort \n6.merge sort \n7.heap sort \n8.redix sort \n");
		exit(0);
	}

	int i, type = atoi(argv[1]), N = atoi(argv[2]);
	
	int *array = malloc(sizeof(int) * N);
	
	printf("array : \n");
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++) {
		int number = rand() % 1000;
		*(array + i) = number;
		printf("%d ", number);
	}

	switch(type) {
	case SELECTION_SORT:
		selection_sort(array, N);
		break;

	case INSERTION_SORT:
		insertion_sort(array, 0, N);
		break;
	
	case BUBBLE_SORT:
		bubble_sort(array, N);
		break;

	case SHELL_SORT:
		shell_sort(array, N);
		break;

	case QUICK_SORT:
		quick_sort(array, 0, N - 1);
		break;

	case MERGE_SORT:
		merge_sort(array, 0, N - 1);
		break;

	case HEAP_SORT:
		heap_sort(array, N);
		break;

	case RADIX_SORT:
		radix_sort_LSD(array, N);
		break;

	default:
		fprintf(stderr, "\nsort type not find.\n");
		free(array);
		exit(0);
	}

	printf("\nafter the sorting of the array :\n");
	for(i = 0; i < N; i++) {
		printf("%d ", *(array + i));
	}
	putchar('\n');

	free(array);

	return 0;
}
