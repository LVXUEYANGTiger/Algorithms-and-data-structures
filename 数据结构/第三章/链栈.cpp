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
//���ṹ 
typedef struct StackNode{
	SElemType data;
	struct StackNode *next;
}StackNode;
//��ջ�ṹ
typedef struct LinkStack{
	struct StackNode *top;
	Status count;
}LinkStack; 
//��������
 
//��ʼ����ջ
Status InitStack(LinkStack *S)
{
	S->top=NULL;
	S->count=0;
	return OK; 
}
//����
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
//�ÿ�
Status ClearStack(LinkStack *S)
{
	S->top=NULL;
	S->count=0;
	return OK;
} 
//�п�
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
//ȡջ��Ԫ��
Status GetTop(LinkStack S,SElemType *e)
{
	if(!S.count)
	{
		return ERROR;
	}
	*e=S.top->data;
	return OK;
} 
//��ջ
Status Push(LinkStack *S,SElemType e)
{
	StackNode *p=(StackNode *)malloc(sizeof(StackNode));
	p->data=e;
	p->next=S->top;
	S->top=p;
	S->count++;
	return OK;
} 
//��ջ
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
//����
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
	
	printf("����������Ҫ��Ԫ�ظ�����\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		scanf("%f",&e);
		Push(&S,e);
	}
	printf("��ΪΪͷ�巨����Ϊ���Ϊ\n");
	StackTraverse(S);
	GetTop(S,&e);
	printf("\n");
	printf("���Ԫ��Ϊ%f \n",e);
	printf("��ջ�в���һ��Ԫ��:\n");
	scanf("%f",&e);
	Push(&S,e);
	StackTraverse(S);
	printf("ɾ��ջ��Ԫ�أ�\n");
	Pop(&S,&e);
	printf("ɾ��Ԫ��Ϊ��%f\n",e); 
	printf("��ջ�ÿ�:\n");
	ClearStack(&S);
	printf("�ж��Ƿ�Ϊ��(1Ϊ��0Ϊ����)%d \n",StackEmpty(S));
	printf("����ջ����Ϊ(1):%d\n",DestroyStack(&S));
	return 0;
}
