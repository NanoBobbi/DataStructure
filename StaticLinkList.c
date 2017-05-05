/*
	# 静态链表
	1. 把未被使用的数组元素称为备用链表
	2. 数组的第一个元素，即下标为0的元素的cursor就存放备用链表的第一个节点的下标，data数据域为空。
	3. 数组的最后一个元素的cursor则存放第一个有值的元素的下标。

	## 优点
	* 在插入和删除操作时，只需要修改游标，不需要移动元素，从而改进了在顺序存储结构中的插入和删除操作需要移动大量元素的缺点
	## 缺点
	* 没有解决联系存储分配带来的表长难以确定的问题
	* 失去了顺序存储结构随机存取的特性
	*/
#include "stdio.h"
#define MAXSIZE 20
#define ERROR 1
#define OK 0
typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType data;
	int cursor;
}Component,StaticLinkList[MAXSIZE];

/*将space变成备用链表*/
Status initList(StaticLinkList space)
{
	for (int i = 0; i < MAXSIZE - 1; ++i)
	{
		space[i].cursor = i + 1;
	}
	space[MAXSIZE - 1].cursor = 0;
	space[0].data = 0;
	return 0;
}

/*赋值 并将部分的备用链表初始化已用链表*/
Status assign(StaticLinkList space,int number)
{
	for (int i = 0; i < number; ++i)
	{
		space[i+1].data = i + 1;
	}
	/*已用链表的最后一个元素的cursor指向头元素*/
	space[number].cursor = 0;
	/*头元素的cursor指向备用链表的头元素*/
	space[0].cursor = number + 1;
	/*数组的最后一个元素的cursor指向已用链表的头元素*/
	space[MAXSIZE-1].cursor = 1;
	return 0;
}
/*“为了辨明数组中哪些分量未被使用，解决的办法是将所有未被使用过的及已被删除的分量用游标链成一个备用的链表”

摘录来自: 程杰. “大话数据结构”。 iBooks. */
int malloc_StaticLinkList(StaticLinkList space)
{
	int headOfFreeSpace;
	headOfFreeSpace = space[0].cursor;
	/*如果备用链表不为空，拿出一个分量后，将下一个分量作为备用。头元素的cursor指向下一个备用元素*/
	if (space[0].cursor)
	space[0].cursor = space[headOfFreeSpace].cursor;
	return headOfFreeSpace;
}

/*将该节点还原成备用链表的第一个节点*/
void free_StaticLinkList(StaticLinkList space,int position)
{
	/*要删除的节点的cursor指向备用链表的首元素*/
	space[position].cursor = space[0].cursor;
	/*数组头元素指向要删除的该节点*/
	space[0].cursor = position;
}

/*返回已用链表的长度*/
int length(StaticLinkList L)
{
	int count = 0;
	int ptrOfIndex = L[MAXSIZE-1].cursor;
	while(ptrOfIndex != 0)
	{
		ptrOfIndex = L[ptrOfIndex].cursor;
		count++;
	}
	return count;
}

Status insert(StaticLinkList L,int position,ElemType newValue)
{
	int ptr = MAXSIZE-1,indexOfTheNew;
	if (position < 1 || position > length(L) + 1)
	{
		return ERROR;
	}
	/*得到一个空余位置*/
	indexOfTheNew = malloc_StaticLinkList(L);
	if (indexOfTheNew)
	{
		L[indexOfTheNew].data = newValue;
		/*找到位置为position-1的元素，如果position的值为1，则不执行循环，last仍为最后数组元素*/
		for (int i = 0; i < position - 1; ++i)
		{
			ptr = L[ptr].cursor;
		}
		/*跟链表插入算法一样，以下两句不能颠倒*/
		L[indexOfTheNew].cursor = L[ptr].cursor;
		L[ptr].cursor = indexOfTheNew;
		return OK;
	}
	return ERROR;
}

Status delete(StaticLinkList L,int position)
{
	int ptr = MAXSIZE-1,obsolete;
	if (position < 1 || position > length(L))
	{
		return ERROR;
	}
	for (int i = 0; i < position - 1; ++i)
	{
		ptr = L[ptr].cursor;
	}
	obsolete = L[ptr].cursor;
	L[ptr].cursor = L[obsolete].cursor;
	free_StaticLinkList(L,obsolete);
	return OK;

}

Status foreach(StaticLinkList L)
{
	int ptr = L[MAXSIZE-1].cursor;
	if (ptr == 0)
	{
		printf("The StaticLinkList is empty.\n");
		return ERROR;
	}
	printf("%s %s %s\n","index","value","cursor");
	for (int i = 0; i < length(L); ++i)
	{
		printf("%5d %5d %5d\n",ptr,L[ptr].data,L[ptr].cursor );
		ptr = L[ptr].cursor;
	}
	return OK;
}
int main(int argc, char const *argv[])
{
	StaticLinkList SList;
	initList(SList);
	assign(SList,5);
	delete(SList,4);
	insert(SList,2,6);
	foreach(SList);
	return 0;
}