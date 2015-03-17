#include <stdio.h>
#include "link_list.c"

int
main(void)
{
	LinkList L;
	InitList(L);
	
	ElemType e, next_e , e1 = 10, e2 = 20;
	ListInsert(L, 1, e1);
	ListInsert(L, 2, e2);

	GetElem(L, 1, &e);
	printf("e1 val : %d\n", e);

	NextElem(L, e, &next_e);
	printf("next e val : %d\n", e);

	return 0;	
}
