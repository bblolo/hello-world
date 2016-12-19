#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024
#define TRUE 1
#define FALSE 0
typedef char TreeDataType;
typedef struct BiTNode
{
	TreeDataType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 为了非递归遍历二叉树而设计的栈
typedef struct BiTNode *StackDataType;
typedef struct{
	StackDataType data[MAXSIZE];
	int top;
}SqStack;

// 以下是栈的操作
// 初始化
int InitStack(SqStack *S)
{
    S->top = -1;
    return TRUE;
}

// 清空
int ClearStack(SqStack *S)
{
    S->top = -1;
    return TRUE;
}

// 判断栈空
int StackEmpty(SqStack *S)
{
    if(S->top == -1)
        return TRUE;
    else
        return FALSE;
}

// 获取栈长度
int StackLength(SqStack *S)
{
    return S->top + 1;
}

// 取栈顶元素(不删除)
int GetTop(SqStack *S, StackDataType *e)
{
    if(StackEmpty(S))    
        return FALSE;

    // 获取栈顶元素, 通过*e返回
    *e = S->data[S->top];
    return TRUE;
}


// 入栈
int Push(SqStack *S, StackDataType e)
{
    if(S->top == MAXSIZE - 1)
        return FALSE;
    S->top ++;
    S->data[S->top] = e;
    return TRUE;
}
// 出栈
int Pop(SqStack *S, StackDataType *e)
{
    if(StackEmpty(S))  
        return FALSE;
    *e = S->data[S->top];
    S->top --;
    return TRUE;
}
// 已上是栈的操作


// 创建二叉树
// 每个节点的数据都是一个字符
// 教材P118 图6.11所示的二叉树输入格式为:-+a00*b00c00/f00-d00e00回车
BiTree CreateBiTree()
{
	BiTree root = NULL;
	char value;
	scanf("%c", &value);
	// 如果输入的是字符'0'表示该节点为空
	if(value != '0')
	{
		root = (BiTree)malloc(sizeof(BiTNode));
		root->data = value;
		root->lchild = CreateBiTree();
		root->rchild = CreateBiTree();
	}
	return root;
}
// 中根遍历递归算法
void InOrderTraverseRecursion(BiTree T)
{
	if(T)
	{
		InOrderTraverseRecursion(T->lchild);
		printf("%c", T->data);
		InOrderTraverseRecursion(T->rchild);
	}
}
// 中根遍历非递归算法
void InOrderTraverse(BiTree T)
{
	// 定义栈
	SqStack stack;
	// 将二叉树根节点地址赋给P
	BiTNode *p = T;
	// 初始化栈
	InitStack(&stack);
	// 只要p非空或者栈非空
	while(p || !StackEmpty(&stack))
	{
		// 如果p非空
		if(p)
		{
			// 将p入栈
			Push(&stack, p);
			// 接下来处理左子树(在下一轮循环中也将其入栈)
			p = p->lchild;
		}
		// 如果p为空, 即某个节点的左子树为空
		else
		{
			// 将给节点出栈
			Pop(&stack, &p);
			// 访问该节点
			printf("%c", p->data);
			// 接下来处理该节点的右子树((在下一轮循环中将其入栈))
			p = p->rchild;
		}
	}
	// 结束
	printf("\n");
}

// 先根遍历递归算法
void PreOrderTraverseRecursion(BiTree T)
{
	if(T)
	{
		printf("%c", T->data);
		PreOrderTraverseRecursion(T->lchild);
		PreOrderTraverseRecursion(T->rchild);
	}
}

// 先根遍历非递归
void PreOrderTraverse(BiTree T)
{
	// 定义栈
	SqStack stack;
	// 将要便利的二叉树根节点地址赋给p
	BiTNode *p = T;
	// 初始化栈
	InitStack(&stack);
	// 只要p非空或者栈非空
	while(p || !StackEmpty(&stack))
	{
		// 如果p非空
		if(p)
		{
			// 访问p
			printf("%c", p->data);
			// 将p入栈
			Push(&stack, p);
			// 接下来处理p的左子树(在下一轮循环中也访问该节点, 并将其入栈, 如果其存在的话)
			p = p->lchild;
		}
		// 如果p空, 栈非空
		else
		{
			// 将前面已经访问过的节点出栈
			Pop(&stack, &p);
			// 接下来处理其右子树(在下一轮循环中访问该节点, 并将其入栈, 如果其存在的话)
			p = p->rchild;
		}
	}
	// 结束
	printf("\n");
}

// 先根遍历递归算法
void PostOrderTraverseRecursion(BiTree T)
{
	if(T)
	{		
		PostOrderTraverseRecursion(T->lchild);
		PostOrderTraverseRecursion(T->rchild);
		printf("%c", T->data);
	}
}

// 后根遍历非递归
void PostOrderTraverse(BiTree T)
{
	// 定义栈
	SqStack stack;
	// pre表示访问的前一个节点, 初始为空
	BiTNode *p, *pre = NULL;
	// 初始化栈
	InitStack(&stack);
	// 将要遍历的二叉树根节点入栈
	Push(&stack, T);
	// 只要栈非空
	while(!StackEmpty(&stack))
	{
		// 出栈
		Pop(&stack, &p);
		// 如果该节点的左孩子为空, 且右孩子为空
		if(p->lchild == NULL && p->rchild == NULL)
		{
			// 访问该节点
			printf("%c", p->data);
			// 将其赋给p
			pre = p;
		}		
		// 如果该节点有孩子节点, 且pre非空, 且pre是该节点的左孩子或右孩子
		// 无论哪种情况, 都说明该节点的所有孩子均已经被访问
		else if(pre != NULL && (pre == p->lchild || pre == p->rchild))
		{
			// 访问该节点
			printf("%c", p->data);
			// 将其赋给p
			pre = p;
		}
		// 其它情况
		else
		{
			// 还不能访问该节点, 将其再次入栈
			Push(&stack, p);
			// 如果有右孩子, 右孩子入栈
			if(p->rchild)
				Push(&stack, p->rchild);
			// 如果有左孩子, 左孩子入栈
			if(p->lchild)
				Push(&stack, p->lchild);
		}		
	}
	// 结束
	printf("\n");
}

int main()
{
	// 创建二叉树
	BiTree tree = CreateBiTree();
	// 中根遍历
	printf("中根遍历结果(非递归):\n");
	InOrderTraverse(tree);
	printf("中根遍历结果(递归):\n");
	InOrderTraverseRecursion(tree);
	printf("\n");
	// 先根遍历
	printf("先根遍历结果(非递归):\n");
	PreOrderTraverse(tree);
	printf("先根遍历结果(递归):\n");
	PreOrderTraverseRecursion(tree);
	printf("\n");
	// 后根遍历
	printf("后根遍历结果(非递归):\n");
	PostOrderTraverse(tree);
	printf("后根遍历结果(递归):\n");
	PostOrderTraverseRecursion(tree);
	printf("\n");
	return 1;
}