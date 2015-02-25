#include <stdio.h>
#include <string.h>

int max(int x, int y) {
	return x > y ? x : y;
}

int compare_int(const void *a, const void *b) {
	return *(int *)a < *(int *)b ? -1 : *(int *)a > *(int *)b ? 1 : 0;
}

int compare_str(const void *a, const void *b) {
	return strcmp((char *)a, (char *)b);
}

int compare_value(const void *a, const void *b, int (* compare)(const void *, const void *)) {
	return compare(a, b);
}

int main(void) {
	//p 是函数指针
	int (* p)(int, int) = &max;	//&可以省略
	int a, b, c, d, ret;
	a = 1;
	b = 3;
	c = 2;
	d = (*p)((*p)(a, b), c);	//与直接调用函数等价
	printf("max number : %d\n", d);

	//函数指针做为参数
	ret = compare_value(&a, &b, compare_int);
	printf("compare_int ret : %d\n", ret);
	
	ret = compare_value("hello", "hello", compare_str);
	printf("compare_strcmp ret : %d\n", ret);

	return 0;
}


