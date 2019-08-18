#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define STACK_ININ_SIZE 100 //�洢�ռ��ʼ�������� 
#define STACKINCREMENT 10 //�洢�ռ�������� 
#define OVERFLOW -1 
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct{
	Status *base;//��ջ����֮ǰ������֮��base��ֵΪNULL 
	Status *top;//ջ��ָ�� 
	Status stacksize;//��ǰ�Ĵ洢�ռ�,��Ԫ��Ϊ��λ 
}SqStack;

//��������
Status InitStack(SqStack &S);//����һ����ջ
Status GetTop(SqStack S,Status &e);//�õ�ջ����һ��Ԫ�� 
Status Push(SqStack &S,Status e);//ѹ��һ��Ԫ�� 
Status Pop(SqStack &S,Status &e);//ɾ��һ��Ԫ�� 
Status StackEmpty(SqStack S);//�ж��Ƿ�Ϊ��ջ 
Status InitStack(SqStack &S)
{
	//����һ����ջ
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
	//��ջ��������e����s��ջ��Ԫ�ز�����OK���򷵻�ERROR
	if(S.top==S.base)
	{
		return ERROR;
	}
	e=*(S.top-1); 
	return OK; 
}
Status Push(SqStack &S,Status e)
{
	if(S.top-S.base>=S.stacksize)//ջ��׷�ӿռ� 
	{
		S.base=(Status *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(Status));
		if(S.base==NULL)//�洢����ʧ�� 
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
	//��ջ������ɾ��S��ջ��Ԫ����e������ֵ������OK���򷵻�ERROR 
	if(S.top==S.base)
	{
		return ERROR;
	} 
	e=*--S.top;
	return OK;
}
Status StackEmpty(SqStack S)//�ж��Ƿ�Ϊ��ջ 
{
	if(S.base==S.top)
	{
		return OK;//��Ϊ��ջ�򷵻�1 
	} 
	else
	{
		return ERROR;//��Ϊ����ջ�򷵻�0
	}
} 
void conversion(SqStack &S)
{
	//����������κ�һ���Ǹ�ʮ������,��ӡ��������ֵ�İ˽�����
	Status N,i,e;
	InitStack(S);
	
	printf("������һ���Ǹ�ʮ������:\n");
	scanf("%d",&N);
	printf("��������Ҫת���Ľ���:\n");
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
	printf("����Ϊ����ת���ĳ���:\n");
	conversion(S);
	return 0;
}
