#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef char SElemType;
typedef struct
{
    SElemType *base;
    SElemType *top;
    Status stacksize;
}SqStack;
typedef struct
{
    Status *base;
    Status *top;
    Status stacksize;
}sqStack;
Status InitStack(SqStack &S)
{
    S.base=(SElemType*)malloc(sizeof(SElemType)*MAXSIZE);
    if(!S.base)
    exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return OK;
}


Status initStack(sqStack &S)
{
    S.base=(Status*)malloc(sizeof(Status)*MAXSIZE);
    if(!S.base)
    exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return OK;
}
Status Push(SqStack &S,SElemType e)
{
    if(S.top-S.base==S.stacksize)
    return ERROR;
    *S.top++=e;
    return OK;
}
Status push(sqStack &S,Status e)
{
    if(S.top-S.base==S.stacksize)
    return ERROR;
    *S.top++=e;
    //printf("%daa\n",e);
    return OK;
}
Status Pop(SqStack &S,SElemType &e)
{
    if(S.top==S.base)
    return ERROR;
    e=*--S.top;
    return OK;
}
Status pop(sqStack &S,Status &e)
{
    if(S.top==S.base)
    return ERROR;
    e=*--S.top;
    return OK;
}
SElemType GetTop(SqStack S)
{
    if(S.top!=S.base)
    return *(S.top-1);
}
Status getTop(sqStack S)
{
    if(S.top!=S.base)//栈非空
    return *(S.top-1);//返回栈顶元素的值，栈顶指针不变
}
Status In(SElemType e)//判断读入字符是否为运算符
{
	if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}
SElemType Precede(SElemType a,SElemType b)//比较运算符的优先级
{
    int i=0,j=0;
	char c[][7]={
	{'>','>','<','<','<','>','>'}, 
	{'>','>','<','<','<','>','>'}, 
	{'>','>','>','>','<','>','>'}, 
	{'>','>','>','>','<','>','>'}, 
	{'<','<','<','<','<','=','0'},
	{'>','>','>','>','0','>','>'},
	{'<','<','<','<','<','0','='}
	}; 
	switch(a)
	{
		case '+': i=0; break; 
		case '-': i=1; break; 
		case '*': i=2; break; 
		case '/': i=3; break; 
		case '(': i=4; break; 
		case ')': i=5; break; 
		case '=': i=6; break; 	
	}
	switch(b)
	{
		case '+': j=0; break; 
		case '-': j=1; break; 
		case '*': j=2; break; 
		case '/': j=3; break; 
		case '(': j=4; break; 
		case ')': j=5; break; 
		case '=': j=6; break; 	
	}	
	return c[i][j];
}
Status Operate(Status a,SElemType theta,Status b)//运算
{
    Status c;
    if(theta=='+')
      c=a+b;
    else if(theta=='-')
      c=a-b;
    else if(theta=='*')
      c=a*b;
    else if(theta=='/')
    {
    	if(b==0) 
    	{
    	printf("0不能为除数!\n");
		}
     	 c=a/b;
	}
    
    return c;
}
int EvaluateExpression()
{
    int sum,a,b;
    SqStack OPTR;
    sqStack OPND;
    char ch,theta,x,c;
    initStack(OPND);//寄存操作数和运算结果
    InitStack(OPTR);//寄存运算符
    Push(OPTR,'#');
    ch=getchar();
    while(ch!='#'||GetTop(OPTR)!='#')
    {
        if(!In(ch))
        {
            c=ch;
            ch=getchar();
            if(!In(ch))
            {
                sum=(c-48)*10+ch-48;
                push(OPND,sum);
                ch=getchar();
            }
            else
            {
                sum=c-48;
                push(OPND,sum);
            }
        }
        else
        {
            switch(Precede(GetTop(OPTR),ch))
            {
                case '<':
                    Push(OPTR,ch);
                    ch=getchar();
                    break;
                case '>':
                    Pop(OPTR,theta);
                    pop(OPND,b);
                    pop(OPND,a);
                    push(OPND,Operate(a,theta,b));
                    break;
                case '=':
                    Pop(OPTR,x);
                    ch=getchar();
                    break;
            }
        }
    }
    return getTop(OPND);
}
int main(void)
{
    printf("输入表达式,#表示结束\n");
    printf("%d\n",EvaluateExpression());
    return 0;
}
