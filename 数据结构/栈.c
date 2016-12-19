//
//  栈.c
//  数据结构复习资料
//
//  Created by 陈华锋 on 2016/11/29.
//  Copyright © 2016年 陈华锋. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 10
#define TRUE 1
#define FALSE 0
typedef int StackDataType;

typedef struct{
    StackDataType data[MAXSIZE];
    int top;
}SqStack;

// 初始化
int InitStack(SqStack *S)
{
    S->top = -1;
    return TRUE;
}

// 清空
int ClearStack(SqStack *S)
{
    S->top = -1;
    return TRUE;
}

// 判断栈空
int StackEmpty(SqStack *S)
{
    if(S->top == -1)
        return TRUE;
    else
        return FALSE;
}

// 获取栈长度
int StackLength(SqStack *S)
{
    return S->top + 1;
}

// 取栈顶元素(不删除)
int GetTop(SqStack *S, StackDataType *e)
{
    if(StackEmpty(S))
    {
        printf("栈空!\n");
        return FALSE;
    }
    // 获取栈顶元素, 通过*e返回
    *e = S->data[S->top];
    return TRUE;
}

// 显示所有元素
int DispStack(SqStack *S)
{
    int i;
    if(StackEmpty(S))
    {
        printf("栈空!\n");
        return FALSE;
    }
    printf("栈中所有元素如下:\n\n");
    i = S->top;
    while(i >= 0)
	{
        printf("%10d%20d\n", i + 1, S->data[i]);
		i --;
	}
    printf("输出完毕.\n");
    return TRUE;
}

// 入栈
int Push(SqStack *S, StackDataType e)
{
    if(S->top == MAXSIZE - 1)
    {
        printf("栈满!\n");
        return FALSE;
    }
    S->top ++;
    S->data[S->top] = e;
    return TRUE;
}
// 出栈
int Pop(SqStack *S, StackDataType *e)
{
    if(StackEmpty(S))
    {
        printf("栈空!\n");
        return FALSE;
    }
    *e = S->data[S->top];
    S->top --;
    return TRUE;
}

// 显示菜单
void ShowMenu()
{
    printf("\n\n");
    printf("**********顺序表***********\n");
    printf("*         1:显示          *\n");
    printf("*         2:栈顶元素      *\n");
    printf("*         3:入栈          *\n");
    printf("*         4:出栈          *\n");
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
    StackDataType e;
    SqStack myStack;
    InitStack(&myStack);
    srand((unsigned)time(0));
    for(i = 0; i < 5; i ++)
        Push(&myStack, rand() % 20 + 1);
    
    while(1)
    {
        switch(SelectMenu())
        {
            case 1:
                DispStack(&myStack);
                break;
            case 2:
                if(GetTop(&myStack, &e) == TRUE)
                    printf("%10d%20d\n", myStack.top + 1, e);
                break;
            case 3:
                printf("新元素值:");
                scanf("%d", &e);
                if(Push(&myStack, e) == TRUE)
                    printf("入栈成功.\n");
                else
                    printf("入栈失败.\n");
                break;
            case 4:
                if(Pop(&myStack, &e) == TRUE)
                {
                    printf("出栈的值:%d\n", e);
                    printf("出栈成功.\n");
                    
                }
                else
                    printf("出栈失败.\n");
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}


