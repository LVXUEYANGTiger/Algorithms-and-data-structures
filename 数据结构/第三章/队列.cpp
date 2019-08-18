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
	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ�� 
}LinkQueue;
//��������
Status InitQueue(LinkQueue &Q); //��ʼ�� 
Status DestoryQueue(LinkQueue &Q);//���� 
Status EnQueue(LinkQueue &Q,QElemType e);//���� 
Status DeQueue(LinkQueue &Q,QElemType &e);//ɾ�� 
Status Print(LinkQueue Q);//���ֵ 



Status InitQueue(LinkQueue &Q)
{
	//����һ���ն��� 
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
	//���ٶ���
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
	//����Ԫ��eΪQ���µĶ�βԪ��
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
	//�����в�����ɾ��Q�Ķ�ͷԪ�أ���e������ֵ������OK
	//���򷵻�ERROR
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
Status Print(LinkQueue Q)//���ֵ 
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
	printf("\nɾ������Ϊ%f\n",e); 
	Print(Q);
	return 0;
}
