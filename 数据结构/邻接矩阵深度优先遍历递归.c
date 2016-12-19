#include <stdio.h>
#define MAXSIZE 100
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

void DFSM(Graph *g, int *visited, int i)
{
	int j;
	printf("������ȱ�������:%c\n", g->vexs[i]);//�������
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
	// ����ͼ
	CreateGraph(&g);
	// ����ڽӾ���
	PrintEdges(&g);
	// ����������
	printf("������ȱ���˳��Ϊ:\n");
	DFS(&g);
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          