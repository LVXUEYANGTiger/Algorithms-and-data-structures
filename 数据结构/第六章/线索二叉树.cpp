#include <iostream>
#include <stdio.h>
#include <stdlib.h>
typedef int Status;
#define OVERFLOW -2
typedef char TElemType;
#define OK 1
#define ERROR 0 
typedef enum PointerTag{
	Link,Thread//Link==0ָ��Thread==1���� 
}PointerTag; 
typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;//���Һ���ָ�� 
	PointerTag LTag,RTag;//���ұ�־ 
}BiThrNode,*BiThrTree; 
//��������
Status CreatBiTree(BiThrTree &T); 
Status Visit(TElemType e);
Status InOrderThreading(BiThrTree &Thrt,BiThrTree &T);
void InThreading(BiThrTree &pre,BiThrTree &p);
Status InOrderTraverse_Thr(BiThrTree T,Status (*Visit)(TElemType e));
//��ʼ��������
Status CreatBiTree(BiThrTree &T)
{
	TElemType ch;
	
	scanf("%c",&ch);
	if(ch=='#')
	{
		T=NULL;
	}
	else
	{
		if(!(T=(BiThrTree)malloc(sizeof(BiThrNode))))
		{
			exit(OVERFLOW);
		}
		T->data=ch;
		CreatBiTree(T->lchild);//���������� 
		CreatBiTree(T->rchild);//���������� 
	}
	return OK; 
} 
//���� 
Status Visit(TElemType e)
{
	printf("%c",e);
	return OK;
}
void InThreading(BiThrTree &pre,BiThrTree &p)
{

	if(p)
	{
		InThreading(pre,p->lchild);//������������
		if(!p->lchild)//ǰ������ 
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		else
		{
			p->LTag=Link;
		}
		if(!pre->rchild)//�������� 
		{
			pre->RTag=Thread;
			pre->rchild=p;
		} 
		else
		{
			pre->RTag=Link;
		}
		pre=p;//����preָ��p��ǰ�� 
		InThreading(pre,p->rchild);//������������ 
	}
}
//����������
Status InOrderThreading(BiThrTree &Thrt,BiThrTree &T)
{
	//�������������T,������������������Thrtָ��ͷ���
	BiThrTree pre;
	
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
	{
		exit(OVERFLOW);
	} 
	Thrt->LTag=Link;//����ͷ��� 
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;//��ָ���ָ
	
	if(!T)
	{
		Thrt->lchild=Thrt;//���������Ϊ������ָ���ָ 
	}
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(pre,T); //��������������������� 
		pre->rchild=Thrt;//���һ����������� 
		pre->RTag=Thread;
		Thrt->rchild=pre; 
	} 
	return OK;
} 
Status InOrderTraverse_Thr(BiThrTree T,Status (*Visit)(TElemType e))
{
	//Tָ��ͷ��㣬ͷ��������lchildָ���
	//���������������T�ķǵݹ��㷨��ÿ��Ԫ�ص��ú���Visit
	BiThrTree p;
	p=T->lchild;//pָ����ڵ�
	while(p!=T)//pָ����ڵ� 
	{
		while(p->LTag==Link)
		{
			p=p->lchild;
		}
		if(!Visit(p->data))
		{
			return ERROR;//����������Ϊ�յ�ʱ�� 
		}
		while(p->RTag==Thread&&p->rchild!=T)
		{
			p=p->rchild;
			Visit(p->data);
		} 
		p=p->rchild;
	}
	return OK; 
}
int main(int argc, char** argv) 
{
	BiThrTree T; 
	BiThrTree Thrt;
	CreatBiTree(T);
	InOrderThreading(Thrt,T);
	InOrderTraverse_Thr(Thrt,Visit);
	
	return 0;
}
