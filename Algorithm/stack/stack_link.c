#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Item;
typedef struct Node * link;
typedef struct Node{
	Item item;
	link next;
} Node;

typedef struct Stack {
	link top;
	int length;
} Stack;

void
InitStack(Stack * stack) {
	stack->top = NULL;
	stack->length = 0;
}

link
New(Item item, link next) {
	link x = malloc(sizeof(Node));
	x->item = item;
	x->next = next;
	return x;
}

bool
Empty(Stack * stack) {
	return stack->length == 0;
}

void
Push(Stack * stack, Item item) {
	link p = New(item, stack->top);
	stack->top = p;
	stack->length = stack->length + 1;
}

bool
Pop(Stack * stack, Item *item) {
	if(Empty(stack))
		return false;

	*item = stack->top->item;
	link t = stack->top;
	stack->top = stack->top->next;
	stack->length = stack->length - 1;
	free(t);

	return true;
}

int
main(void) {
	Stack stack;
	InitStack(&stack);

	Item item1 = 3, item2 = 2, item3 = 1;
	Push(&stack, item1);
	Push(&stack, item2);
	Push(&stack, item3);

	printf("is empty : %d\n", Empty(&stack));

	Item temp;
	Pop(&stack, &temp);
	printf("pop %d\n", temp);

	Pop(&stack, &temp);
	printf("pop %d\n", temp);

	Pop(&stack, &temp);
	printf("pop %d\n", temp);

	printf("is empty : %d\n", Empty(&stack));

	return 0;
}

