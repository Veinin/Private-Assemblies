#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include <stdbool.h>

typedef int ElemType
typedef struct LNode
{
	ElemType data;
	struct LNode * next;
} LNode;

typedef LNode * LinkList;

void InitList(LinkList L);
void DestroList(LinkList *L);
void ClearList(LinkdList L);
bool ListIsEmpty(LinkList L);
int  ListLength(LinkList L);
bool GetElem(LinkList L, int i, ElemType *e);
bool NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
bool ListInsert(LinkList L, int i, ElemType e);
bool ListDelete(LinkList L, int i, ElemType *e);
void ListTraverse(LinkList L, void(* pfun)(ElemType));

#endif
