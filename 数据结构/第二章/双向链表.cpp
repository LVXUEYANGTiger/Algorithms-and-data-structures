#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
typedef float ElemType;
typedef int Status;
typedef struct SXLNode{
	ElemType data;
	struct SXLNode *prior,*next;
}SXLNode,*SXLinkList;
//����������
Status Creat_SX(SXLinkList &head);//˫������Ľ��� 
void Print_SX(SXLinkList head);//��ʾ����Ԫ�� 
Status Insert_SX(SXLinkList &head,Status n,ElemType e);//˫������Ĳ��� 
Status Delete_SX(SXLinkList &head,Status n);//˫�������ɾ�� 






Status Creat_SX(SXLinkList &head)//˫������Ľ��� 
{
	SXLinkList q,p;
	Status i=0,j;
	head=(SXLinkList)malloc(sizeof(SXLNode));
	head->next=NULL;
	head->prior=NULL;
	p=head;
	
	scanf("%d",&j);
	
	for(i=0;i<j;i++)
	{
		q=(SXLinkList)malloc(sizeof(SXLNode));
		scanf("%f",&q->data);
		q->next=NULL;
		p->next=q;
		q->prior=p;
		p=q;
		
	}
	
	return 0;	
}
void Print_SX(SXLinkList head)//��ʾ����Ԫ�� 
{
	SXLinkList q;
	q=head->next;
	
	while(q!=NULL)
	{
		printf("%4.2f ",q->data);
		q=q->next;
	} 
}
Status Insert_SX(SXLinkList &head,Status n,ElemType e)//˫������Ĳ��� 
{
	SXLinkList p,q;
	Status i=1;
	p=head;
	
	while(p!=NULL&&i<n)
	{
		i++;
		p=p->next;
	} 
	q=(SXLinkList)malloc(sizeof(SXLNode));
	q->data=e;
	p->next->prior=q;
	q->next=p->next;
	p->next=q;
	q->prior=p;
	return 0;
}
Status Delete_SX(SXLinkList &head,Status n)//˫�������ɾ�� 
{
	SXLinkList p,q;
	Status i=1;
	p=head;
	
	while(p->next!=NULL&&i<n-1)
	{
		i++;
		p=p->next;
	}
	q=p->next;
	q->next->prior=p;
	p->next=q->next;
	free(q);
} 


 
int main(int argc, char** argv) 
{
	SXLinkList head;
	ElemType e;
	
	//���Բ��淶���Լ�ȥ���Է��ִ������֪�� 
	Creat_SX(head);//�������� 
	Print_SX(head);//��ʾ����Ԫ�� 
	printf("\n");
	printf("----------------------------\n");
	Insert_SX(head,1,0.3);
	Print_SX(head);//��ʾ����Ԫ�� 
	printf("\n");
	printf("----------------------------\n");
	Delete_SX(head,1);
	Print_SX(head);//��ʾ����Ԫ�� 
	return 0;
}
