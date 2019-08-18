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
//函数声明


void InitStack(SeqStack *S)//初始化空栈 
{
	S->top=0;
} 
Status InitEmpty(SeqStack S)//判断是否为空栈 
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
Status GetTop(SeqStack S,ElemType *e)//得到栈顶的一个元素 
{
	if(S.stack<=0)
	{
		printf("栈已经空\n");
		return 0;
	}
	else
	{
		*e=S.stack[S.top-1];
		return 1; 
	}
}
Status PushStack(SeqStack *S,ElemType e) //在栈顶压入一个元素 
{
	if(S->top>=StackSize)
	{
		printf("栈已经满,不能将元素入栈");
		return 0;
	} 
	else
	{
		S->stack[S->top]=e;
		S->top++;
		return 1;
	} 
}
Status PopStack(SeqStack *S,ElemType *e)//出栈 
{
	if(S->top==0)
	{
		printf("栈中已经没有元素了!");
		return 0;
	}
	else
	{
		S->top--;
		*e=S->stack[S->top];
		return 1;
	}
}
Status StackLength(SeqStack S)//求栈的长度 
{
	return S.top; 
}
void ClearStack(SeqStack *S)//清空栈 
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
	printf("原来的数组元素为:\n");
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		printf("%4.2f  ",a[i]);
	}
	printf("\n");
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)//判断有几个元素 
	{
		if(PushStack(&S,a[i])==0)
		{
			printf("栈已满,不能进栈\n");
			return 0;
		} 
	}
	printf("出栈的顺序：\n");
	if(PopStack(&S,&e)==1)
	{
		printf("%f ",e);
	}
	if(PopStack(&S,&e)==1)
	{
		printf("%f \n",e);
	}
	printf("当前栈顶的元素为:\n");
	if(GetTop(S,&e)==0)
	{
		printf("栈已空");
		return 0;
	}
	else
	{
		printf("%f",e);
	}
	printf("将元素99.9入栈:\n");
	if(PushStack(&S,99.9)==0)
	{
		printf("栈已满不能入栈\n");
		return 0;
	} 
	printf("当前栈的长度为%d\n",StackLength(S));
	printf("栈的出栈顺序为\n");
	while (!InitEmpty(S))
	{
		PopStack(&S, &e);
		printf("%4.2f  ",e); 
	}
	return 0;
}
