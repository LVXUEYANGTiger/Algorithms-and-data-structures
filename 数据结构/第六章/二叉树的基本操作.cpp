#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100//�洢�ռ��ʼ������ 
#define STACKINCREMENT 10//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
#define OVERFLOW -1
#define OK 1
#define ERROR 0
typedef char TElemType;
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ�� 
}BiTNode,*BiTree; 
typedef BiTree SElemType; 
typedef int Status;
typedef struct{
	SElemType *base;//��ջ���������֮��base��ֵΪNULL 
	SElemType *top;//ջ��ָ��
	Status stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}SqStack;

//��������
Status InitStack(SqStack &S);
Status GetTop(SqStack S,SElemType &e);
Status Push(SqStack &S,SElemType e); 
Status StackSize(SqStack S);
Status Pop(SqStack &S,SElemType &e);
Status StackEmpty(SqStack S);

//---------------------------------------------------------����������ʽ�洢--------------------------------------------------------------------------------------


//----------------------------------------------------------ջ�Ĺ������--------------------------------------------------------------------------------------
Status InitStack(SqStack &S)
{
	//����һ����ջ
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(S.base==NULL)
	{
		exit(OVERFLOW);//�洢ʧ�� 
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
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if(S.top-S.base>=S.stacksize)
	{
		//ջ��׷�Ӵ洢�ռ�
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		{
			exit(OVERFLOW);//�洢����ʧ�� 
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
	//��ջ������ɾ��S��ջ��Ԫ�أ���e������ֵ������OK�����򷵻�ERROR
	if(S.top==S.base)
	{
		return ERROR;
	} 
	e=*(--S.top);
	return OK;
}
Status StackEmpty(SqStack S)
{
	//�ж�ջ�Ƿ�Ϊ������ǿ��򷵻�1���򷵻�0
	if(S.base==S.top)
	{
		return OK;
	}
	else
	{
		return ERROR;	
	} 

}
//-------------------------------------------------------------���Ĳ���----------------------------------------------------------------------------------------
Status CreateBiTree(BiTree &T)
{
	//�������������������нڵ��ֵ(һ���ַ�)#�ַ���ʾ����
	//������������ʾ�Ķ�����T
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
		T->data=ch;//���ɸ��ڵ� 
		CreateBiTree(T->lchild);//���������� 
		CreateBiTree(T->rchild);//���������� 
	}
	return OK;
}
Status Visit(TElemType e)
{
	printf("%c",e);
	return OK;
} 
//--------------------------------------------------------------------------ǰ�к�������ĵݹ�----------------------------------------------------------------------------
Status PreOrderTraverse(BiTree T,Status (*Visit)(TElemType e))
{
	//���ö�������洢�ṹVisit �Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿһ������Ԫ�ص��ú���Visit
	//��򵥵�Visit������ 
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
	//���ö�������洢�ṹVisit �Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿһ������Ԫ�ص��ú���Visit
	//��򵥵�Visit������ 
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
	//���ö�������洢�ṹVisit �Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿһ������Ԫ�ص��ú���Visit
	//��򵥵�Visit������ 
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
//--------------------------------------------------------------------------��������ķǵݹ��㷨----------------------------------------------------------------
Status InOrderTraverse1(BiTree T,Status (*Visit)(TElemType e))
{
	//���ö�������洢�ṹVisit�Ƕ�����Ԫ�ز����Ļ���Ӧ�ú���
	//��������������ķǵݹ��㷨��ÿ������Ԫ�ض����ú���Visit
	SqStack S;
	BiTree p;
	
	InitStack(S);
	Push(S,T);
	
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p)
		{
			Push(S,p->lchild);//��������ͷ 
		}
		Pop(S,p);//��ָ����ջ
		if(!StackEmpty(S))//���ʽڵ�����һ�� 
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
			p=p->lchild;//��ָ���ջ���������� 
		}
		else//��ָ����ջ���ʸ��ڵ���������� 
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
Status PreOrderTraverse2(BiTree T,Status (*Visit)(TElemType e))//ǰ��ǵݹ������һ�ַ���
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
	printf("�ݹ�ǰ�����:\n");
	PreOrderTraverse(T,Visit);
	printf("\n");

	printf("�ݹ��������:\n"); 
	InOrderTraverse(T,Visit);
	printf("\n");
	printf("�ݹ�������:\n"); 
	EpOrderTraverse(T,Visit);
	printf("\n");
	printf("�ǵݹ�ǰ�����1:\n");
	PreOrderTraverse2(T,Visit);
	printf("\n");
	printf("�ǵݹ��������1:\n"); 
	InOrderTraverse1(T,Visit);
	printf("\n");
	printf("�ǵݹ��������2:\n");
	InOrderTraverse2(T,Visit);
	printf("\n");
	printf("�������ĸ߶�Ϊ��%d",FindTreeDeep(T));
	printf("\n");
	printf("�������Ľڵ���Ϊ:%d\n",SizeTree(T));
	printf("("); 
	printf("���չ�������:\n");
	printf("("); 
	PrintTree(T);
	printf(")");
	return 0;
}
