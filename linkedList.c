#include<stdio.h>//等号“=”，从左到右叫做指针的指向，从右到左叫做赋值
#include<stdlib.h>
#define OK 0
#define ERROR 1
typedef struct node
{
	int data;
	struct node *next;//链表的*next指针域中存的是下一个节点的地址，所以必须是struct node
}node,*pnode;

pnode creatlist(pnode head,int n)//头插法是把元素查到之前一个元素的前面，所以与输出顺序相反
{
	pnode p;
	int i;
	head=(pnode)malloc(sizeof(node));
	head->next=NULL;			//head仅仅起到了头指针的作用，不存放数据
	for(i=0;i<n;i++)
	{
		p=(pnode)malloc(sizeof(node));
		scanf("%d",&p->data);	//p才是真正存放数据的地域，直接引用head就能使用p，因为head的next指向p 
		p->next=head->next;//把L->next中的值（即null）赋给p->next，不能为null，由于头插在head的后面，否则与后面断开
		head->next=p;//在把p放在l->next，这两步是为了始终使得链表尾指向null
	}
  return head;
}

pnode creat(pnode L,int n)//尾插法，克服了之前倒序的问题，不过要额外指针r，算法变得复杂和晦涩
{
	pnode p,r;
	int i;
	L=(pnode)malloc(sizeof(node));
	L->next=NULL;
	r=L;			//r指向L
	for(i=0;i<n;i++)
	{
		p=(pnode)malloc(sizeof(node));
		scanf("%d",&p->data);	
		r->next=p;//使得r->next指向p，由于之前如何p等价，r->next和L->next同时指向p;
r=p;//为什么不直接写成L->next=p呢？第一个循环可以，如果都写成这样，循环就会一直赋给L，指针的变动无法实现所以用副量等价
	}//r=p，的含义是使p和r重名，之前r和L重名，都同时被指向p，而下一个循环又将r重新赋值，不影响之前的L
	//r->next=p；r=p；再次使得r->next和r同时指向p
	r->next=NULL;
	return L;
}

int insert(pnode L,int i,int e)
{
	pnode p,newnode;
	int j;
	p=L;//又是重名问题，如果直接写成L，就会改变原来的指针方向而无法复原，所以增加一个副指针
	for(j=0;j<i-1;j++)		
	{p=p->next;}
//	if(!p||j>i-1) return ERROR; 有点多此一举
	newnode=(pnode)malloc(sizeof(node));
	newnode->data=e;
	newnode->next=p->next;  //把指向下一个节点的指针赋给要插入的newnode节点的next
	p->next=newnode;//在把原本指向下个节点的指针 再指向newnode，就完成了插入
	return OK;
}

int del(pnode L,int i)
{
	pnode p,r;
	int j;
	p=L;//又是重名问题，如果直接写成L，就会改变原来的指针方向而无法复原，所以增加一个副指针
	for(j=0;j<i-1;j++)		
	{p=p->next;} 
	r=p->next;//r指向p->next  
	p->next=p->next->next;//把p节点的next的next，赋给p->next，即跳过中间的
	free(r);//在把r指向的就是上一步跳过的 释放掉
	return OK;
}

int length(pnode L)
{
	pnode p;
	int i;
	p=L;
	for(i=0;;i++)
	{
		p=p->next;
		if(p->next==NULL)
		{break;}
	}
	return i+1;
}

int getelem()
{}

int locate(pnode L,int e)
{
	pnode p;
	int i;
	p=L;
	for(i=0;;i++)
	{
		p=p->next;
		if(p->data==e)
		{break;}
		if(i>length(L))
		{
			printf("not found the data!");
			break;}
	}
	return i+1;
}

int load(pnode L)
{
	pnode p;
	int i;
	p=L->next;
	for(i=0;;i++)
	{		
		printf("%d ",p->data);
		p=p->next;
		if(p==NULL)
		{break;}
	}
	printf("\n");
	return OK;
}

int main()
{
	pnode L;
	printf("please input five elements:\n");
	L=creat(L,5);
	printf("The length of the list is %d\n",length(L));
	load(L);
	insert(L,1,8);	
	printf("The length of the list is %d\n",length(L));
	load(L);
	del(L,1);
	printf("The length of the list is %d\n",length(L));
	load(L);
	printf(	"the place of 5 is:%d\n",locate(L,5));

	return 0;
}
