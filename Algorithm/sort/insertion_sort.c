/**
 * 插入排序： 
 * 将资料分成已排序、未排序两部份
 * 依序由未排序中的第一笔(正处理的值)，插入到已排序中的适当位置
 * 插入时由右而左比较，直到遇到第一个比正处理的值小的值，再插入
 * 比较时，若遇到的值比正处理的值大或相等，则将值往右移

 * 时间复杂度(Time Complexity)
 * 	Best Case：Ο(1) 当资料的顺序恰好为由小到大时，每回合只需比较1次
 * 	Worst Case：Ο(n2) 当资料的顺序恰好为由大到小时，第i回合需比i次
 * 	Average Case：Ο(n2) 第n笔资料，平均比较n/2次

 * 空间复杂度(Space Complexity)：O(1)

 * 稳定性(Stable/Unstable)：稳定(Stable)
 **/
#include "sort.h"

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
