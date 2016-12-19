#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 标识一个不可能达到的最大权重值
#define MAX_WEIGHT 100000.0f

typedef struct
{
	char character;					// 要编码的字符
	float weight;					// 节点权值
	int parent, lchild, rchild;		// 双亲及左右孩子在数组中的下标
	char *code;						// 字符character对应的huffman编码
}HuffNode, *HuffTree;


// 构造哈夫曼树
// n: 叶子节点数量, 即要被编码的字符的数量
void Huffman(HuffTree tree, int n)
{
	int i, j, p1, p2, m;
	float small1, small2;

	// 哈夫曼树中非叶子节点的度均为2, 而二叉树中n2 = n0 - 1
	// 所以总节点数量为m = n2 + n1 + n0 = (n - 1) + 0 + n = 2 * n - 1
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
		printf("请输入第%d个编码字符信息:\n", i + 1);
		printf("字符:");
		// 清空输入缓冲区
		fflush(stdin);
		scanf("%c", &tree[i].character);
		printf("权重:");
		scanf("%f", &tree[i].weight);
	}

	// 进行n-1次合并, 产生n-1个新节点
	for(i = n; i < m; i ++) 
	{
		// 选取权值最小的根节点
		p1 = -1;
		p2 = -1;
		small1 = small2 = MAX_WEIGHT;
		for(j = 0; j < i; j ++)
		{
			// parent为-1表示该叶子节点还未参与合并
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

		// 合并p1和p2
		tree[p1].parent = i;
		tree[p2].parent = i;
		tree[i].lchild = p1;
		tree[i].rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
}

// 输出哈夫曼树
void Display(HuffTree tree, int n)
{
	int m = 2 * n - 1, i;
	printf("%10s%10s%10s%10s%10s%10s\n", "字符", "下标", "weight", "parent", "lchild", "rchild");
	for(i = 0; i < m; i ++)
	{
		printf("%10c%10d%10.2f%10d%10d%10d\n", tree[i].character, i, tree[i].weight, tree[i].parent, tree[i].lchild, tree[i].rchild);
	}
	printf("\n\n");
}

// 输出哈夫曼编码
void DisplayCode(HuffTree tree, int n)
{
	int i;
	printf("%10s%20s\n", "字符", "编码");
	for(i = 0; i < n; i ++)
		printf("%10c%20s\n", tree[i].character, tree[i].code);
	printf("\n\n");
}

// 生成Huffman编码
void HuffmanCode(HuffTree tree, int n)
{
	int c, p, start, i;
	// 临时保存编码的一段内存空间
	char *cd = (char*)malloc(sizeof(char*) * (n + 1));
	cd[n] = '\0';

	// 对于n个字符中的每一个求取其huffman编码
	for(i = 0; i < n; i ++)
	{
		// 用c保存当前的节点
		c = i;

		// start用于记录当前位编码的存储在cd中的下标
		start = n - 1; 
		
		// 双亲节点下标
		p = tree[c].parent;
		while(p != -1)
		{
			// 根据c是p的左或右孩子设置当前位的编码
			if(tree[p].lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';
			// 从右往左记录
			start --;
			// 更新c和p, 直至huffman树的根节点
			c = p;
			p = tree[c].parent;
		}
		// 根据上述while循环过程及记录下来的编码, 确定第i个字符的编码位数, 并分配空间, 空出1位保存结束符'\0'
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
	printf("请输入节点字符数量:");
	scanf("%d", &n);
	tree = (HuffTree)malloc(sizeof(HuffNode) * (2 * n - 1));
	// 创建Huffman树
	Huffman(tree, n);
	// 输出Huffman树
	Display(tree, n);
	// 生成Huffman编码
	HuffmanCode(tree, n);
	// 输出每个字符的Huffman编码
	DisplayCode(tree, n);

	// 释放内存
	FreeMemory(tree, n);
	return 1;
}
