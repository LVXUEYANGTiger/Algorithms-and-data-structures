#include <iostream>
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#define ERROR 0
#define TRUE 1 
#define FALSE 0 
#define OK 1
#define MAXSTRLEN 255//�û�������255���ڶ�����󴮳� 
typedef unsigned char SString[MAXSTRLEN+1];//0��Ԫ�ش�Ŵ��ĳ��� 
typedef int Status; 
//��������
Status StrAssign(SString T,char *chars);// ���ɴ� 
Status StrCopy(SString T,SString S);//���� 
Status StrEmpty(SString S);//�ж��Ƿ�Ϊ�մ� 
Status StrCompare(SString S,SString T);//�Ƚ� 
Status StrLength(SString S);//�󳤶� 
Status ClearString(SString S);//��� 
Status Concat(SString T,SString S1,SString S2);//���� 
Status SubString(SString Sub,SString S,Status pos,Status len);//ȡ�Ӵ� 
Status Index(SString S,SString T,Status pos);//��λ����λ�� 
void replace(SString &S,SString T,SString V);//ȡ���� 
Status StrInser(SString S,Status pos,SString T);//���봮 
Status StrDelete(SString &S,Status pos,Status len);//ɾ���� 
void StrPrint(SString T);//����� 
 
Status StrAssign(SString T,char *chars)
{
	//����һ����ֵ����chars�Ĵ�T
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
	//�ɴ�S���Ƶô�T
	Status i;
	for(i=0;i<=S[0];i++)
	{
		T[i]=S[i];
	} 
	return OK;
}
Status StrEmpty(SString S)
{
	//��SΪ�մ��򷵻�TRUE���򷵻�FALSE
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
	//��ʼ����ST������
	//�����������S>T�򷵻�ֵ>0��S=T�򷵻�ֵ=0��S<T�򷵻�ֵ<0
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
	//���ش���Ԫ�ظ��� 
	return S[0];
}
Status ClearString(SString S)
{
	//��S���Ϊ�մ�
	S[0]=0;//���Ϊ��
	return OK; 
}
Status Concat(SString T,SString S1,SString S2)
{
	//��T����S1��S2�����Ӷ��ɵ��´���δ�ض��򷵻�TRUE���򷵻�FALSE
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
	else if(S1[0]<MAXSTRLEN)//�ض�S2 
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
	//��Sub���ش�S�ĵ�POS���ַ��𳤶�Ϊlen���Ӵ�
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
	//�����Ӵ�T������S�е�POS���ַ�֮���λ���������ڷ���ֵΪ0 
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
		i=Index(S,T,pos);//��S�ж�λ�Ӵ�T��λ��i
		if(i!=0)
		{
			SubString(sub,S,pos,i-pos);//ȡs�б������Ӵ�
			Concat(news,news,sub); //���� 
			Concat(news,news,V);
			pos=i+m;//��һ�ζ�λ��λ�� 
		} 
	}
	SubString(sub,S,pos,n-pos+1);
	Concat(S,news,sub); 
}
Status StrInser(SString S,Status pos,SString T)
{
	//z�ڴ�S�ĵ�POS���ַ�֮ǰ���봮T��ȫ����󷵻�TRUE ���ֲ���󷵻�ERROR
	Status i;
	if(pos<1||pos>S[0]+1)
	{
		return ERROR;
	} 
	if(S[0]+T[0]<=MAXSTRLEN)
	{
		//��ȫ����
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
		//���ֲ���
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
	//��S�е�posλ�ó���Ϊlen���Ӵ�
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
	//����ַ���T
	Status i;
	for(i=1;i<=T[0];i++)
	{
		printf("%c",T[i]);
	} 
	printf("\n");
}
int main(int argc, char** argv) 
{	
	//����ʱ���æ���Լ��ⶨ 
	SString T,S,Sub,V;
	int i;
	char cmp,chars[MAXSTRLEN+1];
	
	printf("�����봮S:\n");
	gets(chars);
	StrAssign(S,chars);
	printf("���ɵĴ�SΪ:\n");
	StrPrint(S);
	
	printf("�����봮T:\n");
	gets(chars);
	StrAssign(T,chars);
	printf("���ɵĴ�Ϊ:\n");
	StrPrint(T);
	printf("�����봮V:\n");
	gets(chars);
	StrAssign(V,chars);
	StrPrint(V);
//	printf("���ƴ�T\n");
//	StrCopy(T,S);
//	StrPrint(S); 
//	
//	printf("(�մ�Ϊ1����Ϊ0)%d\n",StrEmpty(S));
//	printf("��ͬΪ1S>TΪ����0S<TΪС��0%d\n",StrCompare(S,T));
//	printf("���ĳ���Ϊ:%d",StrLength(S));
//	printf("���Ӵ�:\n");
//	Concat(Sub,S,T);
//	printf("���ɵĴ�Ϊ:\n");
//	StrPrint(Sub);
//	SubString(Sub,S,1,3);
//	StrPrint(Sub);
//	printf("�ַ�λ��%d\n",Index(Sub,S,1)); 
	replace(S,T,V);
//	StrInser(S,1,T);
//	StrDelete(T,1,2);
//	StrPrint(T);
	return 0;
}
