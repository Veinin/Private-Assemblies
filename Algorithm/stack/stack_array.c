#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_CODE -1
#define STACK_SIZE 10

typedef struct Stack {
	int top;
	int val[STACK_SIZE];
} Stack;

void 
InitStack(Stack * stack) {
	stack->top = 0;
}

bool
Empty(Stack *stack) {
	return stack->top == 0; 
}

void
Push(Stack *stack, int v) {
	stack->top = stack->top + 1;
	stack->val[stack->top] = v;
}

int
Pop(Stack *stack) {
	if(Empty(stack))
		return ERROR_CODE;

	stack->top = stack->top - 1;
	return 	stack->val[stack->top + 1];
}

int
main(void) {
	Stack stack;
	InitStack(&stack);
	
	Push(&stack, 3);
	Push(&stack, 2);
	Push(&stack, 1);

	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));

	printf("is empty : %d\n", Empty(&stack));

	return 0;
}
