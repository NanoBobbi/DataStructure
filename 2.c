#include<stdio.h>//�Ⱥš�=���������ҽ���ָ���ָ�򣬴��ҵ��������ֵ
#include<stdlib.h>
#define OK 0
#define ERROR 1
typedef struct node
{
	int data;
	struct node *next;//�����*nextָ�����д������һ���ڵ�ĵ�ַ�����Ա�����struct node
}node,*pnode;

pnode creatlist(pnode head,int n)//ͷ�巨�ǰ�Ԫ�ز鵽֮ǰһ��Ԫ�ص�ǰ�棬���������˳���෴
{
	pnode p;
	int i;
	head=(pnode)malloc(sizeof(node));
	head->next=NULL;			//head��������ͷָ������ã����������
	for(i=0;i<n;i++)
	{
		p=(pnode)malloc(sizeof(node));
		scanf("%d",&p->data);	//p��������������ݵĵ���ֱ������head����ʹ��p����Ϊhead��nextָ��p 
		p->next=head->next;//��L->next�е�ֵ����null������p->next������Ϊnull������ͷ����head�ĺ��棬���������Ͽ�
		head->next=p;//�ڰ�p����l->next����������Ϊ��ʼ��ʹ������βָ��null
	}
  return head;
}

pnode creat(pnode L,int n)//β�巨���˷���֮ǰ��������⣬����Ҫ����ָ��r���㷨��ø��Ӻͻ�ɬ
{
	pnode p,r;
	int i;
	L=(pnode)malloc(sizeof(node));
	L->next=NULL;
	r=L;			//rָ��L
	for(i=0;i<n;i++)
	{
		p=(pnode)malloc(sizeof(node));
		scanf("%d",&p->data);	
		r->next=p;//ʹ��r->nextָ��p������֮ǰ���p�ȼۣ�r->next��L->nextͬʱָ��p;
r=p;//Ϊʲô��ֱ��д��L->next=p�أ���һ��ѭ�����ԣ������д��������ѭ���ͻ�һֱ����L��ָ��ı䶯�޷�ʵ�������ø����ȼ�
	}//r=p���ĺ�����ʹp��r������֮ǰr��L��������ͬʱ��ָ��p������һ��ѭ���ֽ�r���¸�ֵ����Ӱ��֮ǰ��L
	//r->next=p��r=p���ٴ�ʹ��r->next��rͬʱָ��p
	r->next=NULL;
	return L;
}

int insert(pnode L,int i,int e)
{
	pnode p,newnode;
	int j;
	p=L;//�����������⣬���ֱ��д��L���ͻ�ı�ԭ����ָ�뷽����޷���ԭ����������һ����ָ��
	for(j=0;j<i-1;j++)		
	{p=p->next;}
//	if(!p||j>i-1) return ERROR; �е���һ��
	newnode=(pnode)malloc(sizeof(node));
	newnode->data=e;
	newnode->next=p->next;  //��ָ����һ���ڵ��ָ�븳��Ҫ�����newnode�ڵ��next
	p->next=newnode;//�ڰ�ԭ��ָ���¸��ڵ��ָ�� ��ָ��newnode��������˲���
	return OK;
}

int del(pnode L,int i)
{
	pnode p,r;
	int j;
	p=L;//�����������⣬���ֱ��д��L���ͻ�ı�ԭ����ָ�뷽����޷���ԭ����������һ����ָ��
	for(j=0;j<i-1;j++)		
	{p=p->next;} 
	r=p->next;//rָ��p->next  
	p->next=p->next->next;//��p�ڵ��next��next������p->next���������м��
	free(r);//�ڰ�rָ��ľ�����һ�������� �ͷŵ�
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