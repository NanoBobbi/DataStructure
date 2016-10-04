#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LIST_INIT_SIZE 100
#define LISINCREMENT 10
#define ElemType int
#define Status int
typedef struct Sq{
 ElemType *elem;
 int length;
 int listsize;
}SqList;
Status InitList(SqList *L)
{
 L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
 if(!L->elem)
  return 0;
 L->length=0;
 L->listsize=LIST_INIT_SIZE;
 return 1;
}
Status ListInsert(SqList *L,int i,ElemType e)
{
 int *q,*p;
 if(i<1||i>L->length)
  return 0;
 if(L->length>L->listsize)
 { 
        ElemType *newbase=(ElemType*)realloc(L->elem,(LIST_INIT_SIZE+LISINCREMENT)*sizeof(ElemType));
     if(!newbase)
      return 0;
     L->elem=newbase;
     L->listsize+=(LISINCREMENT);
 }																																																																																										

 q=&(L->elem[i-1]);
 for(p=&(L->elem[L->length-1]);p>=q;--p)
  *(p+1)=*p;
    *q=e;
 ++L->length;
 return 1;
}
Status ListDelete(SqList *L,int i,ElemType e)
{
 int *p,*q;
 if(i<1||i>L->length)
        return 0;
    p=&(L->elem[i-1]);
 e=*p;
 q=L->elem+L->length-1;
 for(++p;p<=q;++p)
  *(p-1)=*p;
 --L->length;
 return 1;
}
int main(void)
{
 int i,j,e,lo,temp;
 SqList *L=(SqList*)malloc(sizeof(SqList));
    InitList(L);
 printf("请输顺序表的长度:\n");
    scanf("%d",&L->length);
 printf("请输入顺序表的各个元素:\n");
 for(i=0;i<L->length;++i)
  scanf("%d",&L->elem[i]);
 printf("输入的顺序表是:\n");
    for (i=0;i<L->length;++i)
    {
  printf("%d ",L->elem[i]);
 }
 printf("\n");
    printf("请输入插入的位置以及节点:\n");
    scanf("%d%d",j,&e);
 ListInsert(L,j,e); 
 printf("插入后的顺序表为:\n");
 for (i=0;i<L->length;++i)
    {
  printf("%d ",L->elem[i]);
 }
 printf("\n");
 printf("请输入要删除的位置：");
 scanf("%d",&lo);
 ListDelete(L,lo,temp);
 for (i=0;i<L->length;++i)
    {
  printf("%d ",L->elem[i]);
 }
 printf("\n");
 free(L);
 return 0;
}
