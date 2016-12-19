#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 5
#define TRUE 1
#define FALSE 0

typedef int DataType;
typedef struct {
	DataType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

// ��ʼ��
int InitQueue(SqQueue *sq)
{
	sq->front = 0;
	sq->rear = 0;
	return TRUE;
}

// �ж϶����Ƿ�Ϊ��
int QueueEmpty(SqQueue *sq) 
{
	// ����������β�غ�
	if(sq->front == sq->rear)
		return TRUE;
	else
		return FALSE;
}

// ����г���
int QueueLength(SqQueue *sq)
{
	// ���㳤�Ȳ�����
	return (sq->rear - sq->front + MAXSIZE) % MAXSIZE; 
}

// ��ȡ����Ԫ��(��ɾ��)
int GetHead(SqQueue *sq, DataType *e)
{
	if(QueueEmpty(sq))
	{
		printf("�ն���!\n");
		return FALSE;		
	}
	*e = sq->data[sq->front];
	return TRUE;
}

// ���
int EnQueue(SqQueue *sq, DataType e)
{
	if(sq->front == (sq->rear + 1) % MAXSIZE)
	{
		printf("���!\n");
		return FALSE;
	}
	sq->data[sq->rear] = e;
	sq->rear = (sq->rear + 1) % MAXSIZE;	
	return TRUE;		
}

// ����
int DeQueue(SqQueue *sq, DataType *e)
{
	if(QueueEmpty(sq))
	{
		printf("���п�!\n");
		return FALSE;
	}
	*e = sq->data[sq->front];
	sq->front = (sq->front + 1) % MAXSIZE;
	return TRUE;
}

// �ӱ�ͷ����β�����������Ԫ��
int QueueTraverse(SqQueue *sq)
{
	int i;
	if(QueueEmpty(sq))
	{
		printf("���п�!\n");
		return FALSE;
	}
	printf("��������Ԫ��:\n");
	i = sq->front;
	while(i != sq->rear)
	{
		printf("%10d%20d\n", i + 1, sq->data[i]);
		i = (i + 1) % MAXSIZE;
	}
	printf("\n");
	return TRUE;
}

// ��ʾ�˵�
void ShowMenu()
{
    printf("\n\n");
    printf("**********˳���***********\n");
    printf("*         1:��ʾ          *\n");
    printf("*         2:����          *\n");
    printf("*         3:���          *\n");
    printf("*         4:����          *\n");
    printf("*         0:�˳�          *\n");
    printf("***************************\n");
    printf("��ѡ��:");
}
// ��ȡ�˵�
int SelectMenu()
{
    int sel;
    ShowMenu();
    scanf("%d", &sel);
    return sel;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    // һЩ��ʼ������
    int i;
    DataType e;
    SqQueue myQueue;
    InitQueue(&myQueue);
    srand((unsigned)time(0));
    for(i = 0; i < 2; i ++)
        EnQueue(&myQueue, rand() % 20 + 1);
    
    while(1)
    {
        switch(SelectMenu())
        {
            case 1:
                QueueTraverse(&myQueue);
                break;
            case 2:
				if(GetHead(&myQueue, &e) == TRUE)
					printf("%10d%20d\n", myQueue.front + 1, e);
                break;
            case 3:
                printf("��Ԫ��ֵ:");
                scanf("%d", &e);
                if(EnQueue(&myQueue, e) == TRUE)
                    printf("��ӳɹ�.\n");
                else
                    printf("���ʧ��.\n");
                break;
            case 4:
                if(DeQueue(&myQueue, &e) == TRUE)
                {
                    printf("���ӵ�ֵ:%d\n", e);
                    printf("���ӳɹ�.\n");
                    
                }
                else
                    printf("����ʧ��.\n");
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}