#include <stdio.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct
{
	DataType vexs[MAXSIZE];		// 顶点信息表 
	int edges[MAXSIZE][MAXSIZE];// 邻接矩阵, 对角线为0,边为整数权值, 不存在的边为-1, 表示无穷大 
	int numVexs, numEdges;		// 顶点数和边数 
}Graph;

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

void DFSM(Graph *g, int *visited, int i)
{
	int j;
	printf("深度优先遍历顶点:%c\n", g->vexs[i]);//输出顶点
	visited[i] = 1;
	for(j = 0; j < g->numVexs; j ++)
		if(g->edges[i][j] > 0 && !visited[j])
			DFSM(g, visited, j);	 
}

void DFS(Graph *g)
{
	int i;
	int visited[MAXSIZE];
	for(i = 0; i < g->numVexs; i ++)
		visited[i] = 0;
	for(i = 0; i < g->numVexs; i++)
		if(!visited[i])
			DFSM(g, visited, i);
}

int main()
{
	Graph g;
	// 创建图
	CreateGraph(&g);
	// 输出邻接矩阵
	PrintEdges(&g);
	// 输出遍历结果
	printf("深度优先遍历顺序为:\n");
	DFS(&g);
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          