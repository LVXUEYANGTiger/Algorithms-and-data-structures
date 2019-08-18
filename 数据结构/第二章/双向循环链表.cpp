#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
typedef int Status;
typedef float ElemType;
typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;
//函数的声明
Status Creat_DuL(DuLinkList &head);//链表的创建注意：引号 
void Print_DuL(DuLinkList head);//链表元素的输出 
DuLinkList GetElem_DuL(DuLinkList L,Status i);//得到i的位置 
Status ListInsert_DuL(DuLinkList &head,Status i,ElemType e);//插入

 
Status Creat_DuL(DuLinkList &head)//链表的创建 
{
	DuLinkList p,q;
	Status i=0,j;
	head=(DuLinkList)malloc(sizeof(DuLNode));
	head->next=head->prior=NULL;
	p=head;
	printf("请输入节点数:\n"); 
	scanf("%d",&j);
	for(i=0;i<j;i++)
	{
		q=(DuLinkList)malloc(sizeof(DuLNode));
		scanf("%f",&q->data);
		p->next=q;
		q->prior=p;
		p=q;
	}
	p->next=head;
	head->prior=p;

} 
void Print_DuL(DuLinkList head)//链表元素的输出 
{
	DuLinkList p;
	p=head->next;
	while(p!=head)
	{
		printf("%f ",p->data);
		p=p->next;
	}
}
Status ListInsert_DuL(DuLinkList &head,Status i,ElemType e)
{
	//在带头结点的双链循环表中第i个位置之前插入元素e
	//i的合法值为1<=i<=表长+1
	DuLinkList p,s;
	if(!(p=GetElem_DuL(head,i)))//在L中确定插入位置 
	{
		return 0; 
	}
	if(!(s=(DuLinkList)malloc(sizeof(DuLNode))))
	{
		return 0;
	} 
	s->data=e;
	s->prior=p->prior;
	p->prior->next=s;
	s->next=p;
	p->prior=s;
	return 0;
	
} 


DuLinkList GetElem_DuL(DuLinkList L,Status i)
{
	DuLinkList p;
	int j=0;
	p=L->next;
	while(p!=L && j<i-1)
	{
		p=p->next;
		j++;
	}
	if(p==p->next || j>i-1)
	{
		return 0;
	}
		
	
	return p;
}
Status ListDelete_DuL(DuLinkList &head,Status i,ElemType &e)
{
	DuLinkList p;
	//删除带头结点的双链循环线性表的第i给元素i的合法值i<=i<=表长
	if(!(p=GetElem_DuL(head,i)))//在L中确定第i个元素的位置指针p 
	{
		return 0;//p=NULL即第i个元素不存在 
	} 
	e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p);
	return 0; 
}
int main(int argc, char** argv) 
{
	DuLinkList head;
	ElemType e;
	 
	 
	//测试程序不规范请自己去调试 
	Creat_DuL(head);
	Print_DuL(head);
	printf("\n");
	printf("-----------------------------------\n");
	ListInsert_DuL(head,1,2.3);
	Print_DuL(head);
	printf("\n");
	printf("-----------------------------------\n");
	ListDelete_DuL(head,1,e);
	Print_DuL(head);
	return 0;
}
