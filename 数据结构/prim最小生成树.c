#include <stdio.h>

#define MAXSIZE 100
#define INTMAX 32767 

struct
{
	int end;// end已经在MST中 
	int len;// 当前点(不在MST中)与end之间的直接距离 
}minedge[MAXSIZE];

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
// 以上: 图的基本操作


void prim(Graph *g, int u)
{
	int v, k, j, min;
	for(v = 0; v < g->numVexs; v ++)
	{// 记录与起点关联的所有边 
		if(v != u)
		{
			minedge[v].end = u;
			minedge[v].len = g->edges[v][u];
		}
	}
	minedge[u].len = 0;//表示u已经加入MST 
	
	for(k = 0; k < g->numVexs - 1; k ++)
	{// 每次向MST中加入1个顶点,共加入g->numVexs - 1次 
		min = INTMAX; 
		v = -1;
		for(j = 0; j < g->numVexs; j ++)
		{
			if(minedge[j].len > 0 && minedge[j].len < min)
			{				
				min = minedge[j].len;
				v = j;
			}
		}
		if(min == INTMAX)//没有找到直接距离最小的顶点 
		{
			printf("图不连通, 无生成树!");
			return;
		}
		// v:新加入MST的顶点 
		// minedge[v].end:之前就在MST的顶点 
		printf("%c  %c\n", g->vexs[v], g->vexs[minedge[v].end]);
		minedge[v].len = 0;//标识顶点v已被加入MST 
		for(j = 0; j < g->numVexs; j ++)
		{// 对所有还没有在MST中的顶点
		 // 如果j与新加入MST的顶点v之间的直接距离更小
		 // 则更新minedge[j] 
			if(minedge[j].len != 0)
			{
				if(minedge[j].len < 0 || (g->edges[j][v] > 0 && g->edges[j][v] < minedge[j].len))
				{
					minedge[j].len = g->edges[j][v];
					minedge[j].end = v;
				}
			}
		}
	} 
}

int main()
{
	Graph g;
	// 创建图
	CreateGraph(&g);
	// 输出邻接矩阵
	PrintEdges(&g);
	// 创建最小生成树
	printf("Prim最小生成树:\n");
	prim(&g, 0);
	return 0;
}                 