#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define OK 1
#define ERROR 0
#define true 1
#define false 0

typedef struct Node
{
 int data;    //����
 struct Node * pNext; //ָ����һ����ָ��
} NODE, * PNODE;   //NODE�ȼ���struct Node, PNODE�ȼ���struct Node *

typedef struct Stack
{
 PNODE pTop;    //ջ�����
 PNODE pBottom;   //ջ�׽��
} STACK, * PSTACK;   //STACK�ȼ���struct Stack, PSTACK�ȼ���struct Stack *

int initStack(PSTACK pStack);    //��ջ���г�ʼ���ĺ���
int pushStack(PSTACK pStack, int val);  //��ջ�ĺ���
int popStack(PSTACK pStack, int * pVal);//��ջ�ĺ�����*pVal���������ջ��Ԫ������
void traverseStack(PSTACK pStack);   //����ջ�ĺ���
int isEmpty(PSTACK pStack);    //�ж�ջ�Ƿ�Ϊ�յĺ���
int clearStack(PSTACK pStack);   //���ջ�ĺ���

int main(void)
{
 STACK stack;   //����һ��ջ����,STACK�ȼ���struct Stack
 int val;    //���������ջ������
 initStack(&stack);  //����ջ�ĳ�ʼ������
 pushStack(&stack, 10); //������ջ�ĺ���
 pushStack(&stack, 20);
 pushStack(&stack, 30);
 pushStack(&stack, 50);
 traverseStack(&stack); //���ñ���ջ�ĺ���
 
 if(popStack(&stack, &val))//���ó�ջ�ĺ���
  printf("��ջ�ɹ�����ջ��Ԫ��ֵΪ��%d\n", val);
 else
  printf(" ��ջʧ��!");

 if(popStack(&stack, &val))//���ó�ջ�ĺ���
  printf("��ջ�ɹ�����ջ��Ԫ��ֵΪ��%d\n", val);
 else
  printf(" ��ջʧ��!");
 
 clearStack(&stack);//�������ջ�ĺ���
 traverseStack(&stack); //���ñ���ջ�ĺ���
 system("pause");
 return 0;
}

int initStack(PSTACK pStack)
{
 
 pStack->pTop = (PNODE)malloc(sizeof(NODE));//����һ���ս�㣬��pTopָ����
 if(NULL != pStack->pTop)
 {
  pStack->pBottom = pStack->pTop; //��pBottomҲָ��սڵ�
  pStack->pTop->pNext = NULL;//��տս���ָ����
 }
 else      //����ڴ����ʧ��
 {
  printf("�ڴ����ʧ��!�����˳�!\n");
  exit(-1);
 }
 return OK;
}

int pushStack(PSTACK pStack, int val)
{
 PNODE pNew = (PNODE)malloc(sizeof(NODE));//��̬����һ���½��
 //�����½����������ֵ
 pNew->data = val;
 //���½���ָ����ָ��֮ǰ���Ŀսڵ�
 pNew->pNext = pStack->pTop;   //pStack->pTop���ܻ���pStack->pBottom
 pStack->pTop = pNew;//pTopָ���µĽ��
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
  PNODE rNode = pStack->pTop;//�ȱ���ջ��Ԫ�صĵ�ַ��Ȼ��pTopָ����һԪ��,����ͷ�֮ǰջ��Ԫ�ص��ڴ�
  *pVal = rNode->data;
  pStack->pTop = rNode->pNext;
  free(rNode);
  rNode = NULL;
  return true;
 }
}

void traverseStack(PSTACK pStack)
{
 PNODE pNode = pStack->pTop;//��ջ������һ����ʱ���,��Ϊ�ڱ���ջ��ʱ��������ջ
 while(pStack->pBottom != pNode )//ѭ������ջ,ֱ��ջ��
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
{ //ջΪ�գ����˳��ú���
 if(isEmpty(pStack))
 {
  return ERROR;
 }
 else
 {  
  PNODE p = pStack->pTop;//�������ָ����������ͷ�ջ��Ԫ�ص��ڴ�
  PNODE q = NULL;  
  while(p != pStack->pBottom)//ѭ���ͷ��ڴ�
  {
   q = p->pNext;
   free(p);
   p = q;
  } 
  pStack->pTop = pStack->pBottom;//��ջ����ջ��ָ��ͬһ��ָ����Ϊ�յĽ��
  return OK;
 }
}