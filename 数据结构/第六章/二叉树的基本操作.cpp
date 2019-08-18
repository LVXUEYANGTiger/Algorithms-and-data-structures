#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100//存储空间初始分配量 
#define STACKINCREMENT 10//当前已分配的存储空间，以元素为单位
#define OVERFLOW -1
#define OK 1
#define ERROR 0
typedef char TElemType;
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;//左右孩子指针 
}BiTNode,*BiTree; 
typedef BiTree SElemType; 
typedef int Status;
typedef struct{
	SElemType *base;//在栈构造和销毁之后base的值为NULL 
	SElemType *top;//栈顶指针
	Status stacksize;//当前已分配的存储空间，以元素为单位 
}SqStack;

//函数声明
Status InitStack(SqStack &S);
Status GetTop(SqStack S,SElemType &e);
Status Push(SqStack &S,SElemType e); 
Status StackSize(SqStack S);
Status Pop(SqStack &S,SElemType &e);
Status StackEmpty(SqStack S);

//---------------------------------------------------------二叉树的链式存储--------------------------------------------------------------------------------------


//----------------------------------------------------------栈的构造完成--------------------------------------------------------------------------------------
Status InitStack(SqStack &S)
{
	//构造一个空栈
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(S.base==NULL)
	{
		exit(OVERFLOW);//存储失败 
	}
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK; 
} 
Status GetTop(SqStack S,SElemType &e)
{
	if(S.base==S.top)
	{
		return ERROR;
	}
	e=*(S.top-1);
	return OK;
}
Status Push(SqStack &S,SElemType e)
{
	//插入元素e为新的栈顶元素
	if(S.top-S.base>=S.stacksize)
	{
		//栈满追加存储空间
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		{
			exit(OVERFLOW);//存储分配失败 
		}
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	} 
	*S.top++=e;
	return 	OK;
}
Status StackSize(SqStack S)
{
	return S.top-S.base;
}
Status Pop(SqStack &S,SElemType &e)
{
	//若栈不空则删除S的栈顶元素，用e返回其值并返回OK否则则返回ERROR
	if(S.top==S.base)
	{
		return ERROR;
	} 
	e=*(--S.top);
	return OK;
}
Status StackEmpty(SqStack S)
{
	//判断栈是否为空如果是空则返回1否则返回0
	if(S.base==S.top)
	{
		return OK;
	}
	else
	{
		return ERROR;	
	} 

}
//-------------------------------------------------------------树的操作----------------------------------------------------------------------------------------
Status CreateBiTree(BiTree &T)
{
	//按先序次序输入二叉树中节点的值(一个字符)#字符表示空树
	//构造二叉链表表示的二叉树T
	TElemType ch;
	scanf("%c",&ch);
	if(ch=='#')
	{
		T=NULL;
	} 
	else
	{
		if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
		{
			exit(OVERFLOW);
		}
		T->data=ch;//生成根节点 
		CreateBiTree(T->lchild);//构造左子树 
		CreateBiTree(T->rchild);//构造右子树 
	}
	return OK;
}
Status Visit(TElemType e)
{
	printf("%c",e);
	return OK;
} 
//--------------------------------------------------------------------------前中后序遍历的递归----------------------------------------------------------------------------
Status PreOrderTraverse(BiTree T,Status (*Visit)(TElemType e))
{
	//采用二叉链表存储结构Visit 是对数据元素操作的应用函数
	//先序遍历二叉树T的递归算法，对每一个数据元素调用函数Visit
	//最简单的Visit函数是 
	//	Status PrintElement(TElemType e)
	//	{
	//		printf("%c",e);
	//		return OK;
	//	}
	if(T)
	{
	
		if(Visit(T->data))
		{
			if(PreOrderTraverse(T->lchild,Visit))
			if(PreOrderTraverse(T->rchild,Visit))
			return OK;
		}
		return ERROR;
		
	}
	else
	{
		return OK;
	}
}
Status InOrderTraverse(BiTree T,Status (*Visit)(TElemType e))
{
	//采用二叉链表存储结构Visit 是对数据元素操作的应用函数
	//中序遍历二叉树T的递归算法，对每一个数据元素调用函数Visit
	//最简单的Visit函数是 
	//	Status PrintElement(TElemType e)
	//	{
	//		printf("%c",e);
	//		return OK;
	//	}
	if(T)
	{
	
		if(InOrderTraverse(T->lchild,Visit))
		{
			if(Visit(T->data))
			if(InOrderTraverse(T->rchild,Visit))
			return OK;
		}
		return ERROR;
		
	}
	else
	{
		return OK;
	}
}
Status EpOrderTraverse(BiTree T,Status (*Visit)(TElemType e)) 
{
	//采用二叉链表存储结构Visit 是对数据元素操作的应用函数
	//后序遍历二叉树T的递归算法，对每一个数据元素调用函数Visit
	//最简单的Visit函数是 
	//	Status PrintElement(TElemType e)
	//	{
	//		printf("%c",e);
	//		return OK;
	//	}
	if(T)
	{
	
		if(EpOrderTraverse(T->lchild,Visit))
		{
			
			if(EpOrderTraverse(T->rchild,Visit))
			if(Visit(T->data))
			return OK;
		}
		return ERROR;
		
	}
	else
	{
		return OK;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------中序遍历的非递归算法----------------------------------------------------------------
Status InOrderTraverse1(BiTree T,Status (*Visit)(TElemType e))
{
	//采用二叉链表存储结构Visit是对数据元素操作的基本应用函数
	//中序遍历二叉树的非递归算法对每个数据元素都调用函数Visit
	SqStack S;
	BiTree p;
	
	InitStack(S);
	Push(S,T);
	
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p)
		{
			Push(S,p->lchild);//向左走向尽头 
		}
		Pop(S,p);//空指针退栈
		if(!StackEmpty(S))//访问节点向右一步 
		{
			Pop(S,p);
			if(!Visit(p->data))
			{
				return ERROR;
			}
			Push(S,p->rchild); 
		} 
	} 
} 
Status InOrderTraverse2(BiTree T,Status (*Visit)(TElemType e))
{
	
	BiTree p;
	SqStack S;
	
	InitStack(S);
	p=T;
	
	while(p||!StackEmpty(S))
	{
		if(p)
		{
			Push(S,p);
			p=p->lchild;//根指针进栈遍历左子树 
		}
		else//根指针退栈访问根节点遍历右子树 
		{
			Pop(S,p);
			if(!Visit(p->data))
			{
				return ERROR;
			} 
			p=p->rchild;
		}
	}
	return OK;
}
Status PreOrderTraverse2(BiTree T,Status (*Visit)(TElemType e))//前序非递归遍历第一种方法
{	
	SqStack S;	
	InitStack(S);	
	BiTree p = T;	
	while (p || !StackEmpty(S))	
	{		
		if (p) 
		{			
			Push(S, p);			
			Visit(p->data);			
			p = p->lchild;		
		}		
		else		
		{			
			Pop(S, p);			
			p = p->rchild;		
		}	
	}	
		
	return OK;
}
Status FindTreeDeep(BiTree T)
{
	Status deep=0;
	Status lchilddeep,rchilddeep;
	
	if(T==NULL)
	{
		return ERROR;
	}
	if(T)
	{
		lchilddeep=FindTreeDeep(T->lchild);
		rchilddeep=FindTreeDeep(T->rchild);
		
		deep=lchilddeep>=rchilddeep?lchilddeep+1:rchilddeep+1;
	}
	return deep;
} 
Status SizeTree(BiTree T)
{

	if(T == NULL)
	{
		return 0;
	} 

	if(T->lchild == NULL && T->rchild == NULL)
	{
		return 1;
	} 

	return SizeTree(T->lchild)+SizeTree(T->rchild)+1;

} 
void PrintTree(BiTree T)
{
	if(T)
	{
		 
		printf("%c",T->data);
		if(T->lchild!=NULL || T->rchild!=NULL)
		{
			printf("(");
			PrintTree(T->lchild);
			if(T->lchild!=NULL && T->rchild!=NULL)
				printf(",");
			PrintTree(T->rchild);
			printf(")");
		}
	}
	
}
int main(int argc, char** argv) 
{
	BiTree T;
	
	CreateBiTree(T);
	printf("递归前序遍历:\n");
	PreOrderTraverse(T,Visit);
	printf("\n");

	printf("递归中序遍历:\n"); 
	InOrderTraverse(T,Visit);
	printf("\n");
	printf("递归后序遍历:\n"); 
	EpOrderTraverse(T,Visit);
	printf("\n");
	printf("非递归前序遍历1:\n");
	PreOrderTraverse2(T,Visit);
	printf("\n");
	printf("非递归中序遍历1:\n"); 
	InOrderTraverse1(T,Visit);
	printf("\n");
	printf("非递归中序遍历2:\n");
	InOrderTraverse2(T,Visit);
	printf("\n");
	printf("二叉树的高度为：%d",FindTreeDeep(T));
	printf("\n");
	printf("二叉树的节点数为:%d\n",SizeTree(T));
	printf("("); 
	printf("按照广义表输出:\n");
	printf("("); 
	PrintTree(T);
	printf(")");
	return 0;
}
