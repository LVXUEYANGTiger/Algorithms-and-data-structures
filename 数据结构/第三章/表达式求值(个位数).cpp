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
Status In(char e)//�ж϶����ַ��Ƿ�Ϊ����� 
{
	if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
	    return OK;//�� 
	else 
	    return ERROR; //���� 
}
char Precede(char a,char b)//�Ƚ�����������ȼ� 
{
	char f;
	if(a=='+'||a=='-')
	{
		if(b=='+'||b=='-'||b==')'||b=='#')
		    f='>';
		else if(b=='*'||b=='/'||b=='(')
		    f='<';
	}
	else if(a=='*'||a=='/')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
		else if(b=='(')
		   f='<';
	}
	else if(a=='(')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b==')')
		   f='=';
	}
	else if(a==')')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
	}
	else if(a=='#')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b=='#')
		   f='=';
	}
	return f;
}
char Eva(char a,char theta,char b)//���� 
{
	char c;
	a=a-'0';
	b=b-'0';
	if(theta=='+')
	  c=a+b+'0';
	else if(theta=='-')
	  c=a-b+'0';
	else if(theta=='*')
	  c=a*b+'0';
	else if(theta=='/')
	  c=a/b+'0';	  
	return c; 
}
Status EvaluateExpression()
{
	SqStack OPND,OPTR;
	char ch,a,b,theta,x;
	InitStack(OPND);//������ջ�������� 
	InitStack(OPTR);//�����ջ 
	Push(OPTR,'#');
	ch=getchar();
	while(ch!='#'||GetTop(OPTR)!='#')
	{
		if(!In(ch))       //���Ϊ���� 
		{
			Push(OPND,ch);
			ch=getchar();
		}
		else             //����������� 
		{
			switch(Precede(GetTop(OPTR),ch))
			{
				case '<':                    //�����ַ����ȼ��� 
					Push(OPTR,ch);
				    ch=getchar();
					break;
				case '>':                    //�����ַ����ȼ��� 
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					Push(OPND,Eva(a,theta,b));
					break;
				case '=':                    //���ȼ���ͬ 
					Pop(OPTR,x);
				    ch=getchar();
					break;
			}
		} 
	}
	return GetTop(OPND)-'0';
}
int main()
{
	printf("�������������ʽ,����#����\n");
	printf("�����: %d\n",EvaluateExpression());
	return 0;

} 
