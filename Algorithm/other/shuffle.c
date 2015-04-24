/**
洗牌
目的：每张牌在每个位置出现的概率相同。

方案1：
每次随机抽一张，如果抽到重复，则继续抽，知道抽到不重复的为止，时间复杂度位O(N^2)，牌的数量越大，到后面随机的时间越长，效率低，不适合

方案2：
随机交换两个位置，共交换n次

方案3（正确算法）：
第一次把第一张和随机一张牌交换，第二次把第二张和随机一张牌交换……重复做 N 次
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void
shuffle_1(int *array, int n) {
	int i, r;
	int *temp = malloc(sizeof(int) * n);

	for(i = 0; i < n; i++) {
		while(array[r = (rand() % n)] == -1);

		array[r] = -1;
		temp[i] = r;
	}

	memcpy(array, temp, sizeof(int) * n);
	free(temp);
}

void
shuffle_2(int *array, int n) {
	int i, j, k, temp;
	for(i = 0; i < n; i++) {
		j = rand() % n;
		k = rand() % n;

		temp = array[j];
		array[j] = array[k];
		array[k] = temp;
	}
}

void 
shuffle_3(int *array, int n) {
	int i, temp;

	if(n == 0)
		return;

	while(--n) {
		i = rand() % (n + 1);
		temp = array[n];
		array[n] = array[i];
		array[i] = temp;
	}
}

void
print_array_reset(int *array, int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%d ", array[i]);
		array[i] = i;
	}
	putchar('\n');
}

int
main(void) {
	int i, N = 52;

	int *array = malloc(sizeof(int) * N);
	for(i = 0; i < N; i++) {
		array[i] = i;
	}
	
	srand((unsigned) time(NULL));

	shuffle_1(array, N);
	print_array_reset(array, N);

	shuffle_2(array, N);
	print_array_reset(array, N);

	shuffle_3(array, N);
	print_array_reset(array, N);

	free(array);

	return 0;
}

