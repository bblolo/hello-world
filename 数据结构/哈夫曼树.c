#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ��ʶһ�������ܴﵽ�����Ȩ��ֵ
#define MAX_WEIGHT 100000.0f

typedef struct
{
	char character;					// Ҫ������ַ�
	float weight;					// �ڵ�Ȩֵ
	int parent, lchild, rchild;		// ˫�׼����Һ����������е��±�
	char *code;						// �ַ�character��Ӧ��huffman����
}HuffNode, *HuffTree;


// �����������
// n: Ҷ�ӽڵ�����, ��Ҫ��������ַ�������
void Huffman(HuffTree tree, int n)
{
	int i, j, p1, p2, m;
	float small1, small2;

	// ���������з�Ҷ�ӽڵ�ĶȾ�Ϊ2, ����������n2 = n0 - 1
	// �����ܽڵ�����Ϊm = n2 + n1 + n0 = (n - 1) + 0 + n = 2 * n - 1
	m = 2 * n - 1;
	for(i = 0; i < m; i ++)
	{
		tree[i].parent = -1;
		tree[i].lchild = -1;
		tree[i].rchild = -1;
		tree[i].character = 0;
		tree[i].weight = 0.0;
	}

	for(i = 0; i < n; i ++)
	{
		printf("�������%d�������ַ���Ϣ:\n", i + 1);
		printf("�ַ�:");
		// ������뻺����
		fflush(stdin);
		scanf("%c", &tree[i].character);
		printf("Ȩ��:");
		scanf("%f", &tree[i].weight);
	}

	// ����n-1�κϲ�, ����n-1���½ڵ�
	for(i = n; i < m; i ++) 
	{
		// ѡȡȨֵ��С�ĸ��ڵ�
		p1 = -1;
		p2 = -1;
		small1 = small2 = MAX_WEIGHT;
		for(j = 0; j < i; j ++)
		{
			// parentΪ-1��ʾ��Ҷ�ӽڵ㻹δ����ϲ�
			if(tree[j].parent == -1)
			{
				if(tree[j].weight < small1)
				{
					small2 = small1;
					small1 = tree[j].weight;
					p2 = p1;
					p1 = j;
				}
				else if(tree[j].weight < small2)
				{
					small2 = tree[j].weight;
					p2 = j;
				}
			}
		}

		// �ϲ�p1��p2
		tree[p1].parent = i;
		tree[p2].parent = i;
		tree[i].lchild = p1;
		tree[i].rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
}

// �����������
void Display(HuffTree tree, int n)
{
	int m = 2 * n - 1, i;
	printf("%10s%10s%10s%10s%10s%10s\n", "�ַ�", "�±�", "weight", "parent", "lchild", "rchild");
	for(i = 0; i < m; i ++)
	{
		printf("%10c%10d%10.2f%10d%10d%10d\n", tree[i].character, i, tree[i].weight, tree[i].parent, tree[i].lchild, tree[i].rchild);
	}
	printf("\n\n");
}

// �������������
void DisplayCode(HuffTree tree, int n)
{
	int i;
	printf("%10s%20s\n", "�ַ�", "����");
	for(i = 0; i < n; i ++)
		printf("%10c%20s\n", tree[i].character, tree[i].code);
	printf("\n\n");
}

// ����Huffman����
void HuffmanCode(HuffTree tree, int n)
{
	int c, p, start, i;
	// ��ʱ��������һ���ڴ�ռ�
	char *cd = (char*)malloc(sizeof(char*) * (n + 1));
	cd[n] = '\0';

	// ����n���ַ��е�ÿһ����ȡ��huffman����
	for(i = 0; i < n; i ++)
	{
		// ��c���浱ǰ�Ľڵ�
		c = i;

		// start���ڼ�¼��ǰλ����Ĵ洢��cd�е��±�
		start = n - 1; 
		
		// ˫�׽ڵ��±�
		p = tree[c].parent;
		while(p != -1)
		{
			// ����c��p������Һ������õ�ǰλ�ı���
			if(tree[p].lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';
			// ���������¼
			start --;
			// ����c��p, ֱ��huffman���ĸ��ڵ�
			c = p;
			p = tree[c].parent;
		}
		// ��������whileѭ�����̼���¼�����ı���, ȷ����i���ַ��ı���λ��, ������ռ�, �ճ�1λ���������'\0'
		tree[i].code = (char*)malloc(sizeof(char) * n - start);
		strcpy(tree[i].code, &cd[start + 1]);
	}

	free(cd);
}

void FreeMemory(HuffTree tree, int n)
{
	int i;
	for(i = 0; i < n; i ++)
		free(tree[i].code);
	free(tree);
}

int main()
{
	int n;
	HuffTree tree;
	printf("������ڵ��ַ�����:");
	scanf("%d", &n);
	tree = (HuffTree)malloc(sizeof(HuffNode) * (2 * n - 1));
	// ����Huffman��
	Huffman(tree, n);
	// ���Huffman��
	Display(tree, n);
	// ����Huffman����
	HuffmanCode(tree, n);
	// ���ÿ���ַ���Huffman����
	DisplayCode(tree, n);

	// �ͷ��ڴ�
	FreeMemory(tree, n);
	return 1;
}
