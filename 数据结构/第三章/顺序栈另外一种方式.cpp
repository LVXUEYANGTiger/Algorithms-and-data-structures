#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define StackSize 100
typedef float ElemType;
typedef int Status;
typedef struct{
	ElemType stack[StackSize];
	Status top; 
}SeqStack; 
//��������


void InitStack(SeqStack *S)//��ʼ����ջ 
{
	S->top=0;
} 
Status InitEmpty(SeqStack S)//�ж��Ƿ�Ϊ��ջ 
{
	if(S.top==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
} 
Status GetTop(SeqStack S,ElemType *e)//�õ�ջ����һ��Ԫ�� 
{
	if(S.stack<=0)
	{
		printf("ջ�Ѿ���\n");
		return 0;
	}
	else
	{
		*e=S.stack[S.top-1];
		return 1; 
	}
}
Status PushStack(SeqStack *S,ElemType e) //��ջ��ѹ��һ��Ԫ�� 
{
	if(S->top>=StackSize)
	{
		printf("ջ�Ѿ���,���ܽ�Ԫ����ջ");
		return 0;
	} 
	else
	{
		S->stack[S->top]=e;
		S->top++;
		return 1;
	} 
}
Status PopStack(SeqStack *S,ElemType *e)//��ջ 
{
	if(S->top==0)
	{
		printf("ջ���Ѿ�û��Ԫ����!");
		return 0;
	}
	else
	{
		S->top--;
		*e=S->stack[S->top];
		return 1;
	}
}
Status StackLength(SeqStack S)//��ջ�ĳ��� 
{
	return S.top; 
}
void ClearStack(SeqStack *S)//���ջ 
{
	S->top=0;
}
int main(int argc, char** argv) 
{
	SeqStack S; 
	Status i=0;
	ElemType a[5]={1.1,2.2,3.3,4.4,9.9};
	ElemType e;
	
	InitStack(&S);
	printf("ԭ��������Ԫ��Ϊ:\n");
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		printf("%4.2f  ",a[i]);
	}
	printf("\n");
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)//�ж��м���Ԫ�� 
	{
		if(PushStack(&S,a[i])==0)
		{
			printf("ջ����,���ܽ�ջ\n");
			return 0;
		} 
	}
	printf("��ջ��˳��\n");
	if(PopStack(&S,&e)==1)
	{
		printf("%f ",e);
	}
	if(PopStack(&S,&e)==1)
	{
		printf("%f \n",e);
	}
	printf("��ǰջ����Ԫ��Ϊ:\n");
	if(GetTop(S,&e)==0)
	{
		printf("ջ�ѿ�");
		return 0;
	}
	else
	{
		printf("%f",e);
	}
	printf("��Ԫ��99.9��ջ:\n");
	if(PushStack(&S,99.9)==0)
	{
		printf("ջ����������ջ\n");
		return 0;
	} 
	printf("��ǰջ�ĳ���Ϊ%d\n",StackLength(S));
	printf("ջ�ĳ�ջ˳��Ϊ\n");
	while (!InitEmpty(S))
	{
		PopStack(&S, &e);
		printf("%4.2f  ",e); 
	}
	return 0;
}
