#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#define ERROR 0
#define OK 1
#define MAXSTRLEN 255//���ĳ�ʼ���� 
typedef char SString[MAXSTRLEN+1];//0�ŵ�Ԫ��Ŵ��ĳ��� 
typedef int Status;
Status StrAssign(SString T,char *chars)
{
	//����һ����ֵ����chars�Ĵ�T
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
	//����ַ���T
	Status i;
	for(i=1;i<=T[0];i++)
	{
		printf("%c",T[i]);
	} 
	printf("\n");
}
Status Index(SString S,SString T,Status pos)//BF�㷨 
{
	//�����Ӵ�t������s�е�pos���ַ�֮���λ��������������ֵΪ0
	//����tΪ�ǿ�1<=pos<=Strlength��s�� 
	Status i,j;
	i=pos;
	j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(S[i]==T[j])//�����ȽϺ���ָ�� 
		{
			++i;
			++j;
		}
		else
		{
			i=i-j+2;//ָ��������¿�ʼƥ�� 
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
	printf("�������ַ���S��\n");
	gets(s);
	StrAssign(S,s);
	printf("����ַ���S��\n");
	StrPrint(S); 
	printf("�������ַ���T��\n"); 
	gets(t);
	StrAssign(T,t);
	printf("����ַ���T��\n");
	StrPrint(T);
	printf("������λ��(��pos���ַ�֮��):\n");
	scanf("%d",&pos);
	printf("ģʽ��T������S��λ��Ϊ%d\n",Index(S,T,pos));
	return 0;
}
