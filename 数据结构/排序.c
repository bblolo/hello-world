#include <stdio.h>
#define NUM 100
#define TRUE 1
#define FALSE 0
typedef int KeyType;
typedef int InfoType;
typedef struct
{ 
     KeyType key;		     //�ؼ�����
     InfoType otherinfo;	 //��¼��������,���ݾ���Ӧ��������
}RecType;//��¼����
typedef RecType SqList[NUM + 1];	//��¼���͵�����,Ϊ�ļ���¼����

void display(SqList R, int n)
{
	int i;
	printf("���м�¼����:\n");
	for(i = 0; i < n; i ++)
	{
		printf("%10d%10d\n", R[i].key, R[i].otherinfo);
	}
	printf("\n");
}

// ֱ�Ӳ��������㷨ʵ��
// 
// ����: 
// 		������R������˳����в�������
//
// ����˵��: 
// 		R: �����¼������, ���Ա���NUM+1����¼ 
// 		n: �����ļ�¼����, ������R[1]~R[n]�� 
void InsertSort(SqList R, int n)	
{  
	int i,j;
	// R[1]����
	// R[2]~R[n]���� 
    for(i = 2; i <= n; i ++)
    {  
		R[0]=R[i];  // R[0]�Ǽ�����, ����������¼ 
        j = i - 1;  // �Ӵ������¼����࿪ʼѰ��������ȷλ��
        			// ע: R[i - 1]�����ź���������� 
        			
		while(R[0].key < R[j].key)	// ����������¼С��j���ļ�¼ 
             R[j+1] = R[j --];  	// �൱��:
			 						// R[j + 1] = R[j];
									// j --;
									// ��Ϊ: ��j����¼����1λ 
									
		// ����ѭ�����ִ�н���ʱ, j��СΪ0 
		// �����������ѭ��:
		// 1: j�ڴ���0��ĳֵʱ, ѭ������������, ˵���������¼���ڵ���j����¼
		//    ��˴������¼Ӧ������j+1��
		// 2: j=1ʱѭ������������, �⼴�������¼��Ŀǰ��С��, j=0ʱ���Ⱥ�����
		//    ��ͬһ��¼, ѭ���˳�, ��ʱj=0, ��������¼Ӧ������1��, ��j+1�� 
		// 
         R[j + 1] = R[0];
     }  
}

// ϣ�������㷨ʵ��
// 
// ����: 
// 		������R������˳�����ϣ������
//
// ����˵��: 
// 		R: �����¼������ 
//         ���ڵ�ǰ����d[i], ������ڱ�����Ϊd[i], ����d[i]��d[0]���
//         ��˽�R��ǰd[0]��Ԫ�����ڱ����ڱ�
// 		n: �����ļ�¼����, ������R[d[0]]~R[d[0] + n - 1]�� 
//    d[]: ��������, ���鰴�յݼ���˳�򱣴����ڶ�R�м�¼���з��������
//       : ���һ������Ϊ1 
//     dn: �������� 
// ϣ������
void ShellSort(SqList R, int n, int d[], int dn) 
{
	int i, j, k, l, h;  
	RecType temp;
	for(i = 0; i < d[0]; i ++)
		R[i].key = -32767;
	
	k = 0;
	//do 
	//{
	//	h = d[k]; // ȡ��������

	//	// ��h������в�������
	//	for(i = 0; i < h; i ++)
	//	{
	//		// ע: ��i���е�2����¼��R�е����Ϊd[0] + i + h
	//		for(j = d[0] + i + h; j < d[0] + n; j += h)
	//		{
	//			// �����ڱ�
	//			// ע: ��i����ڱ�ΪR[i], R[0]~R[d[0] - 1]Ϊ���ڱ�, ���ڽ���ѭ��
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
	//}while(h != 1); /* ����Ϊ1�������ֹ�㷨 */

	do 
	{
		h = d[k]; // ȡ��������

		
			// ע: ��i���е�2����¼��R�е����Ϊd[0] + i + h
			for(j = d[0] + h; j < d[0] + n; j ++)
			{
				// �����ڱ�, R[0]~R[d[0] - 1]Ϊ���ڱ�, ���ڽ���ѭ��
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
	}while(h != 1); /* ����Ϊ1�������ֹ�㷨 */
} 


// ð�������㷨ʵ��
// 
// ����: 
// 		������R������˳�����ð������
//
// ����˵��: 
// 		R: �����¼������ 
// 		n: �����ļ�¼����, ������R[0]~R[n - 1]�� 
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

// ��������֮���� 
// 
// ����: 
// 		������R�����������������л���, �γ�����������������
//		���������м�¼��������ĳ��׼, �������м�¼����С��ĳ��׼ 
//
// ����˵��: 
// 		R: �����¼������ 
// 	  low: ����������ʼλ��
//   high: ������������λ�� 
int Partition(SqList R, int low, int high)			           
{
	int i, j;
	RecType temp;
	i = low;
	j = high;
	temp = R[i];// ��ѡ1����׼��¼ 
	do
	{
		// ����������ҵ�һ��С��temp�ļ�¼ 
		while(R[j].key >= temp.key && i < j)
			j --;
		// ����R[i]��R[j] 
		if(i < j)
			R[i ++] = R[j];
		// �������Ҳ��ҵ�һ������temp�ļ�¼ 
		while(R[i].key <= temp.key && i < j)
			i ++;
		// ����R[i]��R[j] 
		if(i < j)
			R[j --] = R[i];
	}while(i < j);
	R[i] = temp;
	return i;
}

// ���������㷨�ݹ�ʵ��
// 
// ����: 
// 		������R������˳����п�������
//
// ����˵��: 
// 		R: �����¼������
// 	  low: Ҫ�����������ʼλ��
//	 high: Ҫ������������λ�� 
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

// ֱ��ѡ�������㷨ʵ��
// 
// ����: 
// 		������R������˳����п�������
//
// ����˵��: 
// 		R: �����¼������
// 		n: �����ļ�¼����, ������R[0]~R[n - 1]��  
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
//�������㷨
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
	printf("����ǰ:\n");
	display(R + 5, 10);
	/*InsertSort(R + 4, 10);
	printf("���������:\n");
	display(R + 5, 10);*/
	/*ShellSort(R, 10, d, 3);
	printf("ϣ�������:\n");
	display(R + 5, 10);*/
	/*
BubbleSort(R + 5, 10);
	printf("ð�������:\n");
	display(R + 5, 10);*/
	/*
QuickSort(R, 5, 14);
	printf("���������:\n");
	display(R + 5, 10);*/
	/*
HeapSort(R + 4, 10);
	printf("�������:\n");
	display(R + 5, 10);*/
	SelectSort(R + 5, 10);
	printf("ѡ�������:\n");
	display(R + 5, 10);
}



