#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define OK 1
#define ERROR 0
#define true 1
#define false 0

typedef struct Node
{
 int data;    //内容
 struct Node * pNext; //指向下一结点的指针
} NODE, * PNODE;   //NODE等价于struct Node, PNODE等价于struct Node *

typedef struct Stack
{
 PNODE pTop;    //栈顶结点
 PNODE pBottom;   //栈底结点
} STACK, * PSTACK;   //STACK等价于struct Stack, PSTACK等价于struct Stack *

int initStack(PSTACK pStack);    //对栈进行初始化的函数
int pushStack(PSTACK pStack, int val);  //入栈的函数
int popStack(PSTACK pStack, int * pVal);//出栈的函数，*pVal用来保存出栈的元素内容
void traverseStack(PSTACK pStack);   //遍历栈的函数
int isEmpty(PSTACK pStack);    //判断栈是否为空的函数
int clearStack(PSTACK pStack);   //清空栈的函数

int main(void)
{
 STACK stack;   //定义一个栈变量,STACK等价于struct Stack
 int val;    //用来保存出栈的内容
 initStack(&stack);  //调用栈的初始化函数
 pushStack(&stack, 10); //调用入栈的函数
 pushStack(&stack, 20);
 pushStack(&stack, 30);
 pushStack(&stack, 50);
 traverseStack(&stack); //调用遍历栈的函数
 
 if(popStack(&stack, &val))//调用出栈的函数
  printf("出栈成功，出栈的元素值为：%d\n", val);
 else
  printf(" 出栈失败!");

 if(popStack(&stack, &val))//调用出栈的函数
  printf("出栈成功，出栈的元素值为：%d\n", val);
 else
  printf(" 出栈失败!");
 
 clearStack(&stack);//调用清空栈的函数
 traverseStack(&stack); //调用遍历栈的函数
 system("pause");
 return 0;
}

int initStack(PSTACK pStack)
{
 
 pStack->pTop = (PNODE)malloc(sizeof(NODE));//创建一个空结点，让pTop指向它
 if(NULL != pStack->pTop)
 {
  pStack->pBottom = pStack->pTop; //将pBottom也指向空节点
  pStack->pTop->pNext = NULL;//清空空结点的指针域
 }
 else      //如果内存分配失败
 {
  printf("内存分配失败!程序退出!\n");
  exit(-1);
 }
 return OK;
}

int pushStack(PSTACK pStack, int val)
{
 PNODE pNew = (PNODE)malloc(sizeof(NODE));//动态创建一个新结点
 //设置新结点的数据域的值
 pNew->data = val;
 //将新结点的指针域指向之前建的空节点
 pNew->pNext = pStack->pTop;   //pStack->pTop不能换成pStack->pBottom
 pStack->pTop = pNew;//pTop指向新的结点
 return OK;
}

int popStack(PSTACK pStack, int * pVal)
{
 if(isEmpty(pStack))
 {
  return false;
 }
 else
 { 
  PNODE rNode = pStack->pTop;//先保存栈顶元素的地址，然后将pTop指向下一元素,最后释放之前栈顶元素的内存
  *pVal = rNode->data;
  pStack->pTop = rNode->pNext;
  free(rNode);
  rNode = NULL;
  return true;
 }
}

void traverseStack(PSTACK pStack)
{
 PNODE pNode = pStack->pTop;//将栈顶赋给一个临时结点,因为在遍历栈的时候不能销毁栈
 while(pStack->pBottom != pNode )//循环遍历栈,直到栈底
 {
  printf("%d  ", pNode->data);
  pNode = pNode->pNext;
 }
 printf("\n");
 return;
}

int isEmpty(PSTACK pStack)
{
 if(pStack->pTop == pStack->pBottom)
  return true;
 else
  return false;
}

int clearStack(PSTACK pStack)
{ //栈为空，则退出该函数
 if(isEmpty(pStack))
 {
  return ERROR;
 }
 else
 {  
  PNODE p = pStack->pTop;//两个结点指针变量用来释放栈中元素的内存
  PNODE q = NULL;  
  while(p != pStack->pBottom)//循环释放内存
  {
   q = p->pNext;
   free(p);
   p = q;
  } 
  pStack->pTop = pStack->pBottom;//将栈顶和栈底指向同一个指针域为空的结点
  return OK;
 }
}
