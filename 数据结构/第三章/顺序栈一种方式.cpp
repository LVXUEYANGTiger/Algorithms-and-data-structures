#include <iostream>
#include <stdlib.h> 
#define STACK_INIT_SIZE 100//�洢�ռ��ʼ������
#define STACKINCREMENT 10//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
#define OVERFLOW -1
#define OK 1
#define ERROR 0
typedef int Status;
typedef float SElemType;
typedef struct{
	SElemType *base;//��ջ���������֮��base��ֵΪNULL 
	SElemType *top;//ջ��ָ�� 
	Status stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}SqStack; 
//��������
Status InitStack(SqStack &S);//�����ջ 
Status GetTop(SqStack S,SElemType &e);//�õ�ջ����һ��Ԫ�� 
Status Push(SqStack &S,SElemType e);//����һ��Ԫ�� 
Status Pop(SqStack &S,SElemType &e);//ɾ��һ��Ԫ�� 
Status StackTraverse(SqStack S,Status(*visit)(SElemType));//����ջ 

Status InitStack(SqStack &S)//�����ջ 
{
	//����һ����ջs
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType)); 
	if(S.base==NULL)
	{
		exit(OVERFLOW); //�洢ʧ�� 
	}
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
} 
Status GetTop(SqStack S,SElemType &e)
{
	//��ջ���գ�����e����s��ջ��Ԫ�أ�������ok���򷵻�ERROR
	if(S.top==S.base)
	{
		return ERROR;
	} 
	e=*(S.top-1);
	return OK;
} 
Status Push(SqStack &S,SElemType e)
{
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if(S.top-S.base>=S.stacksize)
	{
		//ջ��׷�Ӵ洢�ռ�
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		{
			exit(OVERFLOW);//�洢����ʧ�� 
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
	//��ջ������ɾ��S��ջ��Ԫ�أ���e������ֵ������OK���򷵻�ERROR
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
	printf("������ջ�е�Ԫ��:\n");
	scanf("%d",&j);
	while(j--)
	{
		scanf("%f",&e);
		Push(S,e);
	}
	printf("ջ��Ԫ�ظ���Ϊ:%d\n",StackSize(S));

	GetTop(S,e);
	printf("ջ��Ԫ��Ϊ%f",e);
	printf("\n");
	printf("--------------------------------------\n");
	Push(S,10.5);
	GetTop(S,e);
	printf("ջ��Ԫ��Ϊ%f",e);
	printf("\n");
	printf("--------------------------------------\n");
	Pop(S,e);
	printf("ɾ����Ԫ��Ϊ%f",e);
	printf("\n");
	printf("--------------------------------------\n");
	
	return 0;
}
