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
}node,*pnode;// node��ʾstruct node��*pnode��ʾstruct node *

int init(pnode L)
{
	L->elem=(int*)malloc(MAX_INIT_SIZE*sizeof(int));//˳����Ǹ�L->elem����ռ�
	if(!L->elem)	return ERROR;//������䲻�ɹ����򷵻�error������ʧ��
	L->length=0;
	return OK;
}

int inert(pnode L,int i,Elemtype e)
{																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
	int *p,*q;//p��q ����ָ��elem�����ָ�룬���Ա��붨��Ϊint
	p=&L->elem[i-1];//p��q����ָ�룬ָ����ֻ�ܴ�ŵ�ַ
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

int delelem(pnode L,int e)//��Ԫ��ɾ��ֻ��ɾ��λ�ÿ�ǰ��һ��Ԫ��
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
	/*for(;i<=L->length-1;i++) ���ָ���ֱ�ۺͼ��
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