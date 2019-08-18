#include <iostream>
#include <stdio.h>
#include <stdlib.h>
typedef int Status;
typedef float ElemType;
typedef struct LXNode{
	ElemType data;
	struct LXNode * next;
}LXNode,*LXLinkList;
//函数的声明
Status Creat_LX(LXLinkList &head);//链表的创建 
void Print_LX(LXLinkList head);//链表元素的输出 
Status Insert_LX(LXLinkList head,Status n);//链表的插入 
Status Delete_LX(LXLinkList head,Status n);//链表的删除
void Lunion(LXLinkList &La,LXLinkList &Lb);//俩个表的合并 

Status Creat_LX(LXLinkList &head)//链表的创建
{
	LXLinkList p,q;
	head=(LXLinkList)malloc(sizeof(LXNode));
	p=head;
	
	Status i=0,j=0;
	printf("请输入你想要创建链表元素的个数:\n");
	scanf("%d",&j);
	for(i=0;i<j;i++)
	{
		q=(LXLinkList)malloc(sizeof(LXNode));
		scanf("%f",&q->data);
		p->next=q;
		p=q;
	}
	p->next=head;
}
void Print_LX(LXLinkList head)//链表元素的输出 
{
	LXLinkList p;
	p=head->next;
	while(p!=head)
	{
		printf("%f ",p->data);
		p=p->next;
	}
}
Status Insert_LX(LXLinkList head,Status n)//链表的插入 
{
	LXLinkList p,s;
	p=head;
	Status i=1;
	while(i<n)
	{
		i++;
		p=p->next;
	} 
	s=(LXLinkList)malloc(sizeof(LXNode));
	scanf("%f",&s->data);
	s->next=p->next;
	p->next=s;
	return 0;
} 
Status Delete_LX(LXLinkList head,Status n)//链表的删除
{
	LXLinkList p,q;
	Status i=1;
	p=head->next;
	while(p!=head&&i<n-1)
	{
		i++;
		p=p->next;
	}
	q=p->next;//删除元素的地址
	p->next=q->next;
	free(q); 
} 
void Lunion(LXLinkList &La,LXLinkList &Lb)//俩个表的合并 
{
	LXLinkList p,q;
	p=La->next; 
	q=Lb->next; 
	while(p!=La)
	{
		if(p->next==La)
		{
			break;	
		}
		p=p->next;
	}
	while(q!=Lb)
	{
		if(q->next==Lb)
		{
			break;
		}
		q=q->next;
	}
	p->next=Lb->next;
	q->next=La;	
}
int main(int argc, char** argv) 
{
	LXLinkList head;
	
	//测试程序不规范 
	Creat_LX(head);//创建链表 
	Print_LX(head);//显示链表 
	printf("\n");
	printf("------------------------------\n");
	Insert_LX(head,1);//链表元素的插入 
	Print_LX(head);
	printf("\n");
	printf("------------------------------\n");
	Delete_LX(head,2);
	Print_LX(head);
	return 0;
}
