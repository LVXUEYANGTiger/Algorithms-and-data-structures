#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
typedef int Status;
typedef float ElemType;
typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;
//����������
Status Creat_DuL(DuLinkList &head);//����Ĵ���ע�⣺���� 
void Print_DuL(DuLinkList head);//����Ԫ�ص���� 
DuLinkList GetElem_DuL(DuLinkList L,Status i);//�õ�i��λ�� 
Status ListInsert_DuL(DuLinkList &head,Status i,ElemType e);//����

 
Status Creat_DuL(DuLinkList &head)//����Ĵ��� 
{
	DuLinkList p,q;
	Status i=0,j;
	head=(DuLinkList)malloc(sizeof(DuLNode));
	head->next=head->prior=NULL;
	p=head;
	printf("������ڵ���:\n"); 
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
void Print_DuL(DuLinkList head)//����Ԫ�ص���� 
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
	//�ڴ�ͷ����˫��ѭ�����е�i��λ��֮ǰ����Ԫ��e
	//i�ĺϷ�ֵΪ1<=i<=��+1
	DuLinkList p,s;
	if(!(p=GetElem_DuL(head,i)))//��L��ȷ������λ�� 
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
	//ɾ����ͷ����˫��ѭ�����Ա�ĵ�i��Ԫ��i�ĺϷ�ֵi<=i<=��
	if(!(p=GetElem_DuL(head,i)))//��L��ȷ����i��Ԫ�ص�λ��ָ��p 
	{
		return 0;//p=NULL����i��Ԫ�ز����� 
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
	 
	 
	//���Գ��򲻹淶���Լ�ȥ���� 
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
