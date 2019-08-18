#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
//-------------------------------------------------------------------------------------------------- 
//		����˼�룺
//		��M����Ԫ��˳����������ҳ���0
//		�е�1��...ֱ�����һ�е���Ԫ��
//		�����ҵ���ÿ����Ԫ������н�����
//		˳��洢��T��˳����� 
//---------------------------------ϡ��������Ԫ��˳���洢��ʾ-----------------------------------
#define MAXSIZE 12500 //�������Ԫ���������ֵΪ12500 
typedef int Status;
typedef int ElemType;
typedef struct{
	int i,j;//�÷���Ԫ�����±�����±�
	ElemType e; 
}Triple; 
typedef struct{
	Triple data[MAXSIZE+1];//����Ԫ��Ԫ��
	int mu,nu,tu;//��������������ͷ���Ԫ���� 
}TSMatrix;
//----------------------------------------------------------------------------------------------------
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
{
	//������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T��
	//˳��ȡ��ֱ�Ӵ档����M������ȡ��Ԫ�飬�������кź��кŷŵ�T���ʵ�λ�á�
	
	Status num[1000],cpot[1000];//�������� 
	Status col=0,t=0,p=0,q=0;
		
//----------------------------------��������Ĺ�ʽ����-------------------------------------------------------
//num[col]��ʾ����M�ĵ�col���з���Ԫ�ĸ�����cpot[col]ָʾM�е�col�еĵ�һ������Ԫ��B.data�е�ǡ��λ�� 
//								{
//									cpot[0]=0;
//									cpot[col]=cpot[col-1]+num[col-1] 
//								} 
//--------------------------------------------------------------------------------------------------------------
	T.mu=M.nu;//��M��������T������ 
	T.nu=M.mu;//��M��������T������ 
	T.tu=M.tu;//��M�ķ���Ԫ������T�ķ���Ԫ����
	
	if(T.tu)
	{
		for(col=0;col<M.nu;++col)
		{
			num[col]=0;
		}
		for(t=0;t<M.tu;++t)
		{
			++num[M.data[t].j];//��ÿһ�������ķ���Ԫ�ĸ��� 
		}
		cpot[0]=0;
		//���col���е�һ������Ԫ��b.data�����
		for(col=1;col<M.nu;++col)
		{
			cpot[col]=cpot[col-1]+num[col-1];
		} 
		for(p=0;p<M.tu;++p)
		{
			col=M.data[p].j;
			q=cpot[col];
			T.data[q].i=M.data[p].j;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];
		}
	} 
	return OK;
	 
} 
//-------------------------------------------------------------------------------------------------------------
void CreatTSMatrix(TSMatrix &M)
{ 
    printf("������ϡ����������:\n");
    scanf("%d",&M.mu);
    printf("������ϡ����������:\n");
    scanf("%d",&M.nu);
    printf("����������з���Ԫ�صĸ���:\n");
    scanf("%d",&M.tu);
     
    int i;
    for(i=0;i<M.tu;i++)
    {
        printf("�������%d��Ԫ�ص��кź��кż���Ԫ�ص�ֵ:\n",i+1);
        scanf("%d %d %d",&M.data[i].i,&M.data[i].j,&M.data[i].e);
    }
}
//-------------------------------------------------------------------------------------------------------------
Status Print(TSMatrix M)
{
	//��ӡ����Ԫ�� 
	int i,j,k=0,e=0;
	
	printf("����Ԫ��Ϊ:\n"); 
	for(i=0;i<M.mu;i++)
	{
		for(j=0;j<M.nu;j++)
		{
			if(i==M.data[k].i&&j==M.data[k].j)
			{
				printf("%d ",M.data[k].e);
				k++;
			} 
			else
			{
				printf("%d ",e);
			}
			
		}
		printf("\n");
	} 
}
//-------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv) 
{
	TSMatrix M,T;
	
	printf("������M:\n");
	CreatTSMatrix(M);
	Print(M);
	FastTransposeSMatrix(M,T);
	Print(T);
	return 0;
}
