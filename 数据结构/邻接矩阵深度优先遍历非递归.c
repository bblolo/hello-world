#include <stdio.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct
{
	DataType vexs[MAXSIZE];		// ������Ϣ�� 
	int edges[MAXSIZE][MAXSIZE];// �ڽӾ���, �Խ���Ϊ0,��Ϊ����Ȩֵ, �����ڵı�Ϊ-1, ��ʾ����� 
	int numVexs, numEdges;		// �������ͱ��� 
}Graph;


// ����: ջ����
#define TRUE 1
#define FALSE 0
typedef int StackDataType;

typedef struct{
    StackDataType data[MAXSIZE];
    int top;
}SqStack;

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
// ����: ջ����

// ����ͼ
void CreateGraph(Graph *G) 
{
	int i, j, k, w;
	printf("������:");
	scanf("%d", &G->numVexs);
	printf("����:");
	scanf("%d", &G->numEdges);
	// �������ַ���ʾ
	printf("�����붥����Ϣ(�ַ�), ����������Ϣ��:\n");
	for(i = 0; i < G->numVexs; i ++)
	{
		printf("��%d������(�ַ�):", i);
		// ������뻺����
		fflush(stdin);
		scanf("%c", &G->vexs[i]);
	}
	for(i = 0; i < G->numVexs; i ++)// �ڽӾ����ʼ�� 
	{ 
		for(j = 0; j < G->numVexs; j ++)
			G->edges[i][j] = -1; 
		G->edges[i][i] = 0;
	}
	for(k = 0; k < G->numEdges; k ++)//����ߵĶ����ź�Ȩֵ, �����ڽӾ���
	{
		printf("�������%d���ߵĶ������i, j(����0, i��j���벻ͬ)��Ȩֵw(�������0), �ö��Ÿ���:", k);
		scanf("%d,%d,%d", &i, &j, &w);
		G->edges[i][j] = w;
		G->edges[j][i] = w;
	} 
}

// ����ڽӾ���
void PrintEdges(Graph *G)
{
	int i, j;
	printf("�ڽӾ���:\n");
	for(i = 0; i < G->numVexs; i ++)
	{
		for(j = 0; j < G->numVexs; j ++)
			printf("%5d", G->edges[i][j]);
		printf("\n");
	}
}


void DFSM(Graph *g, int i)
{
	int visited[MAXSIZE], j, num = 0;
	SqStack stack;
	for(j = 0; j < g->numVexs; j ++)
		visited[j] = 0;
		
	InitStack(&stack);
	printf("������ʼ����%c\n", g->vexs[i]);
	visited[i] = 1;
	num ++;
	Push(&stack, i);
	while(num < g->numVexs)
	{
		if(!StackEmpty(&stack))
		{
			GetTop(&stack, &i);
			for(j = 0; j < g->numVexs; j ++)
				if(g->edges[i][j] > 0 && !visited[j])
				{
					printf("���ʶ���%c\n", g->vexs[j]);
					visited[j] = 1;
					num ++;
					Push(&stack, j);
					break;
				}
			if(j == g->numVexs)
				Pop(&stack, &i);
		}
		else
		{
			for(j = 0; j < g->numVexs; j ++)
				if(!visited[j])
				{
					printf("���ʶ���%c\n", g->vexs[j]);
					visited[j] = 1;
					num ++;
					Push(&stack, j);
					break;
				}
		}
	}
	ClearStack(&stack);
} 


int main()
{
	Graph g;
	CreateGraph(&g);
	PrintEdges(&g);
	DFSM(&g, 0);
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

