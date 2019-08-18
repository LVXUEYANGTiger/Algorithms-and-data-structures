#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE  100 //˳���洢�ռ�ĳ�ʼ������
#define OK 1
#define ERROR 0
#define LT(a,b) ((a)<=(b)) 
typedef int KeyType;
typedef int Status;
typedef struct{
	KeyType key;
}ElemType;
typedef struct{
	ElemType *elem;
	Status length;
}SSTable;
Status Init_Sq(SSTable &ST)//����һ���յ����Ա� 
{
	ST.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	ST.length=0;
	return OK;	
} 
Status Create_Sq(SSTable &ST,int n)//����һ���ǿ�˳��� 
{
	Status i;
	if(n<0)
	{
		return ERROR;
	} 
	Init_Sq(ST);
	ST.length=n;
	printf("������%d������\n",n);
	for(i=1;i<=ST.length;i++)
	{
		scanf("%d",&ST.elem[i].key);
	}
	return OK;
}
Status Output_Sq(SSTable ST)//���˳��� 
{
	Status i;
	printf("˳����Ԫ��Ϊ:\n");
	for(i=1;i<=ST.length;i++)
	{
		printf("%d  ",ST.elem[i].key);
	}
	printf("\n");
}
Status Search_Sq(SSTable ST,KeyType key)
{
	Status i;
	ST.elem[0].key=key;
	for(i=ST.length;ST.elem[i].key!=key;--i);
	return i;
	
} 
Status Sort(SSTable &ST)
{
	int i,j,temp;
	for(i=1;i<=ST.length;i++)
	{
		for(j=1;j<=ST.length-i;j++)
		{
			if(ST.elem[j].key>ST.elem[j+1].key)
			{
				temp=ST.elem[j+1].key;
				ST.elem[j+1].key=ST.elem[j].key;
				ST.elem[j].key=temp;
			}
		}
	}
}
Status Search_Bin(SSTable ST,KeyType key)
{
	//�ڸ������ST���۰���ҹؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ
	//��Ԫ���ڱ��е�λ�÷���Ϊ0
	Status mid;
	Status low=1;
	Status high=ST.length;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(key==ST.elem[mid].key)
		{
			return mid;
		}
		else if(LT(key,ST.elem[mid].key))
		{
			high=mid-1;
		}
		else
		{
			low=mid+1;
		}
	} 
	return 0;
}
Status Destory(SSTable &ST)
{

	free(ST.elem);
	ST.elem=NULL;
	ST.length=0;
	
	return 1;
} 
void Menu(void)
{
printf("\t\t   ===============��̬˳���===============\n");
printf("\t\t   =                                       =\n");
printf("\t\t   =         ��ѡ����Ĳ�����              =\n");
printf("\t\t   =         [1]����˳���                 =\n");
printf("\t\t   =         [2]����һ��Ԫ��               =\n");
printf("\t\t   =         [3]���ֲ���Ԫ��               =\n");
printf("\t\t   =         [4]��˳����������           =\n");
printf("\t\t   =         [5]��ʾ˳���                 =\n");
printf("\t\t   =         [6]����                       =\n");
printf("\t\t   =         [7]�˳�                       =\n");
printf("\t\t   =========================================\n");

printf("\n");
printf("\n");
printf("��ѡ����Ҫ���еĲ���:\n");
}
int main(int argc, char** argv) 
{
	Status i,j,n,key,temp;
	SSTable ST;
	Init_Sq(ST);//����һ���յ�˳���
	
	Menu();
	scanf("%d",&i);
	while(i!=7){
		switch(i){
			case 1:
				printf("������˳���Ĺؼ��ָ�����\n");
				scanf("%d",&n);
				//����һ���ǿյ�˳���
				if(Create_Sq(ST,n))
				{
					printf("�����ɹ���\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("��������Ҫ���ҵĹؼ���:\n");
				scanf("%d",&key);
				temp=Search_Sq(ST,key);
				if(temp==0)
				{
					printf("�ñ�û�����Ԫ��!!!\n");
				}
				else
				{
					printf("��Ԫ�ص�λ��Ϊ%d\n",temp);
				}
				Menu();
			    break;
			case 3:
				printf("��������Ҫ���ҵĹؼ���:\n");
				scanf("%d",&key);
				temp=Search_Bin(ST,key); 
				if(temp==0)
				{
					printf("�ñ�û�����Ԫ��!!!\n");
				}
				else
				{
					printf("��Ԫ�ص�λ��Ϊ%d\n",temp);
				}
				Menu();
			    break;
			case 4:
				printf("��˳����������!!!\n");
				Sort(ST);
				Menu();
				break; 
			case 5:
				printf("��������:\n"); 
				Output_Sq(ST);
				Menu();
				break; 
			case 6:
				printf("���������:\n"); 
				temp=Destory(ST); 
				if(temp==1)
				{
					printf("���ٳɹ�!!!\n");
				}
				Menu();
				break;
		    default:
				printf("��������,����������!\n");
				Menu();
				break;
		}
		scanf("%d",&i);
	}
	

	return 0;
}
