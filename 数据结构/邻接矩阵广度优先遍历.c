#include <stdio.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct
{
	DataType vexs[MAXSIZE];		// 顶点信息表 
	int edges[MAXSIZE][MAXSIZE];// 邻接矩阵, 对角线为0,边为整数权值, 不存在的边为-1, 表示无穷大 
	int numVexs, numEdges;		// 顶点数和边数 
}Graph;


// 以下: 队列操作
#define TRUE 1
#define FALSE 0

typedef int QueueDataType;
typedef struct {
	QueueDataType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

// 初始化
int InitQueue(SqQueue *sq)
{
	sq->front = 0;
	sq->rear = 0;
	return TRUE;
}

// 判断队列是否为空
int QueueEmpty(SqQueue *sq) 
{
	// 如果队首与队尾重合
	if(sq->front == sq->rear)
		return TRUE;
	else
		return FALSE;
}

// 求队列长度
int QueueLength(SqQueue *sq)
{
	// 计算长度并返回
	return (sq->rear - sq->front + MAXSIZE) % MAXSIZE; 
}

// 获取队首元素(不删除)
int GetHead(SqQueue *sq, QueueDataType *e)
{
	if(QueueEmpty(sq))
		return FALSE;	
	*e = sq->data[sq->front];
	return TRUE;
}

// 入队
int EnQueue(SqQueue *sq, QueueDataType e)
{
	if(sq->front == (sq->rear + 1) % MAXSIZE)
		return FALSE;
	sq->data[sq->rear] = e;
	sq->rear = (sq->rear + 1) % MAXSIZE;	
	return TRUE;		
}

// 出队
int DeQueue(SqQueue *sq, QueueDataType *e)
{
	if(QueueEmpty(sq))
		return FALSE;
	*e = sq->data[sq->front];
	sq->front = (sq->front + 1) % MAXSIZE;
	return TRUE;
}

// 以上: 队列操作

// 创建图
void CreateGraph(Graph *G) 
{
	int i, j, k, w;
	printf("顶点数:");
	scanf("%d", &G->numVexs);
	printf("边数:");
	scanf("%d", &G->numEdges);
	// 顶点用字符表示
	printf("请输入顶点信息(字符), 建立顶点信息表:\n");
	for(i = 0; i < G->numVexs; i ++)
	{
		printf("第%d个顶点(字符):", i);
		// 清空输入缓冲区
		fflush(stdin);
		scanf("%c", &G->vexs[i]);
	}
	for(i = 0; i < G->numVexs; i ++)// 邻接矩阵初始化 
	{ 
		for(j = 0; j < G->numVexs; j ++)
			G->edges[i][j] = -1; 
		G->edges[i][i] = 0;
	}
	for(k = 0; k < G->numEdges; k ++)//读入边的顶点编号和权值, 建立邻接矩阵
	{
		printf("请输入第%d条边的顶点序号i, j(基于0, i和j必须不同)和权值w(必须大于0), 用逗号隔开:", k);
		scanf("%d,%d,%d", &i, &j, &w);
		G->edges[i][j] = w;
		G->edges[j][i] = w;
	} 
}

// 输出邻接矩阵
void PrintEdges(Graph *G)
{
	int i, j;
	printf("邻接矩阵:\n");
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
	printf("访问出发点%c\n", g->vexs[v]);	
	visited[v] = 1;
	EnQueue(&q, v);
	while(!QueueEmpty(&q))
	{
		DeQueue(&q, &v);
		for(j = 0; j < g->numVexs; j ++)
		{
			if(g->edges[v][j] == 1 && !visited[j])
			{
				printf("访问顶点%c\n", g->vexs[j]);
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