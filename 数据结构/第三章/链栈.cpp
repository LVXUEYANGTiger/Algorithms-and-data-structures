#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#define TRUE 1
#define FALSE 0 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1 
typedef float SElemType;
typedef int Status;
//结点结构 
typedef struct StackNode{
	SElemType data;
	struct StackNode *next;
}StackNode;
//链栈结构
typedef struct LinkStack{
	struct StackNode *top;
	Status count;
}LinkStack; 
//函数声明
 
//初始化链栈
Status InitStack(LinkStack *S)
{
	S->top=NULL;
	S->count=0;
	return OK; 
}
//销毁
Status DestroyStack(LinkStack *S)
{
	StackNode *p=S->top;
	for(S->count;S->count>0;S->count--)
	{
		S->top=p->next;
		free(p);
		p=S->top; 
	}
	S->count=0;
	return OK;
} 
//置空
Status ClearStack(LinkStack *S)
{
	S->top=NULL;
	S->count=0;
	return OK;
} 
//判空
Status StackEmpty(LinkStack S)
{
	if(!S.count)
	{
		return TRUE;
	}
	else
	{
		return ERROR;
	}
}
//取栈顶元素
Status GetTop(LinkStack S,SElemType *e)
{
	if(!S.count)
	{
		return ERROR;
	}
	*e=S.top->data;
	return OK;
} 
//入栈
Status Push(LinkStack *S,SElemType e)
{
	StackNode *p=(StackNode *)malloc(sizeof(StackNode));
	p->data=e;
	p->next=S->top;
	S->top=p;
	S->count++;
	return OK;
} 
//出栈
Status Pop(LinkStack *S,SElemType *e)
{
	if(!S->count)
	{
		return ERROR;
	}
	StackNode *p=S->top;
	*e=S->top->data;
	S->top=p->next;
	S->count--;
	return OK;
} 
//遍历
Status StackTraverse(LinkStack S)
{
	while(S.top)
	{
		printf("%f ",S.top->data);
		S.top=S.top->next;
	}
	printf("\n");
	return OK;
} 
int main(int argc, char** argv) 
{
	LinkStack S;
	SElemType e,y;
	Status num=0,i;
	
	InitStack(&S);
	
	printf("请输入你想要的元素个数：\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		scanf("%f",&e);
		Push(&S,e);
	}
	printf("因为为头插法所以为输出为\n");
	StackTraverse(S);
	GetTop(S,&e);
	printf("\n");
	printf("这个元素为%f \n",e);
	printf("在栈中插入一个元素:\n");
	scanf("%f",&e);
	Push(&S,e);
	StackTraverse(S);
	printf("删除栈顶元素：\n");
	Pop(&S,&e);
	printf("删除元素为：%f\n",e); 
	printf("将栈置空:\n");
	ClearStack(&S);
	printf("判断是否为空(1为空0为不空)%d \n",StackEmpty(S));
	printf("销毁栈销毁为(1):%d\n",DestroyStack(&S));
	return 0;
}
