#include <stdlib.h>
#include "queue.h"

typedef struct QNode * QNodePtr;
typedef struct QNode {
	Item item;
	QNodePtr next;
}QNode;

struct queue {
	QNodePtr head;
	QNodePtr tail;
};

void
QueueInit(Q q) {
	q = malloc(sizeof(*q));
	q->head = NULL;
}

bool
QueueEmpty(Q q) {
	return q->head == NULL;
}

void
EnQueue(Q q, Item item) {
	QNodePtr p = malloc(sizeof(*p));
	p->item = item;

	if(q->head == NULL) {
		q->head = p;
		q->head = q->tail;
	} else {
		q->tail->next = p;
		q->tail = q->tail->next;
	}

}

Item
DeQueue(Q q) {
	QNodePtr p = q->head;
	Item item = p->item;
	q->tail = p->next;
	free(p);

	return item;
}
