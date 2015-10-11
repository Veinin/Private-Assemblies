/**
 * 冒泡排序作法：
 * 由未排序中的第一笔开始，与第二笔资料比对
 * 若第一笔 > 第二笔 ⇒ 交换位置(Swap)
 * 若还有未排序的资料，则用第二笔和第三笔资料比对
 * 依此类推
 * 若未排序的资料中，比对时都没有进行交换位置 ⇒ flag = false
 * 代表资料已排序好 ⇒ 提早结束排序
 * 执行时，未排序资料中的最大值会如同气泡般往右跑
 *
 * 时间複杂度(Time Complexity)
 * 	Best Case：Ο(n) 当资料的顺序恰好为由小到大时，第一次执行后，未进行任何swap ⇒ 提前结束
 * 	Worst Case：Ο(n^2) 当资料的顺序恰好为由大到小时，每回合分别执行：n-1、n-2、...、1次，(n-1) + (n-2) + ... + 1 = n(n-1)/2 ⇒ Ο(n2)
 * 	Average Case：Ο(n^2) 第n笔资料，平均比较(n-1)/2次
 *
 * 空间複杂度(Space Complexity)：θ(1)
 * 稳定性(Stable/Unstable)：稳定(Stable)
 **/
#include "sort.h"

void
bubble_sort(int *array, int sz) {
	int i, j, temp;
	for(i = 0; i < sz; i++) {
		for(j = 0; j < sz - i - 1; j++) {
			if(array[j] > array[j + 1])
				SWAP(array[j], array[j + 1]);
		}
	}
}
