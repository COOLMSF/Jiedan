#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"


/*初始化操作, 建立一个二叉数 */
void InitTree(TreeNodePtr* T)
{
	*T = NULL;
}

/*若二叉树存在, 则销毁它 */
void DestroyTree(TreeNodePtr* T)
{
	if (*T == NULL)
		return;

	if ((*T)->lchild != NULL)
		DestroyTree(&(*T)->lchild);
	if ((*T)->rchild != NULL)
		DestroyTree(&(*T)->rchild);
	
	free(*T);
	*T = NULL;
}


/*

*/
TreeNodePtr FindElem(TreeNodePtr T, DataType e)
{
    if (T == NULL)
        return NULL;

	if (*(int *)T->data == *(int *)e)
		return T;
	
	if (*(int *)(T->data) < *(int *)e)
	{
		if (T->rchild == NULL)
			return T;
		return FindElem(T->rchild, e);
	}
	
	if (*(int *)(T->data) > *(int *)e)
	{
		if (T->lchild == NULL)
			return T;
		return FindElem(T->lchild, e);
	}

	return NULL;
}

/*若二叉树不存在, 创建二叉树并把e赋给根结点，否则平衡插入值e */
void InsertTree(TreeNodePtr* T, DataType e)
{
	TreeNodePtr o = (TreeNodePtr)calloc(1, sizeof(TreeNode));
	o->data = e;

	if (*T == NULL)
	{
		*T = o;
		return;
	}

	TreeNodePtr root = FindElem(*T, e);
	if (root == NULL)
		return;

	if (*(int *)(root->data) < *(int *)e)
	{
		root->rchild = o;
	}
	else if (*(int *)(root->data) > *(int *)e)
	{
		root->lchild = o;
	}
	else
	{
		printf("Node already exists\n", e);
		free(o);
		o = NULL;
		return;
	}
}


void __delete(TreeNodePtr* T)
{
	TreeNodePtr p = (*T)->lchild, q = (*T)->rchild;
	// 删除结点, 接左子树
	if (q == NULL)
	{
		free(*T);
		*T = p;

		return;
	}

	// 删除结点, 接右子树
	if (p == NULL)
	{
		free(*T);
		*T = q;

		return;
	}

	// 将树T进行中序遍历后结点e的下一个结点f赋给e, 并删除f
	while (q->lchild != NULL)
	{
		p = q;
		q = q->lchild;
	}

	(*T)->data = q->data;
	p->lchild = q->rchild;
	free(q);
}

/*若二叉树存在结点e, 则删除之 */
void DeleteNode(TreeNodePtr* T, DataType e)
{
	if (*T == NULL)
		return;

	if (*(int *)((*T)->data) == *(int *)e)
		__delete(T);
	else if (*(int *)((*T)->data) > *(int *)e)
		DeleteNode(&(*T)->lchild, e);
	else
		DeleteNode(&(*T)->rchild, e);
}


/*判断二叉树是否为空, 空返回true, 否则false */
bool TreeEmpty(TreeNodePtr T)
{
	if (T == NULL)
		return true;
	return false;
}

/*若二叉树存在, 输出其结点个数 */
int NodeCount(TreeNodePtr T)
{
	if (T == NULL)
		return 0;

	int l = NodeCount(T->lchild);
	int r = NodeCount(T->rchild);

	return l + r + 1;
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
DataType TreeDepth(TreeNodePtr T)
{
	if (T == NULL)
		return 0;
	int l = 0, r = 0;
	if (T->lchild)
		l = *(int *)TreeDepth(T->lchild);
	if (T->rchild)
		r = *(int *)TreeDepth(T->rchild);

	// return (l > r ? l + 1 : r + 1);

	if (l > r) {
	    int k = l + 1;
	    return (DataType )&k;
	}
}

/* 操作结果: 返回T所指结点的值 */
DataType Value(TreeNodePtr T)
{
	return T->data;
}

/* 给T所指结点赋值为value */
void Assign(TreeNodePtr T, DataType value)
{
	T->data = value;
}


/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序递归遍历T */
void InOrderTraverse(TreeNodePtr T)
{
	if (!T) return;
	InOrderTraverse(T->lchild);
	printf("%d ", *(int *)(T->data));
	InOrderTraverse(T->rchild);
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序递归遍历T */
void PostOrderTraverse(TreeNodePtr T)
{
	if (!T) return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%d ", *(int *)(T->data));
}



#pragma region TREE_NODE_STACK_OP

/*栈结构--结点--开始 */
typedef struct NodeStack
{
	TreeNodePtr			data;
	struct NodeStack*	next;
}NodeStack, *NodeStackPtr;


typedef struct SeqStack
{
	NodeStackPtr		top;
	int					count;
}SeqStack, *SeqStackPtr;

void init_stack(SeqStackPtr S)
{
	S->top = NULL;
	S->count = 0;
}
/*栈结构--结点--结束 */


/*结点--栈结构操作:入栈 */
void push_stack(SeqStackPtr S, TreeNodePtr T)
{
	if (!T)	return;

	NodeStackPtr node = (NodeStackPtr)malloc(sizeof(NodeStack));
	node->data = T;
	node->next = S->top;

	S->top = node;
	++S->count;
}


/*结点--栈结构操作:出栈 */
TreeNodePtr pop_stack(SeqStackPtr S)
{
	if (S->count <= 0)	return NULL;

	NodeStackPtr top = S->top;
	TreeNodePtr node = top->data;

	S->top = top->next;
	free(top);

	top = NULL;
	--S->count;

	return node;
}

 
TreeNodePtr top_stack(SeqStackPtr S)
{
	if (S->count <= 0)	return NULL;
	return S->top->data;
}


void __free_stack(NodeStackPtr node)
{
	if (!node) return;

	__free_stack(node->next);
	free(node);
	node = NULL;
}
void free_stack(SeqStackPtr S)
{
	if (!S)	return;
	__free_stack(S->top);
}


void __print_stack(NodeStackPtr node)
{
	if (!node) return;

	__print_stack(node->next);
	printf("%d ", *(int *)(node->data->data));
}

void print_stack(SeqStackPtr S)
{
	if (!S) return;

	static int i = 0;
	__print_stack(S->top);
	printf("\n");
}
#pragma endregion


#pragma region TREE_NODE_QUEUE_OP
/*队列结构--结点--开始 */
typedef struct SeqQueue
{
	NodeStackPtr		back;
	NodeStackPtr		front;
	int					count;
}SeqQueue, *SeqQueuePtr;


void init_queue(SeqQueuePtr Q)
{
	Q->back = NULL;
	Q->front = NULL;
	Q->count = 0;
}


void push_queue(SeqQueuePtr Q, TreeNodePtr T)
{
	if (!T)	return;

	NodeStackPtr node = (NodeStackPtr)malloc(sizeof(NodeStack));
	node->data = T;
	node->next = NULL;

	if (Q->count == 0)
	{
		Q->front = node;
		Q->back = node;
	}
	else
	{
		Q->back->next = node;
		Q->back = node;
	}

	++Q->count;
}


TreeNodePtr pop_queue(SeqQueuePtr Q)
{
	if (Q->count <= 0)	return NULL;

	NodeStackPtr node = Q->front;
	TreeNodePtr data = node->data;

	Q->front = node->next;
	--Q->count;

	free(node);
	node = NULL;

	return data;
}
#pragma endregion


/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序循环遍历T */
void PreOrderLoop(TreeNodePtr T)
{
	if (!T) return;
	SeqStack S;
	init_stack(&S);

	while (T || S.count != 0)
	{
		while (T)
		{
			printf("%d ", *(int *)(T->data));
			push_stack(&S, T);
			T = T->lchild;
		}

		T = pop_stack(&S);
		T = T->rchild;
	}
	printf("\n");
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序循环遍历T */
void InOrderLoop(TreeNodePtr T)
{
	if (!T) return;
	SeqStack S;
	init_stack(&S);

	while (T || S.count != 0)
	{
		while (T)
		{
			push_stack(&S, T);
			T = T->lchild;
		}

		T = pop_stack(&S);
		printf("%d ", *(int *)(T->data));
		T = T->rchild;
	}
	printf("\n");
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序循环遍历T */
void PostOrderLoop(TreeNodePtr T)
{
	if (!T) return;

	SeqStack S;
	init_stack(&S);

	TreeNodePtr p = T, r = NULL;
	while (p || S.count > 0)
	{
		//p 不为空, 将结点p入栈, 进行下一轮循环, 直至左子树全部入栈
		if (p)
		{
			push_stack(&S, p);
			p = p->lchild;
		}

		//p 为空
		else
		{
			//将栈顶赋给p
			p = top_stack(&S);

			//如果p的右子树为空值, 则输出p结点. 并把r指向p, p置为空;
			//如果p的右子树已输出, 则输出p结点. 并把r指向p, p置为空;
			//否则将其右子树入栈, 并将左子树赋给p, 进行下一轮循环
			//其中r表示上一次输出的结点
			if (!p->rchild || p->rchild == r)
			{
				r = pop_stack(&S);
				printf("%d ", *(int *)(p->data));

				r = p;
				p = NULL;
			}
			else
			{
				p = p->rchild;
				push_stack(&S, p);
				p = p->lchild;
			}
		}
	}

	printf("\n");
}

#define D_Test
void PostOrderLoop2(TreeNodePtr T)
{
	TreeNodePtr cur = T, pre = NULL;
	SeqStack S, S2;
	init_stack(&S);
	init_stack(&S2);

	//根节点入栈
	push_stack(&S, cur);
	while (S.count > 0)
	{
#ifdef D_Test
		print_stack(&S);
#endif

		//取栈顶
		cur = top_stack(&S);

		//如果左右子树均不为空, 则出栈并输出, 将pre指向当前输出的结点
		//如果左右子树均已输出, 则出栈并输出, 将pre指向当前输出的结点
		//否则先将右子树入栈, 再将左子树入栈
		if ((cur->lchild == NULL && cur->rchild == NULL) ||
			(pre != NULL && (cur->lchild == pre || cur->rchild == pre)))
		{
			cur = pop_stack(&S);
#ifdef D_Test
			push_stack(&S2, cur);
#else
			printf("%d ", *(int *)(cur->data));
#endif
			pre = cur;
		}
		else
		{
			if (cur->rchild)
				push_stack(&S, cur->rchild);
			if (cur->lchild)
				push_stack(&S, cur->lchild);
		}
	}

#ifdef D_Test
	print_stack(&S2);
	free_stack(&S2);
#endif
	printf("\n");
}


/*层序遍历 树节点先进先出 */
void LevelTraversal(TreeNodePtr T)
{
	if (!T) return;

	SeqQueue Q;
	init_queue(&Q);

	while (1)
	{
		/*根结点输出 */
		if (Q.count == 0)
		{
			printf("%d ", *(int *)(T->data));
			if (T->lchild != NULL)
				push_queue(&Q, T->lchild);
			if (T->rchild != NULL)
				push_queue(&Q, T->rchild);
		}

		int i = 0, cnt = Q.count;
		for (; i < cnt; ++i)
		{
			TreeNodePtr data = pop_queue(&Q);
			if (data->lchild != NULL)
				push_queue(&Q, data->lchild);
			if (data->rchild != NULL)
				push_queue(&Q, data->rchild);
			printf("%d ", *(int *)(data->data));
		}

		if (Q.count == 0)
			break;
	}
	printf("\n");
}

