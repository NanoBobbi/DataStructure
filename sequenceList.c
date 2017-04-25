/*
#顺序线性表
##优点：
 1. 不用为表中元素的逻辑关系而额外增加存储空间
 2. 可以快速的读取表中任意位置的元素
##缺点：
 1. 插入和删除动作需要大量的移动数据
 2. 当线性表的长度变化较大时，难以确定存储空间的容量
 3. 容易造成存储空间的碎片化
*/
#include "stdio.h"
#include "stdlib.h"
/*存储空间初始分配量*/
#define MAXSIZE 20
#define OK 0
#define ERROR 1
#define TRUE 1
#define FALSE 0
typedef int status;
typedef int ElemType;

typedef struct
{
	/*数组存储数据元素，最大值为MAXSIZE */
	ElemType data[MAXSIZE];
	/*线性表当前长度*/
	int length;
}SqList;

status GetElem(SqList L,int position,ElemType *elem)
{
	if (L.length == 0 || position < 1 || position > L.length)
	{
		return ERROR;
	}
	*elem = L.data[position - 1];
	return OK;
}

status ListInsert(SqList *L,int position,ElemType elem)
{
	/*顺序线性表已满*/
	if (L->length == MAXSIZE)
	{
		return ERROR;
	}
	/*插入的位置position不在范围内*/
	if (position < 1 || position > L->length + 1)
	{
		return 2;
	}
	/*不是最后一个数时*/
	if (position <= L->length)
	{
		/*将position后面的数向后移动*/
		for (int i = L->length - 1; i >= position - 1; --i)
		{
			L->data[i + 1] = L->data[i];
		}
	}
	/*将数据elem 插入该位置*/
	L->data[position - 1] = elem;
	L->length++;
	return OK;
}

status ListDelete(SqList *L,int position,ElemType *elem)
{
	if (L->length == 0)
	{
		return ERROR;
	}
	if (position < 0 || position >= L->length)
	{
		return ERROR;
	}
	*elem = L->data[position - 1];
	if (position < L->length)
	{
		for (int i = position; i < L->length; ++i)
		{
			L->data[i - 1] = L->data[i];
		}
	}
	L->length--;
	return OK;
}

status foreach(SqList *L)
{
	if (L->length == 0)
	{
		printf("Empty!");
		return ERROR;
	}
	for (int i = 0; i < L->length; ++i)
	{
		printf("%d ",L->data[i]);
	}
	return OK;
}
int main(int argc, char const *argv[])
{
	SqList L;
	L->length = 0;
	int elem;
	for (int i = 0; i < 3; ++i)
	{
		ListInsert(&L,i+1,i);
	}
	ListDelete(&L,1,&elem);
	printf("\n%d,%d\n",L.length,elem );
	foreach(&L);
	return 0;
}