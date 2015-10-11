/**
 * 希尔排序
 * 希尔排序法为插入排序法的改良
 *
 * 希尔排序法的概念：
 * 将资料排列成二维阵列
 * 对二维阵列的每一行做排序
 * 利用前一次排序的结果来加快排序
 *
 * 希尔排序作法：
 * 由大到小选定数个间距(Gap)，最后一个Gap一定要是1
 * 将资料依指定的间距(Gap)分组，进行插入排序
 * Gap的选择对执行效率有很大的影响
 *
 * 时间复杂度(Time Complexity)
 * 	Best Case：Ο(n)
 * 	Worst Case：依选用的GAP而定，Ο(n2) ~ Ο(n1.5)
 * 	Average Case：Ο(n5/4)
 *
 * 空间复杂度(Space Complexity)：θ(1)
 *
 * 稳定性(Stable/Unstable)：不稳定(Unstable)
 **/
#include "sort.h"

void
shell_sort(int *array, int sz) {
	int gap, i, j, temp;
	for(gap = sz >> 1; gap > 0; gap >>= 1) {
		for(i = gap; i < sz; i ++) {
			temp = array[i];
			for(j = i - gap; j >= 0 && array[j] > temp; j -= gap) {
				array[j + gap] = array[j];
			}
			array[j + gap] = temp;
		}
	}
}
