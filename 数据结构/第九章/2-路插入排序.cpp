#include <stdio.h>
#include <stdlib.h>

#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
typedef int Status; 


#define MAXSIZE 20			//һ������ʾ����С˳������󳤶� 

typedef int KeyType;		//����ؼ�������Ϊ�������� 
typedef int InfoType; 		//������������������� 

typedef struct{
	KeyType key;			//�ؼ����� 
	InfoType otherinfo;		//���������� 
}RcdType;					//��¼���� 

typedef struct{
	RcdType r[MAXSIZE+1];		//r[0]���û������ڱ���Ԫ 
	int length;					//˳����� 
}SqList;						//˳������� 

//------------------------------˳���L�Ľ���----------------------------------------- 

Status CreateSqList(SqList &L){
	int i; 
	printf("������Ҫ������˳���ĳ��ȣ�\n");
	scanf("%d",&L.length);
	printf("������˳����ֵ(�Կո����)\n");
	for(i=1;i<=L.length;++i){
		scanf("%d",&L.r[i].key);
	}
	return OK; 
} 
//----------------------------˳���L�����-------------------------------------------- 

void PrintSqList(SqList L)
{ 
	int i;
	for(i=1;i<=L.length;++i){
		printf("%4d",L.r[i].key);
	}
	printf("\n");
}
 
//-----------------------------2_·��������-------------------------------------------
void P2_InsertSort(SqList &L){											
	int i,j,first,final;
	RcdType *d;
	d=(RcdType*)malloc(L.length*sizeof(RcdType));					//����L.length����¼����ʱ�ռ� 
	d[0]=L.r[1];											//��L�ĵ�1����¼Ϊd���ź���ļ�¼(��λ��[0]) 
	first=final=0;											//first��final�ֱ�ָʾd���ź���ļ�¼�ĵ�1�������1����¼��λ�� 
	for(i=2;i<=L.length;++i)
	{															//���ν�L�ĵ�2�������1����¼����d�� 
		if (L.r[i].key<d[first].key)
		{														//�����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d�����Ԫ��) 
			first=(first-1+L.length)%L.length;					//��dΪѭ������ 
			d[first]=L.r[i];
		}
		else if(L.r[i].key>d[final].key)
		{							//�����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d�����Ԫ��) 
			final=final+1;
			d[final]=L.r[i];
		}
		else{						//�����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��) 
			j=final++;				//�ƶ�d��β��Ԫ���Ա㰴������¼ 
			while(L.r[i].key<d[j].key)
			{
				d[(j+1)%L.length]=d[j];
				j=(j-1+L.length)%L.length;
			}
			d[j+1]=L.r[i];
		}
	}
	for(i=1;i<=L.length;i++) 					//��d����L.r 
		L.r[i]=d[(i+first-1)%L.length]; 		//���Թ�ϵ  
}
int main(int argc,char **argv)
{
   SqList L;
   CreateSqList(L);
   int i;
   printf("����ǰ:\n");
   PrintSqList(L);
   P2_InsertSort(L);
   printf("2_·���������:\n");
   PrintSqList(L);
	return 0;
}
