/**
 * 全排列
 * 不断将每个元素放作第一个元素，然后将这个元素作为前缀，并将其余元素继续全排列，等到出口，出口出去后还需要还原数组
 */
#include <stdio.h>
#include <string.h>

void
swap(char *a, char *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void
AllRange(char *str, int begin, int end)
{
	int i;
	if (begin == end)
	{
		static int count = 1;
		printf("%d : %s\n", count++, str);
		return;
	}
	else
	{
		for(i = begin; i <= end; i++)
		{
			swap(str + begin, str + i);	//将begin~end中每个元素放到begin位置
			AllRange(str, begin + 1, end);	//begin位置确定，将余下begin + 1~end继续全排列
			swap(str + begin, str + i);	//还原数组
		}
	}
}

void 
Permutation(char *str)
{
	AllRange(str, 0, strlen(str) - 1);
}

int 
main(void)
{
	char str[] = "abc";
	Permutation(str);

	return 0;
}
