//
//  main.c
//  数据结构复习资料
//
//  Created by 陈华锋 on 2016/11/29.
//  Copyright © 2016年 陈华锋. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;
#define MAXSIZE 10
#define TRUE 1
#define FALSE 0

typedef struct
{
    ElemType elem[MAXSIZE];
    int length;
}SqList;

// 初始化顺序表
void InitList(SqList *L)
{
    L->length = 0;
}

// 查找值为item的元素在*L中的基于0的位置
int Locate(SqList *L, ElemType item)
{
    int i;
    for(i = 0; i < L->length; i ++)
        if(L->elem[i] == item)
            return i;
    printf("找不到该值!\n");
    return -1;
}

// 在指定位置(i, 基于0)插入e
int Insert(SqList *L, int i, ElemType e)
{
    int j;
    if(L->length == MAXSIZE)
    {
        printf("表满, 溢出.\n");
        return FALSE;
    }
    // 插入位置只可能在0~length
    else if(i < 0 || i > L->length)
    {
        printf("插入位置不合法.\n");
        return FALSE;
    }
    
    // 移动原始表中位于i ~ length - 1处的元素
    for(j = L->length - 1; j >= i; j --)
        L->elem[j + 1] = L->elem[j];
    L->elem[i] = e;
    L->length ++;
    return TRUE;
}

// 在指定位置(i, 基于0)删除元素
int Delete(SqList *L, int i)
{
    int j;
    if(L->length == 0)
    {
        printf("表空, 无法删除.\n");
        return FALSE;
    }
    // 删除位置只可能在0 ~ length - 1
    else if(i < 0 || i > L->length - 1)
    {
        printf("删除位置不合法.\n");
        return FALSE;
    }
    
    // 移动元素表中位于i + 1 ~ length - 1处的元素
    for(j = i + 1; j < L->length; j ++)
        L->elem[j - 1] = L->elem[j];
    L->length --;
    return TRUE;
}

// 显示表中所有数据
void Display(SqList *L)
{
    int i;
    printf("顺序表中数据如下:\n\n");
    for(i = 0; i < L->length; i ++)
    {
        printf("%10d%20d\n", i + 1, L->elem[i]);
    }
    printf("\n显示结束.\n");
}

// 显示菜单
void ShowMenu()
{
    printf("\n\n");
    printf("**********顺序表***********\n");
    printf("*         1:显示          *\n");
    printf("*         2:查找          *\n");
    printf("*         3:插入          *\n");
    printf("*         4:删除          *\n");
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
    ElemType e;
    SqList myList;
    InitList(&myList);
    srand((unsigned)time(0));
    for(i = 0; i < 5; i ++)
        Insert(&myList, i, rand() % 20 + 1);
    
    while(1)
    {
        switch(SelectMenu())
        {
            case 1:
                Display(&myList);
                break;
            case 2:
                printf("请输入要查找的值:");
                scanf("%d", &e);
                i = Locate(&myList, e);
                if(i < 0)
                    printf("未找到.\n");
                else
                {
                    printf("查找结果如下:\n");
                    printf("%10d%20d\n", i + 1, myList.elem[i]);
                }
                break;
            case 3:
                printf("插入位置(基于1):");
                scanf("%d", &i);
                printf("要插入的值:");
                scanf("%d", &e);
                if(Insert(&myList, i - 1, e) == TRUE)
                    printf("插入成功.\n");
                else
                    printf("插入失败.\n");
                break;
            case 4:
                printf("删除位置(基于1):");
                scanf("%d", &i);
                if(Delete(&myList, i - 1) == TRUE)
                    printf("删除成功.\n");
                else
                    printf("删除失败.\n");
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}
