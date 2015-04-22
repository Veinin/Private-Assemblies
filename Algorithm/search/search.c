#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "search.h"

int
main(int argc, char *argv[]) {
	if(argc !=3) {
		fprintf(stderr, "usage : ./search [searchtype] [quantity]\n");
		printf("search type : \n1.binary search \n");
		exit(0);
	}

	int i, searchVal, searchIndex, type = atoi(argv[1]),  N = atoi(argv[2]);

	int *array = malloc(sizeof(int) * N);
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++) {
		int number = rand() % 1000;
		*(array + i) = number;
		printf("%d ", number);
	}
	putchar('\n');

	printf("Please enter a search value : \n");
	scanf("%d", &searchVal);

	switch(type) {
	case 1:
		searchIndex = binary_search(array, 0, N - 1, searchVal);
		break;

	default:
		printf("search type error!\n");
	}

	if(searchIndex >= 0) {
		printf("Find the value of index in the : %d\n", searchIndex);
	} else {
		printf("Didn't find it\n");
	}
	

	free(array);

	return 0;
}