#include <stdio.h>

#define MAXSIZE 100
#define INTMAX 32767 

struct
{
	int end;// end�Ѿ���MST�� 
	int len;// ��ǰ��(����MST��)��end֮���ֱ�Ӿ��� 
}minedge[MAXSIZE];

// ����: ͼ�Ļ�������
typedef char DataType;
typedef struct
{
	DataType vexs[MAXSIZE];		// ������Ϣ�� 
	int edges[MAXSIZE][MAXSIZE];// �ڽӾ���, �Խ���Ϊ0,��Ϊ����Ȩֵ, �����ڵı�Ϊ-1, ��ʾ����� 
	int numVexs, numEdges;		// �������ͱ��� 
}Graph;

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
// ����: ͼ�Ļ�������


void prim(Graph *g, int u)
{
	int v, k, j, min;
	for(v = 0; v < g->numVexs; v ++)
	{// ��¼�������������б� 
		if(v != u)
		{
			minedge[v].end = u;
			minedge[v].len = g->edges[v][u];
		}
	}
	minedge[u].len = 0;//��ʾu�Ѿ�����MST 
	
	for(k = 0; k < g->numVexs - 1; k ++)
	{// ÿ����MST�м���1������,������g->numVexs - 1�� 
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
		if(min == INTMAX)//û���ҵ�ֱ�Ӿ�����С�Ķ��� 
		{
			printf("ͼ����ͨ, ��������!");
			return;
		}
		// v:�¼���MST�Ķ��� 
		// minedge[v].end:֮ǰ����MST�Ķ��� 
		printf("%c  %c\n", g->vexs[v], g->vexs[minedge[v].end]);
		minedge[v].len = 0;//��ʶ����v�ѱ�����MST 
		for(j = 0; j < g->numVexs; j ++)
		{// �����л�û����MST�еĶ���
		 // ���j���¼���MST�Ķ���v֮���ֱ�Ӿ����С
		 // �����minedge[j] 
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
	// ����ͼ
	CreateGraph(&g);
	// ����ڽӾ���
	PrintEdges(&g);
	// ������С������
	printf("Prim��С������:\n");
	prim(&g, 0);
	return 0;
}                 