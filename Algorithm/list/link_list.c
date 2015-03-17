#include <stdio.h>
#include <stdlib.h>
#include "link_list.h"

void
InitList(LinkList L) {
	L = (LinkList) malloc(sizeof(struct LNode));
	if(!L)
		exit(-1);
	L-> next = NULL;
}

void
DestroList(LinkList *L) {
	LinkList q;
	while(*L) {
		q = (*L)->next;
		free(*L);
		*L = q;
	}
}

void
ClearList(LinkList L) {
	LinkList p,q;
	p = L->next;
	while(p) {
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

bool
ListIsEmpty(LinkList L) {
	return L->next == NULL;
}

int
ListLength(LinkList L) {
	int i = 0;
	LinkList p = L->next;
	while(p) {
		i++;
		p = p->next;
	}
	return i;
}

bool
GetElem(LinkList L, int i, ElemType *e) {
	int j = 1;
	LinkList p = L->next;
	while(p && j < i) {
		p = p->next;
		j++;
	}

	if(!p || j > i)
		return false;
	
	*e = p->data;
	return true;

}

bool
NextElem(LinkList L, ElemType cur_e, ElemType *next_e) {
	LinkList p = L->next;
	while(p->next) {
		if(p->data == cur_e) {
			*next_e = p->next->data;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool
ListInsert(LinkList L, int i, ElemType e) {
	int j = 0;
	LinkList p = L, s;
	while(p && j < i - 1) {
		p = p->next;
		j++;
	}

	if(!p || j > i)
		return false;

	s = (LinkList)malloc(sizeof(struct LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return true;
}

bool
ListDelete(LinkList L, int i, ElemType *e) {
	int j = 0;
	LinkList p = L->next, q;
	while(p->next && j < i-1) {
		p = p->next;
		j++;
	}

	if(!p || j > i-1)
		return false;

	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);

	return true;
}

void
ListTraverse(LinkList L, void(* pfun)(ElemType)) {
	LinkList p = L->next;
	while(p) {
		pfun(p->data);
		p = p->next;
	}
}
