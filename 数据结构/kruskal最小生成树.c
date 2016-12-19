#include <stdio.h>

#define NMAX 100
#define INTMAX 32767

typedef struct 
{
	int v1, v2;
	int len;
}EdgeType;

int parent[NMAX];

int GetRoot(int v)
{
	int i;
	i = v;
	while(parent[i] != i)
		i = parent[i];
	return i;
}

// em:已经从小到大排好序的边数组
// vertex_num: 顶点数量
// edge_num: 边数量 
void Krushal(EdgeType em[], int vertex_num, int edge_num)
{
	int i, p1, p2, m, i0;
	for(i = 0; i < vertex_num; i ++)
		parent[i] = i;
	i0 = 0;
	m = 1;
	while(m < vertex_num)
	{		
		p1 = GetRoot(em[i0].v1);
		p2 = GetRoot(em[i0].v2);
		if(p1 == p2)
		{ 
			i0 ++; 
			continue;
		} 
		
		// 序号较小的根作为合并后的根 
		if(p1 > p2)
			parent[p1] = p2;
		else
			parent[p2] = p1;
			
		printf("%d  %d  %d\n", m, em[i0].v1, em[i0].v2);
		i0 ++;
		m ++;
	}
}

int main()
{
	EdgeType em[10] = {
		{0, 2, 1},
		{3, 5, 2},
		{1, 4, 3},
		{2, 5, 4},
		{0, 3, 5},
		{1, 2, 5},
		{2, 3, 5},
		{0, 1, 6},
		{2, 4, 6},	
		{4, 5, 6},
	};
	Krushal(em, 6, 10);			
} 