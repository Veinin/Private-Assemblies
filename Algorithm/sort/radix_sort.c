#include <stdlib.h>
#include "sort.h"

void
radix_sort_LSD(int *array, int sz) {
	const int BASE = 10;
	int i, j, k, m = array[0], lsd, radix = 1;	
	int **temp = malloc(BASE * sizeof(int *));
	int bucket[BASE] = {0};

	for(i = 0; i < BASE; i++) {
		temp[i] = malloc(sz * sizeof(int));
	}

	for(i = 1; i < sz; i++) {
		if(array[i] > m)
			m = array[i];
	}

	while(m / radix > 0) {
		for(i = 0; i < sz; i++) {
			lsd = array[i] / radix % BASE;
			temp[lsd][bucket[lsd]] = array[i];
			bucket[lsd]++;
		}

		for(i = 0, k = 0; i < BASE; i++) {
			int len = bucket[i];
			if(len > 0) {
				for(j = 0; j < len; j++, k++) {
					array[k] = temp[i][j];
				}	
				bucket[i] = 0;
			}
		}

		radix *= BASE;
	}

	free(temp);
}
