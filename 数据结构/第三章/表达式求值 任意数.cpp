#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TURE 1
#define FLASE 0
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;
typedef int Status;

typedef struct {
	SElemType *base,*top;
	int stacksize;
}Sqstackchar;

typedef struct {
	double *base,*top;
	int stacksize;
}Sqstackdouble;

Status InitStackchar(Sqstackchar &S);
Status InitStackdouble(Sqstackdouble &S);
SElemType GetTopchar(Sqstackchar &S,SElemType c);
double GetTopdouble(Sqstackdouble &S,double c);
Status Pushchar(Sqstackchar &S,SElemType &ch);
Status Pushdouble(Sqstackdouble &S,double &ch);
Status Popchar(Sqstackchar &S,SElemType &ch);
Status Popdouble(Sqstackdouble &S,double &ch);
Status StackEmpty(Sqstackchar S);//判断是否为空 
Status Inn(SElemType c);//判断是否是运算符 
double Operate(double a,SElemType theta,double b);//对数进行运算符
SElemType Precede(SElemType ch1,SElemType ch2);//判断运算符的优先级 

int main(int argc, char** argv) {
	SElemType theta,ch,x,c;
	double a=0,b;
	double m;
	Sqstackchar OPTR;
	Sqstackdouble OPND;
	InitStackchar(OPTR);//初始化运算符栈 
	InitStackdouble(OPND);//初始化运算数栈 
	c='#';
	Pushchar(OPTR,c);
	printf("请输入一个带#结尾的表达式:");
	ch=getchar();
	
	while(ch!='#' || GetTopchar(OPTR,c)!='#')
	{
		if(!Inn(ch))//不是运算符则进栈 
		{
			while(!Inn(ch))
			{
				
				a=a*10+(ch-48);
				ch=getchar();	
			}
			Pushdouble(OPND,a);
			printf("入OPND栈 %lf\n",a);
		}
		else
		{
			switch(Precede(GetTopchar(OPTR,c),ch))  //通过比较接收的字符来进行运算
			{
				case'<':              //栈顶元素优先权低 
				Pushchar(OPTR,ch);
				printf("入OPTR栈 %c\n",ch);
				ch=getchar();
				break;
				
				case'>':               //退栈并将运算结果入栈 
				Popchar(OPTR,theta);
				Popdouble(OPND,b);
				Popdouble(OPND,a);
				printf("入OPND栈前%lf %lf\n",b,a);
				Pushdouble(OPND,m=Operate(a,theta,b));
				printf("运算后 %lf\n",m);
				break;
				
				case'=':                 //脱括号并接收下一个字符 
				Popchar(OPTR,x);
				ch=getchar();
				break;
			}
			a=0;
		}
	}
	printf("\n\n\n");
    printf("运算结果= %lf",GetTopdouble(OPND,c));
}

Status InitStackchar(Sqstackchar &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status InitStackdouble(Sqstackdouble &S)
{
	S.base=(double *)malloc(STACK_INIT_SIZE*sizeof(double));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

SElemType GetTopchar(Sqstackchar &S,SElemType c)
{
	if(S.top==S.base)
		return ERROR;
	c=*(S.top-1);
	return c;
}

double GetTopdouble(Sqstackdouble &S,double c)
{
	if(S.top==S.base)
		return ERROR;
	c=*(S.top-1);
	return c;
}

Status Pushchar(Sqstackchar &S,SElemType &ch)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*(S.top++)=ch;
	return OK;
}

Status Pushdouble(Sqstackdouble &S,double &ch)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(double *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(double));
		if(S.base==NULL)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*(S.top++)=ch;
	return OK;
}

Status Popchar(Sqstackchar &S,SElemType &ch)
{
	if(S.top==S.base)
		return ERROR;
	ch=*(--S.top);
	return OK; 
}

Status Popdouble(Sqstackdouble &S,double &ch)
{
	if(S.top==S.base)
		return ERROR;
	ch=*(--S.top);
	return OK; 
}


Status Inn(SElemType c)
{
	if(c=='+' || c=='-' ||c=='*' ||c=='/' || c=='#' || c=='(' ||c==')')
		return OK;
	else
		return ERROR;
}


double Operate(double a,SElemType theta,double b)
{
	double c;
	switch(theta)
	{
		case '+':c=a+b;
		break;
		case '-':c=a-b;
		break;
		case '*':c=a*b;
		break;
		case '/':c=a/b;
		break;
	}

	return c;
}

SElemType Precede(SElemType ch1,SElemType ch2)
{
	if(ch1=='+')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	else if(ch1=='-')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='*')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='/')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='(')
	{
		switch(ch2)
		{
			case '+':return '<';
			case '-':return '<';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '=';
		}
	}
	
	else if(ch1==')')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='#')
	{
		switch(ch2)
		{
			case '+':return '<';
			case '-':return '<';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case '#':return '=';
		}
	}
}
