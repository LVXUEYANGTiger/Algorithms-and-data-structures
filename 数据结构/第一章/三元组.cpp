#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1
typedef float ElemType;
typedef int Status;
typedef ElemType *Triplet;
//�������� 
Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3);// ������Ԫ�� 
Status DestroyTriplet(Triplet &T);//������Ԫ�� 
Status Get(Triplet &T,Status i,ElemType &e);//ȡ��Ԫ���һ���� 
Status Put(Triplet &T,Status i,ElemType e);//����Ԫ���з�һ���� 
Status IsAscending(Triplet T);//�ж���Ԫ���Ƿ����� 
Status IsDescending(Triplet T);//�ж���Ԫ���Ƿ��� 
Status Max(Triplet T,ElemType &e);//����Ԫ�������ֵ 
Status Min(Triplet T,ElemType &e);//����Ԫ������Сֵ 

//������Ԫ��
Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3)
{
	T=(ElemType*)malloc(3*sizeof(ElemType));
	if(T==NULL)//�ж��Ƿ����ɹ� 
	{
		exit(OVERFLOW);	
	}
	T[0]=v1;
	T[1]=v2;
	T[2]=v3;
	return OK;
} 
//������Ԫ��
Status DestroyTriplet(Triplet &T)
{
	free(T);//���ͷ��ڴ� 
	T=NULL;
	return OK; 
}
//ȡ��Ԫ���һ����
Status Get(Triplet &T,Status i,ElemType &e)
{
	if(i<1||i>3)
	{
		return ERROR;
	}
	else
	{
		e=T[i-1];
	}
	return OK;
} 
//����Ԫ���д��һ����
Status Put(Triplet &T,Status i,ElemType e)
{
	if(i<1||i>3)
	{
		return ERROR;
	}
	else
	{
		T[i-1]=e;
	}
	return OK;
} 
//�ж���Ԫ���Ƿ�����
Status IsAscending(Triplet T)
{
	return(T[0]<T[1])&&(T[1]<T[2]);
}
//�ж���Ԫ���Ƿ���
Status IsDescending(Triplet T)
{
	return(T[0]>T[1])&&(T[1]>T[2]);
} 
//�����ֵ
Status Max(Triplet T,ElemType &e)
{
	e=(T[0]>=T[1])?((T[0]>=T[2])?T[0]:T[2]):((T[1]>=T[2])?T[1]:T[2]);
	return OK;
} 
//����Сֵ
Status Min(Triplet T,ElemType &e)
{
	e=(T[0]<=T[1])?((T[0]<=T[2])?T[0]:T[2]):((T[1]<=T[2])?T[1]:T[2]);
	return OK;
}


int main(int argc, char** argv) 
{
	Triplet T;
	ElemType v1,v2,v3,e;
	Status flag,i,x;
	
	printf("���������������¹��ܣ�\n");
	printf("1.��ʼ����Ԫ��T\n2.ȡ��Ԫ���һ������\n3.������Ԫ���һ������\n4.����Ƿ�Ϊ������\n5.����Ƿ�Ϊ������\n6.������ֵ\n7.�����Сֵ\n8.������Ԫ��\n");
	printf("����������Ҫ�Ĺ���:\n");
     
	
	
	
    while(1)
    {
  
    scanf("%d",&x);
    switch(x)
    {
    	case 1:{
				printf("������3�����ִ�������Ԫ����:\n");
				scanf("%f%f%f",&v1,&v2,&v3);
				flag=InitTriplet(T,v1,v2,v3);
				if(flag==1)
				{
					printf("��Ԫ���ʼ���ɹ���Ԫ���ֵ�ֱ�Ϊ%4.2f %4.2f %4.2f\n",T[0],T[1],T[2]);
				}
				};continue;
    	case 2:{
				printf("����������ȡ����Ԫ���еڼ���Ԫ�ص�ֵ\n");
				scanf("%d",&i); 
				flag=Get(T,i,e);
				printf("��%d��Ԫ�ص�ֵΪ%4.2f\n",i,e);
				};continue;
    	case 3:{
				printf("����������Ҫ�����λ�ú���ֵ:\n"); 
				scanf("%d%f",&i,&e);
				Put(T,i,e);
				printf("�µ���Ԫ���ֵΪ:%4.2f %4.2f %4.2f\n",T[0],T[1],T[2]);
				};continue;
        case 4:{
				if(IsAscending(T))
				{
					printf("����Ԫ������\n");
				} 
				};continue;
       	case 5:{	
		   		if(IsDescending(T))
				{
					printf("����Ԫ�齵��\n");
				} 
				else
				{
					printf("����Ԫ�鲻����\n");
				}
				};continue;
       	case 6:{
		   		Max(T,e);
				printf("����Ԫ���е����ֵΪ��%4.2f\n",e);
				};continue;
   		case 7:{	
		   		Min(T,e);
				printf("����Ԫ���е����СֵΪ��%4.2f\n",e); 
				};continue;
	    case 8:{
				flag=DestroyTriplet(T);
				printf("������Ԫ������0:\n");
				scanf("%d",&flag); 
				if(flag==0)
				{
					printf("��Ԫ�����ٳɹ�\n");
				}
				};continue;    	
    }
	}

	
	return 0;
}
