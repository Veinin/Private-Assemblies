#include <stdio.h>
#include "queue.h"

int
main(void) {
	Q q;
	QueueInit(q);

	Item i1 = 1, i2 = 2, i3 = 3, temp;
	EnQueue(q, i1);
	EnQueue(q, i2);
	EnQueue(q, i3);

	printf("queue empty : %d\n", QueueEmpty(q));

	temp = DeQueue(q);
	printf("dequeue val : %d\n", temp);

	temp = DeQueue(q);
	printf("dequeue val : %d\n", temp);
	
	printf("queue empt : %d\n", QueueEmpty(q));

	return 0;
}
