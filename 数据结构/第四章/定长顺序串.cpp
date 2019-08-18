#include <iostream>
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#define ERROR 0
#define TRUE 1 
#define FALSE 0 
#define OK 1
#define MAXSTRLEN 255//用户可以在255以内定义最大串长 
typedef unsigned char SString[MAXSTRLEN+1];//0号元素存放串的长度 
typedef int Status; 
//函数声明
Status StrAssign(SString T,char *chars);// 生成串 
Status StrCopy(SString T,SString S);//复制 
Status StrEmpty(SString S);//判断是否为空串 
Status StrCompare(SString S,SString T);//比较 
Status StrLength(SString S);//求长度 
Status ClearString(SString S);//清空 
Status Concat(SString T,SString S1,SString S2);//连接 
Status SubString(SString Sub,SString S,Status pos,Status len);//取子串 
Status Index(SString S,SString T,Status pos);//定位串的位置 
void replace(SString &S,SString T,SString V);//取代串 
Status StrInser(SString S,Status pos,SString T);//插入串 
Status StrDelete(SString &S,Status pos,Status len);//删除串 
void StrPrint(SString T);//输出串 
 
Status StrAssign(SString T,char *chars)
{
	//生成一个其值等于chars的串T
	Status i;
	if(strlen(chars)>MAXSTRLEN)
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
Status StrCopy(SString T,SString S)
{
	//由串S复制得串T
	Status i;
	for(i=0;i<=S[0];i++)
	{
		T[i]=S[i];
	} 
	return OK;
}
Status StrEmpty(SString S)
{
	//若S为空串则返回TRUE否则返回FALSE
	if(S[0]==0)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}
Status StrCompare(SString S,SString T)
{
	//初始条件ST都存在
	//操作结果：若S>T则返回值>0若S=T则返回值=0若S<T则返回值<0
	Status i;
	for(i=1;i<=S[0]&&i<=T[0];i++)
	{
		if(S[i]!=T[i])
		{
			return S[i]-T[i];
		}
	} 
	return S[0]-T[0];
}
Status StrLength(SString S)
{
	//返回串的元素个数 
	return S[0];
}
Status ClearString(SString S)
{
	//将S清空为空串
	S[0]=0;//令串长为零
	return OK; 
}
Status Concat(SString T,SString S1,SString S2)
{
	//用T返回S1和S2的连接而成的新串若未截断则返回TRUE否则返回FALSE
	Status i=0;
	if(S1[0]+S2[0]<=MAXSTRLEN)
	{
		for(i=1;i<=S1[0];i++)
		{
			T[i]=S1[i];
		}
		for(i=1;i<=S2[0];i++)
		{
			T[i+S1[0]]=S2[i];
		}
		T[0]=S1[0]+S2[0];
		return TRUE;
	} 
	else if(S1[0]<MAXSTRLEN)//截断S2 
	{
		for(i=1;i<=S1[0];i++)
		{
			T[i]=S1[i];
		}
		for(i=1;i<=MAXSTRLEN-S1[0];i++)
		{
			T[S1[0]+i]=S2[i];
		} 
		T[0]=MAXSTRLEN;
		return FALSE;
	}
	else
	{
		for(i=1;i<=MAXSTRLEN;i++)
		{
			T[i]=S1[i];
		}
		T[0]=MAXSTRLEN;
		return FALSE;
	}
}
Status SubString(SString Sub,SString S,Status pos,Status len)
{
	//用Sub返回串S的第POS个字符起长度为len的子串
	Status i;
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
	{
		return ERROR;
	} 
	for(i=1;i<=len;i++)
	{
		Sub[i]=S[pos+i-1];
	}
	Sub[0]=len;
	return OK;
}
Status Index(SString S,SString T,Status pos)
{
	//返回子串T在主串S中第POS个字符之后的位置若不存在返回值为0 
	Status i,n,m;
	SString Sub;
	if(pos>0)
	{
		n=StrLength(S);
		m=StrLength(T);
		i=pos;
		while(i<n-m+1)
		{
			SubString(Sub,S,i,m);
			if(StrCompare(Sub,T)!=0)
			{
				++i;
			}
			else
			{
				return i;
			}
		}
	}
	return 0;
}

void replace(SString &S,SString T,SString V)
{
	Status n,m,pos,i;
	SString news,sub;
	
	
	n=StrLength(S);
	m=StrLength(T);
	pos=1;
	StrAssign(news,NULL);
	i=1;
	while(pos<=n-m+1&&i)
	{
		i=Index(S,T,pos);//在S中定位子串T的位置i
		if(i!=0)
		{
			SubString(sub,S,pos,i-pos);//取s中保留的子串
			Concat(news,news,sub); //连接 
			Concat(news,news,V);
			pos=i+m;//下一次定位的位置 
		} 
	}
	SubString(sub,S,pos,n-pos+1);
	Concat(S,news,sub); 
}
Status StrInser(SString S,Status pos,SString T)
{
	//z在串S的第POS个字符之前插入串T完全插入后返回TRUE 部分插入后返回ERROR
	Status i;
	if(pos<1||pos>S[0]+1)
	{
		return ERROR;
	} 
	if(S[0]+T[0]<=MAXSTRLEN)
	{
		//完全插入
		for(i=S[0];i>=pos;i--)
		{
			S[i+T[0]]=S[i];
		}
		for(i=pos;i<pos+T[0];i++)
		{
			S[i]=T[i-pos+1];
		} 
		S[0]=S[0]+T[0];
		return TRUE;
	}
	else
	{
		//部分插入
		for(i=MAXSTRLEN;i>=pos;i--)
		{
			S[i]=S[i-T[0]];
		} 
		for(i=pos;i<pos+T[0];i++)
		{
			S[i]=T[i-pos+1];
		}
		S[0]=MAXSTRLEN;
		return FALSE;
	}
}
Status StrDelete(SString &S,Status pos,Status len)
{
	//从S中第pos位置长度为len的子串
	Status i;
	if(pos<1||pos>S[0]-len+1||len<0)
	{
		return ERROR;
	} 
	for(i=pos+len;i<=S[0];i++)
	{
		S[i-len]=S[i];
	} 
	S[0]-=len;
	return OK;
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
int main(int argc, char** argv) 
{	
	//由于时间匆忙请自己测定 
	SString T,S,Sub,V;
	int i;
	char cmp,chars[MAXSTRLEN+1];
	
	printf("请输入串S:\n");
	gets(chars);
	StrAssign(S,chars);
	printf("生成的串S为:\n");
	StrPrint(S);
	
	printf("请输入串T:\n");
	gets(chars);
	StrAssign(T,chars);
	printf("生成的串为:\n");
	StrPrint(T);
	printf("请输入串V:\n");
	gets(chars);
	StrAssign(V,chars);
	StrPrint(V);
//	printf("复制串T\n");
//	StrCopy(T,S);
//	StrPrint(S); 
//	
//	printf("(空串为1不空为0)%d\n",StrEmpty(S));
//	printf("相同为1S>T为大于0S<T为小于0%d\n",StrCompare(S,T));
//	printf("串的长度为:%d",StrLength(S));
//	printf("连接串:\n");
//	Concat(Sub,S,T);
//	printf("生成的串为:\n");
//	StrPrint(Sub);
//	SubString(Sub,S,1,3);
//	StrPrint(Sub);
//	printf("字符位置%d\n",Index(Sub,S,1)); 
	replace(S,T,V);
//	StrInser(S,1,T);
//	StrDelete(T,1,2);
//	StrPrint(T);
	return 0;
}
