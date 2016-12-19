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

// Ϊ�˷ǵݹ��������������Ƶ�ջ
typedef struct BiTNode *StackDataType;
typedef struct{
	StackDataType data[MAXSIZE];
	int top;
}SqStack;

// ������ջ�Ĳ���
// ��ʼ��
int InitStack(SqStack *S)
{
    S->top = -1;
    return TRUE;
}

// ���
int ClearStack(SqStack *S)
{
    S->top = -1;
    return TRUE;
}

// �ж�ջ��
int StackEmpty(SqStack *S)
{
    if(S->top == -1)
        return TRUE;
    else
        return FALSE;
}

// ��ȡջ����
int StackLength(SqStack *S)
{
    return S->top + 1;
}

// ȡջ��Ԫ��(��ɾ��)
int GetTop(SqStack *S, StackDataType *e)
{
    if(StackEmpty(S))    
        return FALSE;

    // ��ȡջ��Ԫ��, ͨ��*e����
    *e = S->data[S->top];
    return TRUE;
}


// ��ջ
int Push(SqStack *S, StackDataType e)
{
    if(S->top == MAXSIZE - 1)
        return FALSE;
    S->top ++;
    S->data[S->top] = e;
    return TRUE;
}
// ��ջ
int Pop(SqStack *S, StackDataType *e)
{
    if(StackEmpty(S))  
        return FALSE;
    *e = S->data[S->top];
    S->top --;
    return TRUE;
}
// ������ջ�Ĳ���


// ����������
// ÿ���ڵ�����ݶ���һ���ַ�
// �̲�P118 ͼ6.11��ʾ�Ķ����������ʽΪ:-+a00*b00c00/f00-d00e00�س�
BiTree CreateBiTree()
{
	BiTree root = NULL;
	char value;
	scanf("%c", &value);
	// �����������ַ�'0'��ʾ�ýڵ�Ϊ��
	if(value != '0')
	{
		root = (BiTree)malloc(sizeof(BiTNode));
		root->data = value;
		root->lchild = CreateBiTree();
		root->rchild = CreateBiTree();
	}
	return root;
}
// �и������ݹ��㷨
void InOrderTraverseRecursion(BiTree T)
{
	if(T)
	{
		InOrderTraverseRecursion(T->lchild);
		printf("%c", T->data);
		InOrderTraverseRecursion(T->rchild);
	}
}
// �и������ǵݹ��㷨
void InOrderTraverse(BiTree T)
{
	// ����ջ
	SqStack stack;
	// �����������ڵ��ַ����P
	BiTNode *p = T;
	// ��ʼ��ջ
	InitStack(&stack);
	// ֻҪp�ǿջ���ջ�ǿ�
	while(p || !StackEmpty(&stack))
	{
		// ���p�ǿ�
		if(p)
		{
			// ��p��ջ
			Push(&stack, p);
			// ����������������(����һ��ѭ����Ҳ������ջ)
			p = p->lchild;
		}
		// ���pΪ��, ��ĳ���ڵ��������Ϊ��
		else
		{
			// �����ڵ��ջ
			Pop(&stack, &p);
			// ���ʸýڵ�
			printf("%c", p->data);
			// ����������ýڵ��������((����һ��ѭ���н�����ջ))
			p = p->rchild;
		}
	}
	// ����
	printf("\n");
}

// �ȸ������ݹ��㷨
void PreOrderTraverseRecursion(BiTree T)
{
	if(T)
	{
		printf("%c", T->data);
		PreOrderTraverseRecursion(T->lchild);
		PreOrderTraverseRecursion(T->rchild);
	}
}

// �ȸ������ǵݹ�
void PreOrderTraverse(BiTree T)
{
	// ����ջ
	SqStack stack;
	// ��Ҫ�����Ķ��������ڵ��ַ����p
	BiTNode *p = T;
	// ��ʼ��ջ
	InitStack(&stack);
	// ֻҪp�ǿջ���ջ�ǿ�
	while(p || !StackEmpty(&stack))
	{
		// ���p�ǿ�
		if(p)
		{
			// ����p
			printf("%c", p->data);
			// ��p��ջ
			Push(&stack, p);
			// ����������p��������(����һ��ѭ����Ҳ���ʸýڵ�, ��������ջ, �������ڵĻ�)
			p = p->lchild;
		}
		// ���p��, ջ�ǿ�
		else
		{
			// ��ǰ���Ѿ����ʹ��Ľڵ��ջ
			Pop(&stack, &p);
			// ������������������(����һ��ѭ���з��ʸýڵ�, ��������ջ, �������ڵĻ�)
			p = p->rchild;
		}
	}
	// ����
	printf("\n");
}

// �ȸ������ݹ��㷨
void PostOrderTraverseRecursion(BiTree T)
{
	if(T)
	{		
		PostOrderTraverseRecursion(T->lchild);
		PostOrderTraverseRecursion(T->rchild);
		printf("%c", T->data);
	}
}

// ��������ǵݹ�
void PostOrderTraverse(BiTree T)
{
	// ����ջ
	SqStack stack;
	// pre��ʾ���ʵ�ǰһ���ڵ�, ��ʼΪ��
	BiTNode *p, *pre = NULL;
	// ��ʼ��ջ
	InitStack(&stack);
	// ��Ҫ�����Ķ��������ڵ���ջ
	Push(&stack, T);
	// ֻҪջ�ǿ�
	while(!StackEmpty(&stack))
	{
		// ��ջ
		Pop(&stack, &p);
		// ����ýڵ������Ϊ��, ���Һ���Ϊ��
		if(p->lchild == NULL && p->rchild == NULL)
		{
			// ���ʸýڵ�
			printf("%c", p->data);
			// ���丳��p
			pre = p;
		}		
		// ����ýڵ��к��ӽڵ�, ��pre�ǿ�, ��pre�Ǹýڵ�����ӻ��Һ���
		// �����������, ��˵���ýڵ�����к��Ӿ��Ѿ�������
		else if(pre != NULL && (pre == p->lchild || pre == p->rchild))
		{
			// ���ʸýڵ�
			printf("%c", p->data);
			// ���丳��p
			pre = p;
		}
		// �������
		else
		{
			// �����ܷ��ʸýڵ�, �����ٴ���ջ
			Push(&stack, p);
			// ������Һ���, �Һ�����ջ
			if(p->rchild)
				Push(&stack, p->rchild);
			// ���������, ������ջ
			if(p->lchild)
				Push(&stack, p->lchild);
		}		
	}
	// ����
	printf("\n");
}

int main()
{
	// ����������
	BiTree tree = CreateBiTree();
	// �и�����
	printf("�и��������(�ǵݹ�):\n");
	InOrderTraverse(tree);
	printf("�и��������(�ݹ�):\n");
	InOrderTraverseRecursion(tree);
	printf("\n");
	// �ȸ�����
	printf("�ȸ��������(�ǵݹ�):\n");
	PreOrderTraverse(tree);
	printf("�ȸ��������(�ݹ�):\n");
	PreOrderTraverseRecursion(tree);
	printf("\n");
	// �������
	printf("����������(�ǵݹ�):\n");
	PostOrderTraverse(tree);
	printf("����������(�ݹ�):\n");
	PostOrderTraverseRecursion(tree);
	printf("\n");
	return 1;
}