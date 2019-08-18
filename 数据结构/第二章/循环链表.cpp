#include <iostream>
#include <stdio.h>
#include <stdlib.h>
typedef int Status;
typedef float ElemType;
typedef struct LXNode{
	ElemType data;
	struct LXNode * next;
}LXNode,*LXLinkList;
//����������
Status Creat_LX(LXLinkList &head);//����Ĵ��� 
void Print_LX(LXLinkList head);//����Ԫ�ص���� 
Status Insert_LX(LXLinkList head,Status n);//����Ĳ��� 
Status Delete_LX(LXLinkList head,Status n);//�����ɾ��
void Lunion(LXLinkList &La,LXLinkList &Lb);//������ĺϲ� 

Status Creat_LX(LXLinkList &head)//����Ĵ���
{
	LXLinkList p,q;
	head=(LXLinkList)malloc(sizeof(LXNode));
	p=head;
	
	Status i=0,j=0;
	printf("����������Ҫ��������Ԫ�صĸ���:\n");
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
void Print_LX(LXLinkList head)//����Ԫ�ص���� 
{
	LXLinkList p;
	p=head->next;
	while(p!=head)
	{
		printf("%f ",p->data);
		p=p->next;
	}
}
Status Insert_LX(LXLinkList head,Status n)//����Ĳ��� 
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
Status Delete_LX(LXLinkList head,Status n)//�����ɾ��
{
	LXLinkList p,q;
	Status i=1;
	p=head->next;
	while(p!=head&&i<n-1)
	{
		i++;
		p=p->next;
	}
	q=p->next;//ɾ��Ԫ�صĵ�ַ
	p->next=q->next;
	free(q); 
} 
void Lunion(LXLinkList &La,LXLinkList &Lb)//������ĺϲ� 
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
	
	//���Գ��򲻹淶 
	Creat_LX(head);//�������� 
	Print_LX(head);//��ʾ���� 
	printf("\n");
	printf("------------------------------\n");
	Insert_LX(head,1);//����Ԫ�صĲ��� 
	Print_LX(head);
	printf("\n");
	printf("------------------------------\n");
	Delete_LX(head,2);
	Print_LX(head);
	return 0;
}
