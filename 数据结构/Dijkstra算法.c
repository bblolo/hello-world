#include <stdio.h>
#define MAXSIZE 100
#define INTMAX 32767

// 以下: 图的基本操作
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
	printf("弧数:");
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
			G->edges[i][j] = INTMAX; 
		G->edges[i][i] = 0;
	}
	for(k = 0; k < G->numEdges; k ++)//读入弧的顶点编号和权值, 建立邻接矩阵
	{
		printf("请输入第%d条弧的顶点序号i, j(基于0, i和j必须不同)和权值w(必须大于0), 用逗号隔开:", k);
		scanf("%d,%d,%d", &i, &j, &w);
		G->edges[i][j] = w;
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
			printf("%10d", G->edges[i][j]);
		printf("\n");
	}
}
// 以上: 图的基本操作

void Dijkstra(Graph *g, int v)
{
	int dist[MAXSIZE], flag[MAXSIZE], pre[MAXSIZE];
	int i, j, k, vertex_idx, min;
	for(i = 0; i < g->numVexs; i ++)
	{
		flag[i] = 0;
		dist[i] = g->edges[v][i];
		if(dist[i] == INTMAX)
			pre[i] = -1;
		else
			pre[i] = v;
	}
	flag[v] = 1;//v 加入进集合
	// 目的地有n-1个, 循环n-1次, 每次确定源点到1个目的地的最短路径
	for(i = 1; i < g->numVexs; i ++)
	{
		min = INTMAX;
		for(j = 0; j < g->numVexs; j ++)
		{
			if(!flag[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		// 表示剩下的点和源点之间都不存在路径
		if(min == INTMAX)
			// 不用再找了
			break;
		
		flag[k] = 1;//k加入进集合，表示从v到k的最短路径已确定 
		for(j = 0; j < g->numVexs; j ++)
		{
			if(!flag[j] && dist[j] > dist[k] + g->edges[k][j])
			{
				dist[j] = dist[k] + g->edges[k][j];
				pre[j] = k;
			}
		}		
	} 
	for(i = 0; i < g->numVexs; i ++)
	{
		if(i == v)
			continue;
		
		if(dist[i] == INTMAX)
		{
			printf("源点%c到顶点%c的最短路径不存在.\n", g->vexs[v], g->vexs[i]);
			continue;
		}

		printf("源点%c到顶点%c的最短路径长:%d\n", g->vexs[v], g->vexs[i], dist[i]);
		printf("%c", g->vexs[i]);
		vertex_idx = pre[i];
		while(1)
		{
			printf("<-  %c", g->vexs[vertex_idx]);
			if(vertex_idx == v)
				break;
			vertex_idx = pre[vertex_idx];
		}
		printf("\n");
	}
}

int main()
{
	Graph g;
	int start;
	// 创建图
	CreateGraph(&g);
	// 输出邻接矩阵
	PrintEdges(&g);
	// 求其它点到源点的最短路径
	printf("请输入源点序号(基于0):");
	scanf("%d", &start);
	Dijkstra(&g, start);
	return 0;
}         