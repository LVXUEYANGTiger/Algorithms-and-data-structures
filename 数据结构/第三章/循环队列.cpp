#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define MAXQSIZE 100 //�����г��� 
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef float QElemType;
typedef int Status;
typedef struct{
	QElemType *base;//��ʼ����̬����洢�ռ�
	Status front;//����ͷָ������в�Ϊ����ָ�����ͷԪ��
	Status rear;//βָ�������в���ָ���βԪ�ص���һ��λ�� 
}SqQueue;
//����������
Status InitQueue(SqQueue &Q);//��ʼ��
Status QueueLength(SqQueue Q);//����еĳ���
Status EnQueue(SqQueue &Q,QElemType e);//����Ԫ�� 
Status DeQueue(SqQueue &Q,QElemType &e);//ɾ��Ԫ��
Status DeQueue(SqQueue Q);//ѭ�����еı��� 

 
Status InitQueue(SqQueue &Q)
{
	//����һ���յĶ���
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
	//����Q��Ԫ�ظ����������еĳ���
	return (Q.rear-Q.front+MAXQSIZE )%MAXQSIZE; 
}
Status EnQueue(SqQueue &Q,QElemType e)
{
	//����Ԫ��eΪQ���µĶ�βԪ��
	if((Q.rear+1)%MAXQSIZE==Q.front) 
	{
		return ERROR;//���� 
	}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return OK; 
} 
Status DeQueue(SqQueue &Q,QElemType &e)
{
	//�����в��գ���ɾ��Q�Ķ�ͷԪ����e������ֵ������OK
	//���򷵻�ERROR
	if(Q.front==Q.rear)
	{
		return ERROR;
	} 
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
	return OK;
}
Status DeQueue(SqQueue Q)//ѭ�����еı��� 
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
	
	//���Գ���д�Ĵֲڡ� 
	InitQueue(Q);
	printf("����5������Ԫ��:\n");
	for(i=0;i<5;i++)
	{
		scanf("%f",&e); 
		EnQueue(Q,e);
	}
	printf("--------------\n");
	DeQueue(Q);
	e=QueueLength(Q);
	printf("���еĳ���Ϊ%d\n",int(e));
	EnQueue(Q,2.31);
	DeQueue(Q);
	DeQueue(Q,e);
	DeQueue(Q);
	printf("ɾ����Ԫ��Ϊ%f\n",e); 
	return 0;
}
