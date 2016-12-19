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

// 初始化
int InitQueue(SqQueue *sq)
{
	sq->front = 0;
	sq->rear = 0;
	return TRUE;
}

// 判断队列是否为空
int QueueEmpty(SqQueue *sq) 
{
	// 如果队首与队尾重合
	if(sq->front == sq->rear)
		return TRUE;
	else
		return FALSE;
}

// 求队列长度
int QueueLength(SqQueue *sq)
{
	// 计算长度并返回
	return (sq->rear - sq->front + MAXSIZE) % MAXSIZE; 
}

// 获取队首元素(不删除)
int GetHead(SqQueue *sq, DataType *e)
{
	if(QueueEmpty(sq))
	{
		printf("空队列!\n");
		return FALSE;		
	}
	*e = sq->data[sq->front];
	return TRUE;
}

// 入队
int EnQueue(SqQueue *sq, DataType e)
{
	if(sq->front == (sq->rear + 1) % MAXSIZE)
	{
		printf("溢出!\n");
		return FALSE;
	}
	sq->data[sq->rear] = e;
	sq->rear = (sq->rear + 1) % MAXSIZE;	
	return TRUE;		
}

// 出队
int DeQueue(SqQueue *sq, DataType *e)
{
	if(QueueEmpty(sq))
	{
		printf("队列空!\n");
		return FALSE;
	}
	*e = sq->data[sq->front];
	sq->front = (sq->front + 1) % MAXSIZE;
	return TRUE;
}

// 从表头到表尾依次输出所有元素
int QueueTraverse(SqQueue *sq)
{
	int i;
	if(QueueEmpty(sq))
	{
		printf("队列空!\n");
		return FALSE;
	}
	printf("队列所有元素:\n");
	i = sq->front;
	while(i != sq->rear)
	{
		printf("%10d%20d\n", i + 1, sq->data[i]);
		i = (i + 1) % MAXSIZE;
	}
	printf("\n");
	return TRUE;
}

// 显示菜单
void ShowMenu()
{
    printf("\n\n");
    printf("**********顺序表***********\n");
    printf("*         1:显示          *\n");
    printf("*         2:队首          *\n");
    printf("*         3:入队          *\n");
    printf("*         4:出队          *\n");
    printf("*         0:退出          *\n");
    printf("***************************\n");
    printf("请选择:");
}
// 获取菜单
int SelectMenu()
{
    int sel;
    ShowMenu();
    scanf("%d", &sel);
    return sel;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    // 一些初始化操作
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
                printf("新元素值:");
                scanf("%d", &e);
                if(EnQueue(&myQueue, e) == TRUE)
                    printf("入队成功.\n");
                else
                    printf("入队失败.\n");
                break;
            case 4:
                if(DeQueue(&myQueue, &e) == TRUE)
                {
                    printf("出队的值:%d\n", e);
                    printf("出队成功.\n");
                    
                }
                else
                    printf("出队失败.\n");
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}