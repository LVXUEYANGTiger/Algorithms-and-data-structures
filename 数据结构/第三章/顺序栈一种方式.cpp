#include <iostream>
#include <stdlib.h> 
#define STACK_INIT_SIZE 100//存储空间初始分配量
#define STACKINCREMENT 10//当前已分配的存储空间，以元素为单位
#define OVERFLOW -1
#define OK 1
#define ERROR 0
typedef int Status;
typedef float SElemType;
typedef struct{
	SElemType *base;//在栈构造和销毁之后base的值为NULL 
	SElemType *top;//栈顶指针 
	Status stacksize;//当前已分配的存储空间，以元素为单位 
}SqStack; 
//函数声明
Status InitStack(SqStack &S);//构造空栈 
Status GetTop(SqStack S,SElemType &e);//得到栈顶的一个元素 
Status Push(SqStack &S,SElemType e);//插入一个元素 
Status Pop(SqStack &S,SElemType &e);//删除一个元素 
Status StackTraverse(SqStack S,Status(*visit)(SElemType));//遍历栈 

Status InitStack(SqStack &S)//构造空栈 
{
	//构造一个空栈s
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType)); 
	if(S.base==NULL)
	{
		exit(OVERFLOW); //存储失败 
	}
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
} 
Status GetTop(SqStack S,SElemType &e)
{
	//若栈不空，则用e返回s的栈顶元素，并返回ok否则返回ERROR
	if(S.top==S.base)
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
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		{
			exit(OVERFLOW);//存储分配失败 
		}
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT; 
	} 
	*S.top++=e;
	return OK;
} 
int StackSize(SqStack S)
{
	return S.top-S.base;
} 
Status Pop(SqStack &S,SElemType &e)
{
	//若栈不空则删除S的栈顶元素，用e返回其值并返回OK否则返回ERROR
	if(S.top==S.base)
	{
		return ERROR;
	} 
	e=*(--S.top);
	return OK; 
} 

int main(int argc, char** argv) 
{
	SqStack S;
	Status i=0,j,a;
	SElemType e;
	
	InitStack(S);
	printf("请输入栈中的元素:\n");
	scanf("%d",&j);
	while(j--)
	{
		scanf("%f",&e);
		Push(S,e);
	}
	printf("栈的元素个数为:%d\n",StackSize(S));

	GetTop(S,e);
	printf("栈顶元素为%f",e);
	printf("\n");
	printf("--------------------------------------\n");
	Push(S,10.5);
	GetTop(S,e);
	printf("栈顶元素为%f",e);
	printf("\n");
	printf("--------------------------------------\n");
	Pop(S,e);
	printf("删除的元素为%f",e);
	printf("\n");
	printf("--------------------------------------\n");
	
	return 0;
}
