/**
 给定一个存放整数的数组，重新排列数组使得数组左边为奇数，右边为偶数
 */
#include <stdio.h>

int main(void) {
	int array[] = {2, 3, 4, 10, 21, 22, 7, 23};
	int begin, end, i;
	int len = sizeof(array) / sizeof(int);

	begin = 0;
	end = len - 1;
	while(begin < end) {
		while(array[begin] % 2 == 1)
			begin++;

		while(array[end] % 2 == 0)
			end--;

		printf("swap %d and %d\n", begin, end);

		if(begin > end)
			break;

		int temp = array[begin];
		array[begin] = array[end];
		array[end] = temp;
	}

	for(i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}