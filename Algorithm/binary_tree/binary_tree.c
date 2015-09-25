/**
 * 二叉树
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct BitNode {
	int val;
	struct BitNode *left;
	struct BitNode *right;
} BitNode, *BiTree;

void 
CreateBinaryTree(BiTree *t)
{
	int val;
	scanf("%d", &val);
	if (val <= 0) {
		*t = NULL;
		return;
	} else {
		*t = malloc(sizeof(BitNode));
		(*t)->val = val;
		CreateBinaryTree(&((*t)->left));
		CreateBinaryTree(&((*t)->right));
	}
}

void
Visit(int val)
{
	printf("%d ", val);
}

/**
 * 获取节点个数
 */
int
GetNodeNum(BiTree t)
{
	if (t == NULL)
		return 0;
	return GetNodeNum(t->left) + GetNodeNum(t->right) + 1;
}

/**
 * 前序遍历
 */
void
PreOrderTraverse(BiTree t)
{
	if (t == NULL)
		return;
	
	Visit(t->val);
	PreOrderTraverse(t->left);
	PreOrderTraverse(t->right);
}

/**
 * 中序遍历
 */
void
InOrderTraverse(BiTree t)
{
	if (t == NULL)
		return;
	
	InOrderTraverse(t->left);
	Visit(t->val);
	InOrderTraverse(t->right);
}

/**
 * 后序遍历
 */
void
PostOrderTraverse(BiTree t)
{
	if (t == NULL)
		return;

	PostOrderTraverse(t->left);
	PostOrderTraverse(t->right);
	Visit(t->val);
}

int
main(void)
{
	BiTree t;
	
	printf("------CreateBinaryTree------\n");
	CreateBinaryTree(&t);

	printf("------PreOrderTraverse------\n");
	PreOrderTraverse(t);
	putchar('\n');

	printf("------InOrderTraverse------\n");
	InOrderTraverse(t);
	putchar('\n');

	printf("------PostOrderTraverse------\n");
	PostOrderTraverse(t);
	putchar('\n');

	return 0;
}
