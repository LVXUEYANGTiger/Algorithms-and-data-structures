#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_ININ_SIZE 100
#define STACKINCREMENT 10
typedef int  Status;
typedef struct          //����˳��ջ 
{
	char *base;//ջ�� 
	char *top;//ջ�� 
	Status stacksize;
}SqStack;

//��������
 
Status InitStack(SqStack &S)//��ʼ�� 
{
	S.base=(char*)malloc(sizeof(char)*STACK_ININ_SIZE);
	if(!S.base) 
	exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_ININ_SIZE;
	return OK;
}
Status Push(SqStack &S,char e)//��ջ 
{
	if(S.top-S.base==S.stacksize) return ERROR;//ջ�� 
	*S.top=e;  //Ԫ��eѹ��ջ����ջ��ָ���1; 
	S.top++;
	return OK;
 } 
Status Pop(SqStack &S,char &e)//��ջ 
{
	if(S.top==S.base)  
	return ERROR;   //ջ�� 
	e=*--S.top; //ջ��ָ���һ����ջ��Ԫ�ظ���e;
	return OK;
}
char GetTop(SqStack S)//ȡջ��Ԫ�� 
{
	if(S.top!=S.base)//ջ�ǿ� 
	return *(S.top-1);//����ջ��Ԫ�ص�ֵ��ջ��ָ�벻�� 
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
Status ClearStack(SqStack &S)//���ջ 
{
	char e;
	while(!StackEmpty(S))
	{
		Pop(S,e);
	}
	return OK;
}
Status DestoryStack(SqStack &S)//����ջ 
{
	ClearStack(S);
	S.stacksize=0;
	S.base=S.top=NULL;
	return OK;
}
Status Print(SqStack S)
{
	char *q,*p;
	q=S.base;
	p=--S.top;
	while(q!=p)
	{
		printf("%c",*q);
		q++;
	}
}
void LineEdit(SqStack &S)
{
	char ch,c;
	char a[1000];
	Status i=0;
	
	
	//�����ַ�ջS�����ն˽���һ�в����͵����˹��̵�������
	InitStack(S); //�����ջS
	
	ch=getchar();//���ն˽���һ���ַ�
	while(ch!=EOF)//EOFΪȫ�Ľ����� 
	{
		while(ch!=EOF&&ch!='\n')
		{
			switch(ch)
			{
				case'#':Pop(S,c);break;//����ջ�ǿ�ʱ��ջ
				case'@':ClearStack(S);break;//����SΪ��ջ
				default:Push(S,ch);break;//��Ч�ַ���ջ 
			}
			ch=getchar();//���ն˽�����һ���ַ� 
		}
		while(S.base!=S.top)
		{
			
			Pop(S,c);
			a[i++]=c;
		}
		for(;i>0;i--)
		{
			printf("%c",a[i-1]);
		}
		ch=getchar();
		
		
	}
	
} 
int main(int argc, char** argv) 
{
	SqStack S,SS;
	LineEdit(S);
	

	return 0;
}
