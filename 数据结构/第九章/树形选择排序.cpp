#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>//INT_MAX��
#define N 8
#define MAXSIZE 20 //һ������ʾ����С˳������󳤶� 
typedef int KeyType;//����ؼ�������Ϊ��������
typedef int InfoType;//�������������������
typedef struct{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//���������� 
}RedType; //��¼����
typedef struct{
	RedType r[MAXSIZE+1];//r[0]���û������ڱ���Ԫ
	int length;//˳����� 
}SqList;//˳�������
//˳���Ľ���
void CreateSqList(SqList &L)
{
	int i;
	printf("������Ҫ������˳���ĳ���:\n");
	scanf("%d",&L.length);
	printf("������˳����ֵ(�Կո����)\n");
	for(i=1;i<=L.length;i++)
	{
		scanf("%d",&L.r[i].key);
		L.r[i].otherinfo=i;
	}
} 
//˳�������
void PrintSqList(SqList L)
{
	int i;
	printf("key   ord\n");
	for(i=1;i<=L.length;i++)
	{
		printf("%d %4d\n",L.r[i].key,L.r[i].otherinfo);
	}
	printf("\n");
}
//����ѡ������
void TreeSort(SqList &L){
	int i,j,j1,k,k1,l,n=L.length;
	RedType *t;
	l=(int)ceil(log(n)/log(2))+1; 				//��ȫ�������Ĳ��� 
	k=(int)pow(2,l)-1; 							//l����ȫ�������Ľ������  
	k1=(int)pow(2,l-1)-1; 						//l-1����ȫ�������Ľ������ 
	t=(RedType*)malloc(k*sizeof(RedType)); 		//����������˳��洢�ṹ  
	for(i=1;i<=n;i++) 							//��L.r����Ҷ�ӽ�� 
		t[k1+i-1]=L.r[i];
	for(i=k1+n;i<k;i++) 						//�������Ҷ�ӵĹؼ��ָ������ 
		t[i].key=INT_MAX;
	j1=k1;
	j=k;
	while(j1){ 									//����Ҷ�ӽ�㸳ֵ 
		for(i=j1;i<j;i+=2)
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
		j=j1;
		j1=(j1-1)/2;
	}
	for(i=0;i<n;i++){
		L.r[i+1]=t[0]; 							//����ǰ��Сֵ����L.r[i] 
		j1=0;
		for(j=1;j<l;j++) 						//�������ҽ��t[0]��Ҷ���е����j1 
			t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		t[j1].key=INT_MAX;
		while(j1){
			j1=(j1+1)/2-1; 						//���Ϊj1�Ľ���˫�׽����� 
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	free(t);
}
 
int main(int argc,char**argv)
{
	SqList L;
	CreateSqList(L);
	printf("ֱ�Ӳ��������Ľ��Ϊ��\n");
	TreeSort(L);
	PrintSqList(L);
	return 0;
}
