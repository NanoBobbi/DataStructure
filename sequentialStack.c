/*
	# 栈 Stack
		1. 栈（stack）是限定仅在表尾进行插入和删除操作的线性表。
		2. 我们把允许插入和删除的一端称为栈顶（top），另一端称为栈底（bottom），不含任何数据元素的栈称为空栈。栈又称为后进先出（LastIn First Out）的线性表，简称LIFO结构。
*/
#include "stdio.h"
#include "stdlib.h"
#define MAXSIZE 5
#define OK 0
#define ERROR 1
typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType data[MAXSIZE];
	int top;
}Stack;

Status init(Stack *S)
{
	S->top = -1;
	return OK;
}
Status push(Stack *S,ElemType newValue)
{
	/*栈满 */
	if (S->top == MAXSIZE - 1)
	{
		return ERROR;
	}
	S->top += 1;
	S->data[S->top] = newValue;
	return OK;
}

Status	pop(Stack *S,ElemType *obsolete)
{
	/*“当栈存在一个元素时，top等于0，因此通常把空栈的判定条件定为top等于-1。”*/
	if (S->top == -1)
	{
		return ERROR;
	}
	*obsolete = S->data[S->top];
	S->top -= 1;
	return OK;
}

Status foreach(Stack S)
{
	if (S.top == -1)
	{
		printf("The Stack is empty.\n");
		return ERROR;
	}
	for (int i = 0; i < S.top + 1; ++i)
	{
		printf("%d ", S.data[i]);
	}
	return OK;
}
int main(int argc, char const *argv[])
{
	Stack S;
	init(&S);
	push(&S,1);
	// printf("%d\n",S.top);
	foreach(S);
	return 0;
}