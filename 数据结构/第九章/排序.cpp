#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20//һ������ʾ����С˳������󳤶�
typedef int KeyType;//����ؼ�������Ϊ����
typedef int InfoType;
typedef int Status;
typedef int RcdType;
#define OK 1
#define ERROR 0
#define FALSE 0
typedef struct{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//���������� 
}RedType; //��¼����
typedef struct{
	RedType r[MAXSIZE+1];//r[0]���û����ڱ���Ԫ
	Status length;//˳����� 
}SqList;
typedef SqList HeapType;//�Ѳ���˳���洢��ʾ 
//Լ������
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
Status Creat(SqList &L,int n)
{
	Status i=0;
	L.length=n;
	printf("������%d������:\n",n);
	for(i=1;i<=L.length;i++)
	{
		scanf("%d",&L.r[i].key);
	}
	return OK;
}
//����˳��� 
void Print(SqList L)
{
	Status i;
	printf("˳����Ԫ��Ϊ:\n");
	for(i=1;i<=L.length;i++)
	{
		printf("%d ",L.r[i].key);
	}
	printf("\n"); 
} 
Status InsertSort(SqList &L)
{
	//��˳�����ֱ�Ӳ�������
	Status j=0,i;
	for(i=2;i<=L.length;i++)
	{
		if(LT(L.r[i].key,L.r[i-1].key))//��Ҫ��L.r[i]���������ӱ� 
		{
			L.r[0]=L.r[i];
			for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
			{
				L.r[j+1]=L.r[j];//��¼���� 
			}
			L.r[j+1]=L.r[0]; 
		}		
	} 
	return OK;
} 
//�۰��������
void BInsertSort(SqList &L)
{
	//��˳������۰��������
	Status i,low,high,m;
	for(i=2;i<=L.length;++i)
	{
		L.r[0].key=L.r[i].key;//��L.r[i]�ݴ���L.r[0]
		low=1;
		high=i-1; 
		while(low<=high)//��r[low.high]���۰������������λ�� 
		{
			m=(low+high)/2;//�۰� 
			if(LT(L.r[0].key,L.r[m].key))
			{
				high=m-1;
			} 
			else
			{
				low=m+1;//������ڸ߰��� 
			}
		}
		for(int j=i-1;j>=high+1;--j)
		{
			L.r[j+1].key=L.r[j].key;//��¼������ 
		}
		L.r[high+1].key=L.r[0].key;//���� 
	} 
} 
Status Partition(SqList &L,int low,int high)
{
	//����˳���L���ӱ�r[low...high]�ļ�¼�����¼��λ������������λ�ã���ʱ
	//����֮ǰ�ļ�¼����������
	Status pivotkey;
	 
	L.r[0]=L.r[low];//���ӱ�ĵ�һ����¼�������¼
	pivotkey=L.r[low].key;//�����¼�ؼ���
	while(low<high)//�ӱ�����˽�������м�ɨ�� 
	{
		while(low<high&&L.r[high].key>=pivotkey)
		{
			--high;
		}
		L.r[low]=L.r[high];//���������¼С�ļ�¼�Ƶ��Ͷ� 
		while(low<high&&L.r[low].key<=pivotkey)
		{
			++low;
		}
		L.r[high]=L.r[low];//���������¼��ļ�¼�ƶ����߶� 
	} 
	L.r[low]=L.r[0];//�����¼��λ
	return low;//��������λ�� 
} 
void Qsort(SqList &L,int low,int high)
{
	//��˳���L�е�������L.r[low..high]����������
	Status pivotloc;
	
	if(low<high)//���ȴ���1 
	{
		pivotloc=Partition(L,low,high);//��L.r[low...high]һ��Ϊ2
		Qsort(L,low,pivotloc-1); //���ڵ��ӱ�ݹ�����pivotloc������λ��
		Qsort(L,pivotloc+1,high);//�Ը��ӱ�ݹ����� 
	} 
} 
//ð������
void BubbleSort(SqList &L)
{
	Status i,j,temp,change=1;
	for(i=L.length;i>=1&&change==1;--i)
	{
		change=0;
		for(j=0;j<i;j++)
		{
			if(L.r[j].key>L.r[j+1].key)
			{
				change=1;
				temp=L.r[j].key;
				L.r[j].key=L.r[j+1].key;
				L.r[j+1].key=temp;
			}
		}
	}
} 
//��ѡ������
void  select_sort(SqList &L)
{
	Status i,j,min,temp;
	
	for(i=1;i<=L.length;i++)
	{
		j=i;
		min=i;//��¼��Сֵ�±�
		for(j=i+1;j<=L.length;j++)
		{
			if(L.r[j].key<L.r[min].key)
			{
				min=j;
			}
		} 
		if(min!=i)//����Сֵ������ȷ��λ�� 
		{
			temp=L.r[i].key;
			L.r[i].key=L.r[min].key;
			L.r[min].key=temp; 
		}
	}
}
//ϣ������
void ShellInsert(SqList &L,int dk)
{
	//��˳���L��һ��ϣ�����������㷨�Ǻ�һ��ֱ�Ӳ�������Ƚ����������޸�
	//1.ǰ���¼λ�õ�������dk������1
	//2.r[0]ֻ���ݴ浥Ԫ�������ڱ���j<=0ʱ����λ���Ѿ��ҵ�
	Status j=0,i=0;
	for(i=dk+1;i<=L.length;++i)
	{
		if(LT(L.r[i].key,L.r[i-dk].key))//�轫L.r[i]�������������� 
		{
			L.r[0]=L.r[i];//�ݴ���L.r[0] 
			for(j=i-dk;j>0&&LT(L.r[0].key,L.r[j].key);j-=dk)
			{
				L.r[j+dk]=L.r[j];//��¼���Ʋ��Ҳ���λ�� 
			}
			L.r[j+dk]=L.r[0];//���� 
		}
	} 
} 
void ShellSort(SqList &L,int dlta[],int t)
{
	//����������dlta[0...t-1]��˳�����ϣ������
	for(int k=0;k<t;++k)
	{
		ShellInsert(L,dlta[k]);//һ������Ϊdlta[k]�Ĳ������� 
	} 
} 
/* �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n] */
void Merge(RedType SR[],RedType TR[],int i,int m,int n)
{
 	int j,k,l;
	for(j=m+1,k=i;i<=m && j<=n;k++) /* ��SR�м�¼��С����鲢��TR */
	{
		if (SR[i].key<SR[j].key)
		   TR[k].key=SR[i++].key;
		else
		   TR[k].key=SR[j++].key;
	}
	if(i<=m)
	{
	   for(l=0;l<=m-i;l++)
	   TR[k+l].key=SR[i+l].key;  /* ��ʣ���SR[i..m]���Ƶ�TR */
	}
	if(j<=n)
	{
	   for(l=0;l<=n-j;l++)
	   TR[k+l].key=SR[j+l].key;  /* ��ʣ���SR[j..n]���Ƶ�TR */
	}
}
/* ��SR[s..t]�鲢����ΪTR1[s..t] */
Status MSort(RedType SR[],RedType TR1[],int s, int t)
{
    int m;
    RedType TR2[MAXSIZE+1];
    if(s==t)
    TR1[s].key=SR[s].key;
	else
	{
		m=(s+t)/2;   /* ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t] */
		MSort(SR,TR2,s,m); /* �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m] */
		MSort(SR,TR2,m+1,t); /* �ݹ�ؽ�SR[m+1..t]�鲢Ϊ����TR2[m+1..t] */
		Merge(TR2,TR1,s,m,t); /* ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t] */
	}
}
void MergeSort(SqList &L)
{ 
   MSort(L.r,L.r,1,L.length);
}
//������
void HeapAdjust(HeapType &H,int s,int m)
{
	//��֪H.r[s..m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��屾����H.r[s]�Ĺؼ���ʹ��H.r[s...m]��Ϊһ���󶥶�
	//(�����йؼ��ֶ�˵)
	RedType rc=H.r[s];
	for(int j=2*s;j<=m;j*=2)//��key�ϴ�ĺ��ӽ��ɸѡ 
	{
		if(j<m&&LT(H.r[j].key,H.r[j+1].key))//jΪkey�ϴ�ļ�¼���±� 
		{
			++j;
		} 
		if(!LT(rc.key,H.r[j].key))//rcӦ������λ��s�� 
		{
			break;
		} 
		H.r[s]=H.r[j];
		s=j;
	} 
	H.r[s]=rc;
} 
void HeapSort(HeapType &H)
{
	//��˳�����ж�����
	RedType temp;
	for(int i=H.length/2;i>0;--i)//��H.r[1....H.length]���ɴ󶥶� 
	{
		HeapAdjust(H,i,H.length); 
	} 
	for(int i=H.length;i>1;--i)
	{
		temp=H.r[1];
		H.r[1]=H.r[i];
		H.r[i]=temp;
		HeapAdjust(H,1,i-1); //��H.r[1...i-1]���µ���Ϊ�󶥶� 
	}
}
void Menu(void)
{
	printf("\t\t   ================����=====================\n");
	printf("\t\t   =                                       =\n");
	printf("\t\t   =         ��ѡ����Ĳ�����              =\n");
	printf("\t\t   =         [1]������                     =\n");
	printf("\t\t   =         [2]�����                     =\n");
	printf("\t\t   =         [3]ֱ�Ӳ�������               =\n");
	printf("\t\t   =         [4]��������                   =\n");
	printf("\t\t   =         [5]ð������                   =\n");
	printf("\t\t   =         [6]��ѡ������               =\n");
	printf("\t\t   =         [7]ϣ������                   =\n");
	printf("\t\t   =         [8]�鲢����                   =\n");
	printf("\t\t   =         [9]�۰��������               =\n");
	printf("\t\t   =         [10]������                    =\n");
	printf("\t\t   =========================================\n");
	
	printf("\n");
	printf("\n");
	printf("��ѡ����Ҫ���еĲ���:\n");
}
int main(int argc, char** argv) 
{
	Menu();
	SqList A,B,C;
	Status i=0,n,key;
	int dlta[]={5,3,2,1};//�������� 
	
	scanf("%d",&i);
	while(i!=11){
		switch(i){
			case 1:
				printf("������ؼ��ָ�����\n");
				scanf("%d",&n);
				if(Creat(A,n))
				{
					printf("�����ɹ���\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("�����ñ�:\n");
				Print(A);
				Menu();
			    break;
			case 3:
				printf("ֱ�Ӳ�������\n");
				InsertSort(A);
				Menu();
			    break;
			case 4:
				printf("��������\n");
				Qsort(A,1,A.length);
				Menu();
				break; 
			case 5:
				printf("ð������\n");
				BubbleSort(A);
				Menu();
				break; 
			case 6:
				printf("��ѡ������\n"); 
				select_sort(A);
				Menu();
				break;
			case 7:
				printf("ϣ������:\n");
				ShellSort(A,dlta,A.length);
				Menu();
				break;
			case 8:
				printf("�鲢����:\n");
				MergeSort(A);
				Menu();
				break;
			case 9:
				printf("�۰��������:\n");
				BInsertSort(A);
				Menu();
				break;	
			case 10:
				printf("������:\n");
				HeapSort(A); 
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
