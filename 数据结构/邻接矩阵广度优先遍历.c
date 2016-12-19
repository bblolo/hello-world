#include <stdio.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct
{
	DataType vexs[MAXSIZE];		// ������Ϣ�� 
	int edges[MAXSIZE][MAXSIZE];// �ڽӾ���, �Խ���Ϊ0,��Ϊ����Ȩֵ, �����ڵı�Ϊ-1, ��ʾ����� 
	int numVexs, numEdges;		// �������ͱ��� 
}Graph;


// ����: ���в���
#define TRUE 1
#define FALSE 0

typedef int QueueDataType;
typedef struct {
	QueueDataType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

// ��ʼ��
int InitQueue(SqQueue *sq)
{
	sq->front = 0;
	sq->rear = 0;
	return TRUE;
}

// �ж϶����Ƿ�Ϊ��
int QueueEmpty(SqQueue *sq) 
{
	// ����������β�غ�
	if(sq->front == sq->rear)
		return TRUE;
	else
		return FALSE;
}

// ����г���
int QueueLength(SqQueue *sq)
{
	// ���㳤�Ȳ�����
	return (sq->rear - sq->front + MAXSIZE) % MAXSIZE; 
}

// ��ȡ����Ԫ��(��ɾ��)
int GetHead(SqQueue *sq, QueueDataType *e)
{
	if(QueueEmpty(sq))
		return FALSE;	
	*e = sq->data[sq->front];
	return TRUE;
}

// ���
int EnQueue(SqQueue *sq, QueueDataType e)
{
	if(sq->front == (sq->rear + 1) % MAXSIZE)
		return FALSE;
	sq->data[sq->rear] = e;
	sq->rear = (sq->rear + 1) % MAXSIZE;	
	return TRUE;		
}

// ����
int DeQueue(SqQueue *sq, QueueDataType *e)
{
	if(QueueEmpty(sq))
		return FALSE;
	*e = sq->data[sq->front];
	sq->front = (sq->front + 1) % MAXSIZE;
	return TRUE;
}

// ����: ���в���

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

void BSF(Graph *g, int v)
{
	int j;	
	SqQueue q;
	int visited[MAXSIZE];
	for(j = 0; j < g->numVexs; j ++)
		visited[j] = 0;
	InitQueue(&q);
	printf("���ʳ�����%c\n", g->vexs[v]);	
	visited[v] = 1;
	EnQueue(&q, v);
	while(!QueueEmpty(&q))
	{
		DeQueue(&q, &v);
		for(j = 0; j < g->numVexs; j ++)
		{
			if(g->edges[v][j] == 1 && !visited[j])
			{
				printf("���ʶ���%c\n", g->vexs[j]);
				visited[j] = 1;
				EnQueue(&q, j);
			}
		}
	}
}

int main()
{
	Graph g;
	CreateGraph(&g);
	PrintEdges(&g);
	BSF(&g, 0);
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              