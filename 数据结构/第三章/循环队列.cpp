#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define MAXQSIZE 100 //最大队列长度 
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef float QElemType;
typedef int Status;
typedef struct{
	QElemType *base;//初始化动态分配存储空间
	Status front;//设置头指针如队列不为空则指向队列头元素
	Status rear;//尾指针若队列不空指向队尾元素的下一个位置 
}SqQueue;
//函数的声明
Status InitQueue(SqQueue &Q);//初始化
Status QueueLength(SqQueue Q);//求队列的长度
Status EnQueue(SqQueue &Q,QElemType e);//插入元素 
Status DeQueue(SqQueue &Q,QElemType &e);//删除元素
Status DeQueue(SqQueue Q);//循环队列的遍历 

 
Status InitQueue(SqQueue &Q)
{
	//构造一个空的队列
	Q.base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType)); 
	if(!Q.base)
	{
		exit(OVERFLOW);
	} 
	Q.front=Q.rear=0;
	return OK;
}
Status QueueLength(SqQueue Q)
{
	//返回Q的元素个数，即队列的长度
	return (Q.rear-Q.front+MAXQSIZE )%MAXQSIZE; 
}
Status EnQueue(SqQueue &Q,QElemType e)
{
	//插入元素e为Q的新的队尾元素
	if((Q.rear+1)%MAXQSIZE==Q.front) 
	{
		return ERROR;//队满 
	}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return OK; 
} 
Status DeQueue(SqQueue &Q,QElemType &e)
{
	//若队列不空，则删除Q的队头元素用e返回其值并返回OK
	//否则返回ERROR
	if(Q.front==Q.rear)
	{
		return ERROR;
	} 
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
	return OK;
}
Status DeQueue(SqQueue Q)//循环队列的遍历 
{
	SqQueue q; 
	if(Q.front==Q.rear)
	{
		return ERROR;
	} 
	while(Q.front!=Q.rear)
	{
		printf("%4.2f ",Q.base[Q.front]);
		Q.front=(Q.front+1)%MAXQSIZE;
	}
	printf("\n");
	return OK;
}
int main(int argc, char** argv) 
{
	SqQueue Q;
	Status i;
	QElemType e;
	
	//测试程序写的粗糙。 
	InitQueue(Q);
	printf("输入5个队列元素:\n");
	for(i=0;i<5;i++)
	{
		scanf("%f",&e); 
		EnQueue(Q,e);
	}
	printf("--------------\n");
	DeQueue(Q);
	e=QueueLength(Q);
	printf("队列的长度为%d\n",int(e));
	EnQueue(Q,2.31);
	DeQueue(Q);
	DeQueue(Q,e);
	DeQueue(Q);
	printf("删除的元素为%f\n",e); 
	return 0;
}
