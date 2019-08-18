#include <iostream>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define MAXBUFFER 10
#define OK 1
#define ERROR 0
typedef int Status;
typedef double ElemType;
typedef struct{
	ElemType *base;
	ElemType *top;
	Status stacksize;	
}SqStack;
Status InitStack(SqStack &S)
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(S.base==NULL)
	{
		exit(0);
	}
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
} 
Status Push(SqStack &S,ElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(ElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(ElemType));
		if(S.base==NULL)
		{
			exit(0);
		} 
		S.top=S.base+S.stacksize;
		S.stacksize=S.stacksize+STACKINCREMENT;
	}
	*(S.top)=e;
	S.top++;
	return OK;
}
Status Pop(SqStack &S,ElemType &e)
{
	if(S.top==S.base)
	{
		return ERROR;
	}
	e=*(--S.top);
} 
Status StackLen(SqStack S)
{
	return S.top-S.base;
} 
int main(int argc, char** argv) 
{
	SqStack S;
	char c;
	ElemType d,e;
	char str[MAXBUFFER];
	Status i=0;
	
	InitStack(S);
	printf("�������沨�����ʽ�������������,�����������֮���ÿո����,��$��Ϊ������־:\n");
	scanf("%c",&c);
	while(c!='$')
	{
		while(isdigit(c)||c=='.')//isdigit(c)�����ж��Ƿ�Ϊ0-9�������ַ� 
		{
			str[i++]=c;
			str[i]='\0';
			if(i>=10)
			{
				printf("error");
				return -1;
			} 
			scanf("%c",&c);
			if(c==' ')
			{
				d=atof(str);//atof(str)���ַ�strת��Ϊһ��˫���ȵ����� ����������
				Push(S,d); 
				i=0;
				break;
			}
		}
		switch(c)
		{
			case '+':
					Pop(S,e);
					Pop(S,d);
					Push(S,d+e);
					break;
			case '-':
					Pop(S,e);
					Pop(S,d);
					Push(S,d-e);
					break;
			case '*':
					Pop(S,e);
					Pop(S,d);
					Push(S,d*e);
					break;
			case '/':
					Pop(S,e);
					Pop(S,d);
					if(e!=0)
					{
							Push(S,d-e);
					}
					else
					{
						printf("0������Ϊ����\n");
						return -1;
					}
					break;
		}
		scanf("%c",&c);
	}
	Pop(S,d);
	printf("���յĽ��Ϊ%4.2f",d);
	return 0;
}
