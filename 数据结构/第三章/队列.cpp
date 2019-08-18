#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef float QElemType;
typedef int Status; 
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//对头指针
	QueuePtr rear;//队尾指针 
}LinkQueue;
//函数声明
Status InitQueue(LinkQueue &Q); //初始化 
Status DestoryQueue(LinkQueue &Q);//销毁 
Status EnQueue(LinkQueue &Q,QElemType e);//插入 
Status DeQueue(LinkQueue &Q,QElemType &e);//删除 
Status Print(LinkQueue Q);//输出值 



Status InitQueue(LinkQueue &Q)
{
	//构造一个空队列 
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode)); 
	if(!Q.front)
	{
		exit(OVERFLOW);
	} 
	Q.front->next=NULL;
	return OK; 
} 
Status DestoryQueue(LinkQueue &Q)
{
	//销毁队列
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	} 
	return OK;
}
Status EnQueue(LinkQueue &Q,QElemType e)
{
	//插入元素e为Q的新的队尾元素
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode)); 
	if(!p)
	{
		exit(OVERFLOW);
	}
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;	 
}
Status DeQueue(LinkQueue &Q,QElemType &e)
{
	//若队列不空则删除Q的对头元素，用e返回其值并返回OK
	//否则返回ERROR
	QueuePtr p;
	if(Q.front==Q.rear)
	{
		return ERROR;
	} 
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
	{
		Q.rear=Q.front;
	}
	free(p);
	return OK;
} 
Status Print(LinkQueue Q)//输出值 
{
	QueuePtr q;
	q=Q.front;
	if(Q.front==Q.rear)
	{
		exit(OVERFLOW); 
	}
	while(q!=Q.rear)
	{
		printf("%4.2f ",q->next->data);
		q=q->next;
	}
	return OK;
}
int main(int argc, char** argv) 
{
	LinkQueue Q;
	Status i;
	QElemType e;
	 
	InitQueue(Q);
	for(i=0;i<5;i++)
	{
		scanf("%f",&e);
		EnQueue(Q,e);
	}
	Print(Q);
	printf("\n");
	printf("--------------------------\n");
	EnQueue(Q,2.32);
	Print(Q);
	DeQueue(Q,e);
	printf("\n删除的数为%f\n",e); 
	Print(Q);
	return 0;
}
