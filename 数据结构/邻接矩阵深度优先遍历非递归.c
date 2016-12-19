#include <stdio.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct
{
	DataType vexs[MAXSIZE];		// 顶点信息表 
	int edges[MAXSIZE][MAXSIZE];// 邻接矩阵, 对角线为0,边为整数权值, 不存在的边为-1, 表示无穷大 
	int numVexs, numEdges;		// 顶点数和边数 
}Graph;


// 以下: 栈操作
#define TRUE 1
#define FALSE 0
typedef int StackDataType;

typedef struct{
    StackDataType data[MAXSIZE];
    int top;
}SqStack;

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
// 以上: 栈操作

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


void DFSM(Graph *g, int i)
{
	int visited[MAXSIZE], j, num = 0;
	SqStack stack;
	for(j = 0; j < g->numVexs; j ++)
		visited[j] = 0;
		
	InitStack(&stack);
	printf("访问起始顶点%c\n", g->vexs[i]);
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
					printf("访问顶点%c\n", g->vexs[j]);
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
					printf("访问顶点%c\n", g->vexs[j]);
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

