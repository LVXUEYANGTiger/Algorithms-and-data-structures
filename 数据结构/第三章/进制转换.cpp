#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define STACK_ININ_SIZE 100 //存储空间初始化分配量 
#define STACKINCREMENT 10 //存储空间分配增量 
#define OVERFLOW -1 
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct{
	Status *base;//在栈构造之前和销毁之后base的值为NULL 
	Status *top;//栈顶指针 
	Status stacksize;//当前的存储空间,以元素为单位 
}SqStack;

//函数声明
Status InitStack(SqStack &S);//构造一个空栈
Status GetTop(SqStack S,Status &e);//得到栈顶的一个元素 
Status Push(SqStack &S,Status e);//压入一个元素 
Status Pop(SqStack &S,Status &e);//删除一个元素 
Status StackEmpty(SqStack S);//判断是否为空栈 
Status InitStack(SqStack &S)
{
	//构造一个空栈
	S.base=(Status *)malloc(STACK_ININ_SIZE*sizeof(Status));
	if(S.base==NULL)
	{
		exit(OVERFLOW);
	} 
	S.top=S.base;
	S.stacksize=STACK_ININ_SIZE;
	return OK;
} 
Status GetTop(SqStack S,Status &e)
{
	//若栈不空则用e返回s的栈顶元素并返回OK否则返回ERROR
	if(S.top==S.base)
	{
		return ERROR;
	}
	e=*(S.top-1); 
	return OK; 
}
Status Push(SqStack &S,Status e)
{
	if(S.top-S.base>=S.stacksize)//栈满追加空间 
	{
		S.base=(Status *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(Status));
		if(S.base==NULL)//存储分配失败 
		{
			exit(OVERFLOW); 
		}
		S.top=S.base+S.stacksize;
		S.stacksize=S.stacksize+STACKINCREMENT;
	} 
	*S.top++=e;
	return OK;
}
Status Pop(SqStack &S,Status &e) 
{
	//若栈不空则删除S的栈顶元素用e返回其值并返回OK否则返回ERROR 
	if(S.top==S.base)
	{
		return ERROR;
	} 
	e=*--S.top;
	return OK;
}
Status StackEmpty(SqStack S)//判断是否为空栈 
{
	if(S.base==S.top)
	{
		return OK;//若为空栈则返回1 
	} 
	else
	{
		return ERROR;//若为不空栈则返回0
	}
} 
void conversion(SqStack &S)
{
	//对于输入的任何一个非负十进制数,打印输出与其等值的八进制数
	Status N,i,e;
	InitStack(S);
	
	printf("请输入一个非负十进制数:\n");
	scanf("%d",&N);
	printf("请输入需要转换的进制:\n");
	scanf("%d",&i);
	while(N)
	{
		Push(S,N%i);
		N=N/i;
	}
	while(!StackEmpty(S))
	{
		Pop(S,e);
		printf("%d",e);
	}
}
int main(int argc, char** argv) 
{
	SqStack S;
	printf("下面为进制转换的程序:\n");
	conversion(S);
	return 0;
}
