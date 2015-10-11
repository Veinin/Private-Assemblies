/**
 * 选择排序：
 * 将资料分成已排序、未排序两部分
 * 依序由未排序中找最小值(or 最大值)，加入到已排序部份的末端
 * 
 * 时间复杂度(Time Complexity)，无论要排序数順序如何，都会执行两个回合：
 * Best Case：Ο(n2)
 * Worst Case：Ο(n2)
 * Average Case：Ο(n2)
 * 
 * 空间复杂度(Space Complexity)：O(1)
 *
 * 稳定性(Stable/Unstable)：不稳定(Unstable)
 **/
#include "sort.h"

void
selection_sort(int *arr, int sz) {
	int i, j, min, temp;
	for(i = 0; i < sz; i++) {
		min = i;
		for(j = i + 1; j < sz; j++) {
			if(arr[j] < arr[min])
				min = j;
		}

		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
