#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct queue * Q;
typedef int Item;

void QueueInit(Q);
bool QueueEmpty(Q);
void EnQueue(Q, Item item);
Item DeQueue(Q);

#endif
