#include <stdlib.h>
#include "sort.h"

void
radix_sort_LSD(int *array, int sz) {
	const int BASE = 10;
	int i, j, k, m = array[0], lsd, radix = 1;	
	int **temp = malloc(BASE * sizeof(int *));	//二维数组，存储临时数据
	int bucket[BASE] = {0};				//计数桶，存放每个基数的数量

	for(i = 0; i < BASE; i++) {
		temp[i] = malloc(sz * sizeof(int));
	}

	//计算最大数
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

		//重新排列
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
