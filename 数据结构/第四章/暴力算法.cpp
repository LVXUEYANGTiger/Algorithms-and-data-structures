#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#define ERROR 0
#define OK 1
#define MAXSTRLEN 255//串的初始长度 
typedef char SString[MAXSTRLEN+1];//0号单元存放串的长度 
typedef int Status;
Status StrAssign(SString T,char *chars)
{
	//生成一个其值等于chars的串T
	Status i;
	if(strlen(T)>MAXSTRLEN)
	{
		return ERROR;
	} 
	else
	{
		T[0]=strlen(chars);
		for(i=1;i<=T[0];i++)
		{
			T[i]=*(chars+i-1);
		}
		return OK;
	}
} 
void StrPrint(SString T)
{
	//输出字符串T
	Status i;
	for(i=1;i<=T[0];i++)
	{
		printf("%c",T[i]);
	} 
	printf("\n");
}
Status Index(SString S,SString T,Status pos)//BF算法 
{
	//返回子串t在主串s中第pos个字符之后的位置若不存在则函数值为0
	//其中t为非空1<=pos<=Strlength（s） 
	Status i,j;
	i=pos;
	j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(S[i]==T[j])//继续比较后续指针 
		{
			++i;
			++j;
		}
		else
		{
			i=i-j+2;//指针后退重新开始匹配 
			j=1;
		}
	}
	if(j>T[0])
	{
		return i-T[0];
	} 
	else
	{
		return ERROR;
	}
	
} 
int main(int argc, char** argv) 
{
	char s[256],t[256];
	Status pos;
	SString S,T;
	printf("请输入字符串S：\n");
	gets(s);
	StrAssign(S,s);
	printf("输出字符串S：\n");
	StrPrint(S); 
	printf("请输入字符串T：\n"); 
	gets(t);
	StrAssign(T,t);
	printf("输出字符串T：\n");
	StrPrint(T);
	printf("请输入位置(第pos个字符之后):\n");
	scanf("%d",&pos);
	printf("模式串T在主串S的位置为%d\n",Index(S,T,pos));
	return 0;
}
