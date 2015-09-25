/**
 * 二叉查找树
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Item;
typedef struct STNode {
	Item item;
	struct STNode * l;
	struct STNode * r;
} STNode, *Node;

Node
New(Item item) {
	Node node = malloc(sizeof(STNode));
	node->item = item;
	node->l = node->r = NULL;
	return node;
}

bool
InsertBST(Node node, Item item) {
	if(node == NULL) {
		node = New(item);
		return true;
	}

	if(node->item == item)
		return false;

	if(node->item > item && node->l == NULL) {	//左子树为空，直接插入
		node->l = New(item);
		return true;
	}

	if(node->item < item && node->r == NULL) {	//右子树为空，直接插入
		node->r = New(item);
		return true;
	}

	if(node->item > item) {
		return InsertBST(node->l, item);
	} else {
		return InsertBST(node->r, item);
	}
}

Item
SearchBST(Node node, Item item) {
	if(node == NULL)
		return -1;
	else if(node->item == item) {
		return node->item;
	} else if(node->item > item) {
		return SearchBST(node->l, item);
	} else {
		return SearchBST(node->r, item);
	}
}

bool
DeleteBST(Node node, Item item) {
	if(node == NULL)
		return false;

	return false;
}

void
ClearNodes(Node head) {
	Node l, r;
	if(head != NULL) {
		l = head->l;
		r = head->r;
		free(head);
		ClearNodes(l);
		ClearNodes(r);
	}
}

void
PrintNodes(Node head) {
	if(head != NULL) {
		PrintNodes(head->l);
		printf("%d ", head->item);
		PrintNodes(head->r);
	}
}

int main(void) {
	int i;

	Node head = New(5);

	//insert
	int array[] = {10, 6, 4, 3, 2};
	for(i = 0; i < 5; i++) {
		bool ret = InsertBST(head, array[i]);
	}

	//print
	printf("Binary tree : \n");
	PrintNodes(head);
	putchar('\n');

	//search
	Item s = SearchBST(head, 10);
	printf("search bst : %d\n", s);

	//clear all node
	ClearNodes(head);

	return 0;
}
