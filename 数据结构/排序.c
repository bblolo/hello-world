#include <stdio.h>
#define NUM 100
#define TRUE 1
#define FALSE 0
typedef int KeyType;
typedef int InfoType;
typedef struct
{ 
     KeyType key;		     //关键字域
     InfoType otherinfo;	 //记录的其他域,根据具体应用来定义
}RecType;//记录类型
typedef RecType SqList[NUM + 1];	//记录类型的数组,为文件记录总数

void display(SqList R, int n)
{
	int i;
	printf("所有记录如下:\n");
	for(i = 0; i < n; i ++)
	{
		printf("%10d%10d\n", R[i].key, R[i].otherinfo);
	}
	printf("\n");
}

// 直接插入排序算法实现
// 
// 作用: 
// 		对数组R按不减顺序进行插入排序
//
// 参数说明: 
// 		R: 保存记录的数组, 可以保存NUM+1条记录 
// 		n: 真正的记录条数, 保存在R[1]~R[n]中 
void InsertSort(SqList R, int n)	
{  
	int i,j;
	// R[1]有序
	// R[2]~R[n]无序 
    for(i = 2; i <= n; i ++)
    {  
		R[0]=R[i];  // R[0]是监视哨, 保存待插入记录 
        j = i - 1;  // 从待插入记录的左侧开始寻找自身正确位置
        			// 注: R[i - 1]是已排好序的最大的数 
        			
		while(R[0].key < R[j].key)	// 如果待插入记录小于j处的记录 
             R[j+1] = R[j --];  	// 相当于:
			 						// R[j + 1] = R[j];
									// j --;
									// 意为: 将j处记录右移1位 
									
		// 上述循环最多执行结束时, j最小为0 
		// 两种情况跳出循环:
		// 1: j在大于0的某值时, 循环条件不满足, 说明待插入记录大于等于j处记录
		//    因此待插入记录应保存于j+1处
		// 2: j=1时循环条件仍满足, 意即待插入记录是目前最小的, j=0时不等号两边
		//    是同一记录, 循环退出, 此时j=0, 则待插入记录应保存于1处, 即j+1处 
		// 
         R[j + 1] = R[0];
     }  
}

// 希尔排序算法实现
// 
// 作用: 
// 		对数组R按不减顺序进行希尔排序
//
// 参数说明: 
// 		R: 保存记录的数组 
//         对于当前增量d[i], 所需的哨兵数量为d[i], 所有d[i]中d[0]最大
//         因此将R的前d[0]个元素用于保存哨兵
// 		n: 真正的记录条数, 保存在R[d[0]]~R[d[0] + n - 1]中 
//    d[]: 增量数组, 数组按照递减的顺序保存用于对R中记录进行分组的增量
//       : 最后一个增量为1 
//     dn: 增量个数 
// 希尔排序
void ShellSort(SqList R, int n, int d[], int dn) 
{
	int i, j, k, l, h;  
	RecType temp;
	for(i = 0; i < d[0]; i ++)
		R[i].key = -32767;
	
	k = 0;
	//do 
	//{
	//	h = d[k]; // 取本趟增量

	//	// 对h个组进行插入排序
	//	for(i = 0; i < h; i ++)
	//	{
	//		// 注: 第i组中第2条记录在R中的序号为d[0] + i + h
	//		for(j = d[0] + i + h; j < d[0] + n; j += h)
	//		{
	//			// 设置哨兵
	//			// 注: 第i组的哨兵为R[i], R[0]~R[d[0] - 1]为假哨兵, 用于结束循环
	//			temp = R[j];
	//			l = j - h;
	//			while(temp.key < R[l].key)
	//			{
	//				R[l + h] = R[l];
	//				l = l - h;
	//			}
	//			R[l + h] = temp;
	//		}
	//	}
	//	k ++;
	//}while(h != 1); /* 增量为1排序后终止算法 */

	do 
	{
		h = d[k]; // 取本趟增量

		
			// 注: 第i组中第2条记录在R中的序号为d[0] + i + h
			for(j = d[0] + h; j < d[0] + n; j ++)
			{
				// 设置哨兵, R[0]~R[d[0] - 1]为假哨兵, 用于结束循环
				temp = R[j];
				l = j - h;
				while(temp.key < R[l].key)
				{
					R[l + h] = R[l];
					l = l - h;
				}
				R[l + h] = temp;
			}
		
		k ++;
	}while(h != 1); /* 增量为1排序后终止算法 */
} 


// 冒泡排序算法实现
// 
// 作用: 
// 		对数组R按不减顺序进行冒泡排序
//
// 参数说明: 
// 		R: 保存记录的数组 
// 		n: 真正的记录条数, 保存在R[0]~R[n - 1]中 
void BubbleSort(SqList R, int n)	
{  
	int i, j, noswap;
	RecType temp;
	for(i = 0; i < n -1; i ++)
	{
		noswap = TRUE;
		for(j = n - 2; j >= i; j --)
		{
			if(R[j + 1].key < R[j].key)
			{
				temp = R[j + 1];
				R[j + 1] = R[j];
				R[j] = temp;
				noswap = FALSE;
			}
		}
		if(noswap)
			break;
	}
}

// 快速排序之划分 
// 
// 作用: 
// 		对数组R的连续无序子区进行划分, 形成左右两个无序子区
//		且左子区中记录均不超过某基准, 右子区中记录均不小于某基准 
//
// 参数说明: 
// 		R: 保存记录的数组 
// 	  low: 无序子区开始位置
//   high: 无序子区结束位置 
int Partition(SqList R, int low, int high)			           
{
	int i, j;
	RecType temp;
	i = low;
	j = high;
	temp = R[i];// 任选1条基准记录 
	do
	{
		// 自右向左查找第一条小于temp的记录 
		while(R[j].key >= temp.key && i < j)
			j --;
		// 交换R[i]和R[j] 
		if(i < j)
			R[i ++] = R[j];
		// 自左向右查找第一条大于temp的记录 
		while(R[i].key <= temp.key && i < j)
			i ++;
		// 交换R[i]和R[j] 
		if(i < j)
			R[j --] = R[i];
	}while(i < j);
	R[i] = temp;
	return i;
}

// 快速排序算法递归实现
// 
// 作用: 
// 		对数组R按不减顺序进行快速排序
//
// 参数说明: 
// 		R: 保存记录的数组
// 	  low: 要排序的区间起始位置
//	 high: 要排序的区间结束位置 
void QuickSort(SqList R, int low, int high)	
{  
	int i;
	if(low < high)
	{		
		i = Partition(R, low, high);
		QuickSort(R, low, i - 1);
		QuickSort(R, i + 1, high);
	}
}

// 直接选择排序算法实现
// 
// 作用: 
// 		对数组R按不减顺序进行快速排序
//
// 参数说明: 
// 		R: 保存记录的数组
// 		n: 真正的记录条数, 保存在R[0]~R[n - 1]中  
void SelectSort(SqList R, int n)	
{
	int i, j, k;
	RecType temp;
	for(i = 0; i < n - 1; i ++)
	{
		k = i;
		for(j = i + 1; j < n; j ++)
		{
			if(R[j].key < R[k].key)
				k = j;
		}
		if(k != i)
		{
			temp = R[i];
			R[i] = R[k];
			R[k] = temp;
		}
	}
}

void Shift(SqList R, int i, int m)
{
	int j;
	RecType temp;
	temp = R[i];
	j = 2 * i;
	while(j <= m)
	{
		if(j < m && R[j].key < R[j + 1].key)
			j ++;
		if(temp.key < R[j].key)	
		{
			R[i] = R[j];
			i = j;
			j = 2 * i;			
		}
		else
			break;
	}
	R[i] = temp;
}
//堆排序算法
void HeapSort(SqList R, int n)
{
    int i;
    RecType temp;
    for(i = n / 2; i >= 1; i --)
    	Shift(R, i, n);
   	for(i = n; i >= 1; i --)
   	{
		temp = R[1];
		R[1] = R[i];
		R[i] = temp;
		Shift(R, 1, i - 1);   	
	}
}


void main()
{
	SqList R = {
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{52, 1},
		{40, 2},
		{68, 3},
		{95, 4},
		{79, 5},
		{10, 6},
		{28, 7},
		{52, 8},
		{58, 9},
		{6, 10}
	};
	int d[] = {5, 3, 1};
	printf("排序前:\n");
	display(R + 5, 10);
	/*InsertSort(R + 4, 10);
	printf("插入排序后:\n");
	display(R + 5, 10);*/
	/*ShellSort(R, 10, d, 3);
	printf("希尔排序后:\n");
	display(R + 5, 10);*/
	/*
BubbleSort(R + 5, 10);
	printf("冒泡排序后:\n");
	display(R + 5, 10);*/
	/*
QuickSort(R, 5, 14);
	printf("快速排序后:\n");
	display(R + 5, 10);*/
	/*
HeapSort(R + 4, 10);
	printf("堆排序后:\n");
	display(R + 5, 10);*/
	SelectSort(R + 5, 10);
	printf("选择排序后:\n");
	display(R + 5, 10);
}



