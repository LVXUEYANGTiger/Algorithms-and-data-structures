#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_ININ_SIZE 100
#define STACKINCREMENT 10
typedef int  Status;
typedef struct          //定义顺序栈 
{
	char *base;//栈底 
	char *top;//栈顶 
	Status stacksize;
}SqStack;

//函数声明
 
Status InitStack(SqStack &S)//初始化 
{
	S.base=(char*)malloc(sizeof(char)*STACK_ININ_SIZE);
	if(!S.base) 
	exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_ININ_SIZE;
	return OK;
}
Status Push(SqStack &S,char e)//入栈 
{
	if(S.top-S.base==S.stacksize) return ERROR;//栈满 
	*S.top=e;  //元素e压入栈顶，栈顶指针加1; 
	S.top++;
	return OK;
 } 
Status Pop(SqStack &S,char &e)//出栈 
{
	if(S.top==S.base)  
	return ERROR;   //栈空 
	e=*--S.top; //栈顶指针减一，将栈顶元素赋给e;
	return OK;
}
char GetTop(SqStack S)//取栈顶元素 
{
	if(S.top!=S.base)//栈非空 
	return *(S.top-1);//返回栈顶元素的值，栈顶指针不变 
}
Status StackEmpty(SqStack S)//判断是否为空栈 
{
	if(S.base==S.top)
	{
		return OK;//若为空栈则返回1 
	} 
	else
	{
		return ERROR;//若为不空栈则返回0
	}
} 
Status ClearStack(SqStack &S)//清空栈 
{
	char e;
	while(!StackEmpty(S))
	{
		Pop(S,e);
	}
	return OK;
}
Status DestoryStack(SqStack &S)//销毁栈 
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
	
	
	//利用字符栈S，从终端接收一行并传送到调运过程的数据区
	InitStack(S); //构造空栈S
	
	ch=getchar();//从终端接收一个字符
	while(ch!=EOF)//EOF为全文结束符 
	{
		while(ch!=EOF&&ch!='\n')
		{
			switch(ch)
			{
				case'#':Pop(S,c);break;//仅当栈非空时退栈
				case'@':ClearStack(S);break;//重置S为空栈
				default:Push(S,ch);break;//有效字符进栈 
			}
			ch=getchar();//从终端接收下一个字符 
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
