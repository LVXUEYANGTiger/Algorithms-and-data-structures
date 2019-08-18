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
	char *ch;//���Ƿǿմ��򰴴�������洢������chΪNULL
	Status length;//������ 
}HStrings;
//��������



Status StrAssign(HStrings &T,HString *chars)
{
	Status i,j=0;
	HString *c;
	//����һ����ֵ���ڴ�����chars�Ĵ�T
	if(T.ch)
	{
		free(T.ch);//�ͷ�Tԭ�еĿռ� 
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
	//����S��Ԫ�ظ�����Ϊ���ĳ��� 
	return S.length;
} 

Status StrCompare(HStrings S,HStrings T)
{
	//��S>T,�򷵻�ֵ>0��S=T�򷵻�ֵ=0��S<T�򷵻�ֵ<0
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
	//��S���Ϊ�մ�
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
	//��T����S1��S2���Ӷ��ɵ��´�
	if(!T.ch)
	{
		free(T.ch);//�ͷžɿռ� 
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
	//��Sub���ش�S�ĵ�POS���ַ��𳤶�Ϊlen���Ӵ�
	//���� 1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos+1
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
		printf("�ô��ǿմ�\n");
	}
}
void StrInsert(HStrings &S,Status pos,HStrings T)
{
	Status i;
	//��1<=pos<=Strlength(S)+1�ڴ��ĵ�pos���ַ�֮ǰ���봮T
	if(pos<1||pos>S.length+1)
	{
		printf("����λ�ò�����\n");
		exit(1);
	} 
	if(T.length)
	{
		if(!(S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char))))
		{
			printf("�ռ��������!\n");
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
	//�����Ӵ�T������S�еĵ�pos���ַ�֮���λ��������������ֵΪ0
	//����TΪ�ǿ�
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
	
	printf("������s1��s2:\n");
	gets(a);
	gets(b);
	
	StrAssign(S1,a);
	StrAssign(S2,b);
	printf("���S1��S2��\n");
	PrintStr(S1);
	PrintStr(S2);
	printf("�Ƚ�S1��S2��%d",StrCompare(S1,S2));
	Concat(S3,S1,S2);
	printf("���S3��\n");
	PrintStr(S3);
	printf("\n");
	SubString(S3,S1,2,2);
	PrintStr(S3);
	StrInsert(S3,1,S2);
	PrintStr(S3);
	return 0;
}
