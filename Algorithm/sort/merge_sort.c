#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void
merge(int *array, int low, int mid, int high) {
	int i, k = 0;
	int len = high - low + 1;
	int *temp = malloc(sizeof(int) * len);

	int llow  = low;
	int lhigh = mid;
	int rlow  = mid + 1;
	int rhigh = high;
	
	//分别取出两个文件中较小元素
	while(llow <= lhigh && rlow <= rhigh) {
		if(array[llow] < array[rlow]) {
			temp[k++] = array[llow++];
		} else {
			temp[k++] = array[rlow++];
		}
	}

	//如左边文件还有剩余，全部加入列表
	while(llow <= lhigh) {
		temp[k++] = array[llow++];
	}

	//如右边文件还有剩余，全部加入列表
	while(rlow <= rhigh) {
		temp[k++] = array[rlow++];
	}

	for(i = 0; i < len; i++) {
		array[low + i] = temp[i];
	}

	free(temp);
}


void
merge_sort(int *array, int low, int high) {
	if(low < high) {
		int mid = (low + high) / 2;
		merge_sort(array, low, mid);
		merge_sort(array, mid + 1, high);
		merge(array, low, mid, high);
	}
}

