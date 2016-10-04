#include<stdio.h>
#include<stdlib.h>
#define Elemtype int 
#define OK 0
#define ERROR 1
#define MAX_INIT_SIZE 100
typedef struct node
{
	Elemtype *elem;
	int length;
}node,*pnode;// node表示struct node，*pnode表示struct node *

int init(pnode L)
{
	L->elem=(int*)malloc(MAX_INIT_SIZE*sizeof(int));//顺序表是给L->elem分配空间
	if(!L->elem)	return ERROR;//如果分配不成功，则返回error，分配失败
	L->length=0;
	return OK;
}

int inert(pnode L,int i,Elemtype e)
{																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
	int *p,*q;//p和q 都是指向elem数组的指针，所以必须定义为int
	p=&L->elem[i-1];//p和q都是指针，指针内只能存放地址
	for(q=&L->elem[L->length-1];q>=p;q--)
	{*(q+1)=*q;}
		*p=e;
		L->length++;
	return OK;
}

int del(pnode L,int i)
{
	int *p,*q;
	p=&L->elem[L->length-1];
	for(q=&L->elem[i-1];q<=p;q++)
	{*q=*(q+1);}
	L->length--;
	return OK;
}

int delelem(pnode L,int e)//按元素删除只能删除位置靠前的一个元素
{
	int *p,*q;
	int i=0;
	if(L->length==0)
		return ERROR;
	p=&L->elem[L->length-1];
	for(q=&L->elem[0];q<=p;q++)
	{
		if(*q==e)
		{
			for(;q<=p;q++)
			*q=*(q+1);			
		}					
	}
	L->length--;
	return OK;
}

int locate(pnode L,int e)
{
	int i=0,*p,*q;
	if(L->length==0) printf("Input ERROR");
	p=&L->elem[L->length-1];
	for(q=&L->elem[0];q<=p;q++)
	{
		if(*q==e)
		{
			prinf("the place of the element %d is: %d",*q,i+1);	
		}
		i++;
	}	
	/*for(;i<=L->length-1;i++) 这种更加直观和简洁
	if(*q==e)
		{
	prinf("the place of the element %d is: %d",*q,i+1);	
		}*/
	return i;
}

int load(pnode L)
{
	int *p,*q;
	int i=0;
	if(L->length==0)
		return ERROR;
	p=&L->elem[L->length-1];
	for(q=&L->elem[0];q<=p;q++)
	{
		printf("the %dth elem is %d\n ",i+1,*q);
		i++;
	}
	return OK;
}

int empty(pnode L)
{
	L->length=0;
	return OK;
}

int main()
{
	node L;
	int i,e,n;
	printf("Please input the length of the list:");
	scanf("%d",&n);
	if(init(&L)==OK) printf("The list has been set:\n");
	printf("Please input %d elements\n",n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&e);
		inert(&L,i,e);
	}
	load(&L);
	printf("Please input the the data to delete:");
	scanf("%d",&e);
	delelem(&L,e);
	load(&L);
}