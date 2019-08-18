#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef char HString;
typedef int Status; 
typedef struct{
	char *ch;//若是非空串则按串长分配存储区否则ch为NULL
	Status length;//串长度 
}HStrings;
//函数声明



Status StrAssign(HStrings &T,HString *chars)
{
	Status i,j=0;
	HString *c;
	//生成一个其值等于串常量chars的串T
	if(T.ch)
	{
		free(T.ch);//释放T原有的空间 
	} 
	for(i=0,c=chars;*c;++i,++c)
	{
		if(!i)
		{
			T.ch=NULL;
			T.length=0;
		}
		else
		{
			if(!(T.ch=(char*)malloc(sizeof(char)*i)))
			{
				exit(OVERFLOW);
			}
			for(j=0;j<=i;j++)
			{
				T.ch[j]=chars[j];
			}
			T.length=i+1;
		}
	} 
	return 	OK;
}
Status StrLength(HStrings S)
{
	//返回S的元素个数成为串的长度 
	return S.length;
} 

Status StrCompare(HStrings S,HStrings T)
{
	//若S>T,则返回值>0若S=T则返回值=0若S<T则返回值<0
	Status i;
	for(i=0;i<S.length&&i<T.length;++i)
	{
		if(S.ch[i]!=T.ch[i])
		{
			return S.ch[i]-T.ch[i];
		}
	} 
	return S.length-T.length;
} 
Status ClearString(HStrings &S)
{
	//将S清空为空串
	if(S.ch)
	{
		free(S.ch);
		S.ch=NULL;
	} 
	S.length=0;
	return OK;
}
Status Concat(HStrings &T,HStrings S1,HStrings S2)
{
	Status i=0;
	//用T返回S1和S2连接而成的新串
	if(!T.ch)
	{
		free(T.ch);//释放旧空间 
	} 
	if(!(T.ch=(char*)malloc(sizeof(char)*(S1.length+S2.length))))
	{
		exit(OVERFLOW); 
	} 
	for(i=0;i<S1.length;i++)
	{
		T.ch[i]=S1.ch[i];
	}
	T.length=S1.length+S2.length;
	for(i=0;i<S2.length;i++)
	{
		T.ch[S1.length+i]=S2.ch[i];
	}
	return OK;
}
Status SubString(HStrings &Sub,HStrings S,Status pos,Status len)
{
	//用Sub返回串S的第POS个字符起长度为len的子串
	//其中 1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos+1
	Status i=0; 
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
	{
		return ERROR;
	} 
	if(Sub.ch)
	{
		free(Sub.ch);
	}
	if(!len)
	{
		Sub.ch=NULL;
		Sub.length=0;
	}
	else
	{
		Sub.ch=(char*)malloc(sizeof(len*sizeof(char)));
		for(i=0;i<len;i++)
		{
			Sub.ch[i]=S.ch[pos-1+i];
		}
		Sub.length=len;
	} 
	return OK;
}
void PrintStr(HStrings S)
{
	Status i=0;
	if(S.ch)
	{
		for(i=0;i<S.length;i++)
		{
			printf("%c",S.ch[i]);
		}
		printf("\n");
	}
	else
	{
		printf("该串是空串\n");
	}
}
void StrInsert(HStrings &S,Status pos,HStrings T)
{
	Status i;
	//在1<=pos<=Strlength(S)+1在串的第pos个字符之前插入串T
	if(pos<1||pos>S.length+1)
	{
		printf("插入位置不存在\n");
		exit(1);
	} 
	if(T.length)
	{
		if(!(S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char))))
		{
			printf("空间分配有误!\n");
			exit(-1); 
		}
		for(i=S.length-1;i>=pos-1;--i)
		{
			S.ch[i+T.length]=S.ch[i];
		}
		for(i=0;i<T.length;++i)
		{
			S.ch[i+pos-1]=T.ch[i];
		}
		S.length+=T.length;
	}
}

Status Index(HStrings S,HStrings T,int pos)
{
	//返回子串T在主串S中的第pos个字符之后的位置若不存在则函数值为0
	//其中T为非空
	int i,j;
	
	i=pos;
	j=0; 
	while(i<=StrLength(S)&&j<=StrLength(T))
	{
		if(S.ch[i]==T.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			i=i-j+1;
			j=0;
		}
	} 
	if(j<StrLength(T))
	{
		return i-StrLength(T);
	}
	else
	{
		return 0;
	}
}

int main(int argc, char** argv) 
{
	char a[256];
	char b[256];
	HStrings S1,S2,S3;
	
	S1.ch=NULL;
	S1.length=0;
	S2.ch=NULL;
	S2.length=0;
	S3.ch=NULL;
	S3.length=0; 
	
	printf("请输入s1和s2:\n");
	gets(a);
	gets(b);
	
	StrAssign(S1,a);
	StrAssign(S2,b);
	printf("输出S1和S2：\n");
	PrintStr(S1);
	PrintStr(S2);
	printf("比较S1和S2：%d",StrCompare(S1,S2));
	Concat(S3,S1,S2);
	printf("输出S3：\n");
	PrintStr(S3);
	printf("\n");
	SubString(S3,S1,2,2);
	PrintStr(S3);
	StrInsert(S3,1,S2);
	PrintStr(S3);
	return 0;
}
