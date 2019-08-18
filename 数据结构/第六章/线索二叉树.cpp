#include <iostream>
#include <stdio.h>
#include <stdlib.h>
typedef int Status;
#define OVERFLOW -2
typedef char TElemType;
#define OK 1
#define ERROR 0 
typedef enum PointerTag{
	Link,Thread//Link==0指针Thread==1线索 
}PointerTag; 
typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;//左右孩子指针 
	PointerTag LTag,RTag;//左右标志 
}BiThrNode,*BiThrTree; 
//函数声明
Status CreatBiTree(BiThrTree &T); 
Status Visit(TElemType e);
Status InOrderThreading(BiThrTree &Thrt,BiThrTree &T);
void InThreading(BiThrTree &pre,BiThrTree &p);
Status InOrderTraverse_Thr(BiThrTree T,Status (*Visit)(TElemType e));
//初始化二叉树
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
		CreatBiTree(T->lchild);//构造左子树 
		CreatBiTree(T->rchild);//构造右子树 
	}
	return OK; 
} 
//遍历 
Status Visit(TElemType e)
{
	printf("%c",e);
	return OK;
}
void InThreading(BiThrTree &pre,BiThrTree &p)
{

	if(p)
	{
		InThreading(pre,p->lchild);//左子树线索化
		if(!p->lchild)//前驱线索 
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		else
		{
			p->LTag=Link;
		}
		if(!pre->rchild)//后驱线索 
		{
			pre->RTag=Thread;
			pre->rchild=p;
		} 
		else
		{
			pre->RTag=Link;
		}
		pre=p;//保持pre指向p的前驱 
		InThreading(pre,p->rchild);//右子树线索化 
	}
}
//中序线索化
Status InOrderThreading(BiThrTree &Thrt,BiThrTree &T)
{
	//中序遍历二叉树T,并将其中序线索化，Thrt指向头结点
	BiThrTree pre;
	
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
	{
		exit(OVERFLOW);
	} 
	Thrt->LTag=Link;//建立头结点 
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;//右指针回指
	
	if(!T)
	{
		Thrt->lchild=Thrt;//如果二叉树为空则左指针回指 
	}
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(pre,T); //中序遍历进行中序线索化 
		pre->rchild=Thrt;//最后一个结点线索化 
		pre->RTag=Thread;
		Thrt->rchild=pre; 
	} 
	return OK;
} 
Status InOrderTraverse_Thr(BiThrTree T,Status (*Visit)(TElemType e))
{
	//T指向头结点，头结点的左链lchild指向根
	//中序遍历二叉线索T的非递归算法对每个元素调用函数Visit
	BiThrTree p;
	p=T->lchild;//p指向根节点
	while(p!=T)//p指向根节点 
	{
		while(p->LTag==Link)
		{
			p=p->lchild;
		}
		if(!Visit(p->data))
		{
			return ERROR;//访问左子树为空的时候 
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
