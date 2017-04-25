/*
#单链式线性表
 1. 单链表采用链式存储结构，用一组任意的存储单元存放线性表的元素。单链表不需要分配存储空间，只要有就可以分配，元素个数不受限制。
 2. 单链表的查找操作开销比顺序表大，因为存储结构需要占据额外空间。但插入和删除的时间开销为O(1)，尤其在插入多个节点时，优势更加明显
#头指针
 1. 头指针是指向链表第一个节点。若有头节点则为头节点指针。
 2. 头指针具有标示的作用，所以常用头指针冠以链表的名字。
 3. 无论链表是否为空，头指针均不为空。头指针是链表的必要元素。
#头节点
 1. 头节点是为了操作的统一和方便而设立的，放在第一个元素的节点之前，其数据域一般无意义(本链表存放链表的长度)。
 2. 有了头节点，在插入或删除第一节点就与其他节点的操作就统一。
 3. 头节点不一定是链表的必要元素。
*/
#include "stdlib.h"
#include "stdio.h"
#ifndef OK
#define OK 0
#endif
#ifndef ERROR
#define ERROR 1
#endif
typedef int status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node,*pNode;
typedef pNode List;

status findPosition(pNode headNode,int position,pNode *ptr)
{
	if (position-1 > headNode->data || position <= 0)
	{
		printf("ERROR! Not find position. ");
		return ERROR;
	}
	*ptr = headNode;
	for (int i = 0; i < position - 1; ++i)
	{
		*ptr = (*ptr)->next;
	}
	return OK;
}
status getElem(pNode headNode,int position)
{
	pNode ptr;
	/*ptr 指向链表的第二个节点,所以位置加1*/
	if(position <= 0 || findPosition(headNode,position+1,&ptr) == ERROR)
	{
		printf("getElem fail!\n");
		return ERROR;
	}
	printf("elem:%d\n", ptr->data);
	return OK;
}

status listInsert(pNode headNode,int position,ElemType elem)
{
	pNode ptr,newNode;
	/*ptr 是个副指针，不能使用L，否则就改变了原来的结构*/
	if(findPosition(headNode,position,&ptr) == ERROR)
	{
		printf("Insert fail!\n");
		return ERROR;
	}
	newNode = (pNode)malloc(sizeof(Node));
	newNode->data = elem;
	/*以下两条语句顺序不能调换，必须先赋值后面在赋值前面，否则前面的地址会覆盖后面的地址*/
	newNode->next = ptr->next;
	ptr->next = newNode;
	headNode->data += 1;
	return OK;
}

status listDelete(pNode headNode,int position,ElemType *elem)
{
	pNode ptr,obsoleteNode;
	if(findPosition(headNode,position,&ptr) == ERROR)
	{
		printf("Delete fail!\n");
		return ERROR;
	}
	obsoleteNode = ptr->next;
	ptr->next = ptr->next->next;
//  ptr->next = obsoleteNode->next; 也可这样写
	*elem = obsoleteNode->data;
	/*free 之后依然能访问obsoleteNode的值，
	free函数是把你的这个内存重新放回到红黑树中，让别人可以申请到这个内存
	从逻辑上来说，你现在不能在使用这个内存了，因为它已经不属于你。
	但是系统的实现上目前没有做到，所以你还是能访问这个地址。
	另外，系统也不会帮你覆盖内存中的数据，因为做这一个操作浪费时间，没有必要。
	打一个简单的比方。你租了一套房子，后来租期到了，房子回到房东手里，或者又转租给别人。
	但是你拿着原来的钥匙还是能进入那套房子，虽然这个是不合法的。*/
	free(obsoleteNode);
	headNode->data -= 1;
	return OK;
}

/*双重指针！将headnode 的地址传入函数.
即便headnode的值就是地址类型的。将list的地址传入虚参，将值传回给实参。
如果是传值，那么函数调用完后，就被销毁，因为仅仅传入的是复制的值，并没有传回实参，跟交换同理。*/
void initWithoutReturnHead(pNode *headNode)
{
	*headNode = (pNode)malloc(sizeof(Node));
	(*headNode)->next = NULL;
	(*headNode)->data = 0;
}
/*返回headnode 的地址，就可以避免双重指针*/
pNode initWithReturnHead(pNode headNode)
{
	headNode = (pNode)malloc(sizeof(Node));
	headNode->next = NULL;
	headNode->data = 0;
	return headNode;
}

void assignByTail(pNode headNode,int number)
{
	pNode lastNode,newNode;
	/*lastNode 始终指向链表的最后一个节点*/
	lastNode = headNode;
	/*创建一个新节点后，将lastNode 指针向后移*/
	for (int i = 0; i < number; ++i)
	{
		newNode = (pNode)malloc(sizeof(Node));
		// scanf("%d",&newNode->data);
		newNode->data = i + 1;
		lastNode->next = newNode;
		lastNode = newNode;
	}
	/*最后一个节点一定要设置成NULL，之前头节点的NULL作废了*/
	lastNode->next = NULL;
	headNode->data = number;
}

void assignByHead(pNode headNode,int number)
{
	pNode newNode;
	for (int i = 0; i < number; ++i)
	{
		newNode = (pNode)malloc(sizeof(Node));
		newNode->data = i + 1;
		newNode->next = headNode->next;
		headNode->next = newNode;
	}
	headNode->data = number;
}

status clearList(pNode headNode)
{
	pNode ptr,obsoleteNode;
	if (headNode->data == 0)
	{
		printf("Warning! List is already empty.\n");
		return ERROR;
	}
	obsoleteNode = headNode->next;
	// 不能直接释放obsoleteNode,需用ptr保存它的下一个地址
	for (int i = 0; i < headNode->data; ++i)
	{
		ptr = obsoleteNode->next;
		free(obsoleteNode);
		obsoleteNode = ptr;
	}
	headNode->next = NULL;
	headNode->data = 0;
	return OK;
}

void foreach(pNode headNode)
{
	pNode ptr;
	ptr = headNode->next;
	if (headNode->data == 0)
	{
		printf("List is empty.\n");
		return;
	}
	// for (int i = 0; i < headNode->data; ++i)
	// {
	// 	printf("%d ", ptr->data);
	// 	ptr = ptr->next;
	// }
	while(ptr)
	{
		printf("%d ",ptr->data );
		ptr = ptr->next;
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	/*声明一个list ，list这个变量本身就有自己的地址和默认随机值（注意是地址类型的），不会自动存放还没初始化的链表地址*/
	List list;
	ElemType elem = 0;

	/*两种初始化链表头节点的方法*/
	initWithoutReturnHead(&list);
	// list = initWithReturnHead(list);

	/*尾插法和头插法，头插法顺序会颠倒*/
	assignByTail(list,5);
	// assignByHead(list,5);


	listInsert(list,1,12);
	listDelete(list,1,&elem);
	foreach(list);
	getElem(list,2);
	clearList(list);
	printf("%d\n", list->data);




	return 0;
}