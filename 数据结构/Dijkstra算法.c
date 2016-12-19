#include <stdio.h>
#define MAXSIZE 100
#define INTMAX 32767

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
			G->edges[i][j] = INTMAX; 
		G->edges[i][i] = 0;
	}
	for(k = 0; k < G->numEdges; k ++)//���뻡�Ķ����ź�Ȩֵ, �����ڽӾ���
	{
		printf("�������%d�����Ķ������i, j(����0, i��j���벻ͬ)��Ȩֵw(�������0), �ö��Ÿ���:", k);
		scanf("%d,%d,%d", &i, &j, &w);
		G->edges[i][j] = w;
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
			printf("%10d", G->edges[i][j]);
		printf("\n");
	}
}
// ����: ͼ�Ļ�������

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
	flag[v] = 1;//v ���������
	// Ŀ�ĵ���n-1��, ѭ��n-1��, ÿ��ȷ��Դ�㵽1��Ŀ�ĵص����·��
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
		// ��ʾʣ�µĵ��Դ��֮�䶼������·��
		if(min == INTMAX)
			// ����������
			break;
		
		flag[k] = 1;//k��������ϣ���ʾ��v��k�����·����ȷ�� 
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
			printf("Դ��%c������%c�����·��������.\n", g->vexs[v], g->vexs[i]);
			continue;
		}

		printf("Դ��%c������%c�����·����:%d\n", g->vexs[v], g->vexs[i], dist[i]);
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
	// ����ͼ
	CreateGraph(&g);
	// ����ڽӾ���
	PrintEdges(&g);
	// �������㵽Դ������·��
	printf("������Դ�����(����0):");
	scanf("%d", &start);
	Dijkstra(&g, start);
	return 0;
}         