#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20//一个用做示例的小顺序表的最大长度
typedef int KeyType;//定义关键字类型为整型
typedef int InfoType;
typedef int Status;
typedef int RcdType;
#define OK 1
#define ERROR 0
#define FALSE 0
typedef struct{
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据项 
}RedType; //记录类型
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或当做哨兵单元
	Status length;//顺序表长度 
}SqList;
typedef SqList HeapType;//堆采用顺序表存储表示 
//约定如下
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
Status Creat(SqList &L,int n)
{
	Status i=0;
	L.length=n;
	printf("请输入%d个数字:\n",n);
	for(i=1;i<=L.length;i++)
	{
		scanf("%d",&L.r[i].key);
	}
	return OK;
}
//遍历顺序表 
void Print(SqList L)
{
	Status i;
	printf("顺序表的元素为:\n");
	for(i=1;i<=L.length;i++)
	{
		printf("%d ",L.r[i].key);
	}
	printf("\n"); 
} 
Status InsertSort(SqList &L)
{
	//对顺序表做直接插入排序
	Status j=0,i;
	for(i=2;i<=L.length;i++)
	{
		if(LT(L.r[i].key,L.r[i-1].key))//需要将L.r[i]插入有序子表 
		{
			L.r[0]=L.r[i];
			for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
			{
				L.r[j+1]=L.r[j];//记录后移 
			}
			L.r[j+1]=L.r[0]; 
		}		
	} 
	return OK;
} 
//折半插入排序
void BInsertSort(SqList &L)
{
	//对顺序表做折半插入排序
	Status i,low,high,m;
	for(i=2;i<=L.length;++i)
	{
		L.r[0].key=L.r[i].key;//将L.r[i]暂存在L.r[0]
		low=1;
		high=i-1; 
		while(low<=high)//在r[low.high]中折半查找有序插入的位置 
		{
			m=(low+high)/2;//折半 
			if(LT(L.r[0].key,L.r[m].key))
			{
				high=m-1;
			} 
			else
			{
				low=m+1;//插入点在高半区 
			}
		}
		for(int j=i-1;j>=high+1;--j)
		{
			L.r[j+1].key=L.r[j].key;//记录往后移 
		}
		L.r[high+1].key=L.r[0].key;//插入 
	} 
} 
Status Partition(SqList &L,int low,int high)
{
	//交换顺序表L中子表r[low...high]的记录枢轴记录到位，并返回所在位置，此时
	//在它之前的记录均不大于它
	Status pivotkey;
	 
	L.r[0]=L.r[low];//用子表的第一个记录做枢轴记录
	pivotkey=L.r[low].key;//枢轴记录关键字
	while(low<high)//从表的俩端交替地向中间扫描 
	{
		while(low<high&&L.r[high].key>=pivotkey)
		{
			--high;
		}
		L.r[low]=L.r[high];//将比枢轴记录小的记录移到低端 
		while(low<high&&L.r[low].key<=pivotkey)
		{
			++low;
		}
		L.r[high]=L.r[low];//将比枢轴记录大的记录移动到高端 
	} 
	L.r[low]=L.r[0];//枢轴记录到位
	return low;//返回枢轴位置 
} 
void Qsort(SqList &L,int low,int high)
{
	//对顺序表L中的子序列L.r[low..high]做快速排序
	Status pivotloc;
	
	if(low<high)//长度大于1 
	{
		pivotloc=Partition(L,low,high);//将L.r[low...high]一分为2
		Qsort(L,low,pivotloc-1); //对于低子表递归排序pivotloc是枢轴位置
		Qsort(L,pivotloc+1,high);//对高子表递归排序 
	} 
} 
//冒泡排序
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
//简单选择排序
void  select_sort(SqList &L)
{
	Status i,j,min,temp;
	
	for(i=1;i<=L.length;i++)
	{
		j=i;
		min=i;//记录最小值下标
		for(j=i+1;j<=L.length;j++)
		{
			if(L.r[j].key<L.r[min].key)
			{
				min=j;
			}
		} 
		if(min!=i)//将最小值放在正确的位置 
		{
			temp=L.r[i].key;
			L.r[i].key=L.r[min].key;
			L.r[min].key=temp; 
		}
	}
}
//希尔排序
void ShellInsert(SqList &L,int dk)
{
	//对顺序表L做一趟希尔插入排序本算法是和一趟直接插入排序比较做了以下修改
	//1.前后记录位置的增量是dk而不是1
	//2.r[0]只是暂存单元而不是哨兵当j<=0时插入位置已经找到
	Status j=0,i=0;
	for(i=dk+1;i<=L.length;++i)
	{
		if(LT(L.r[i].key,L.r[i-dk].key))//需将L.r[i]插入有序增量表 
		{
			L.r[0]=L.r[i];//暂存在L.r[0] 
			for(j=i-dk;j>0&&LT(L.r[0].key,L.r[j].key);j-=dk)
			{
				L.r[j+dk]=L.r[j];//记录后移查找插入位置 
			}
			L.r[j+dk]=L.r[0];//插入 
		}
	} 
} 
void ShellSort(SqList &L,int dlta[],int t)
{
	//按增量序列dlta[0...t-1]对顺序表做希尔排序
	for(int k=0;k<t;++k)
	{
		ShellInsert(L,dlta[k]);//一趟增量为dlta[k]的插入排序 
	} 
} 
/* 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n] */
void Merge(RedType SR[],RedType TR[],int i,int m,int n)
{
 	int j,k,l;
	for(j=m+1,k=i;i<=m && j<=n;k++) /* 将SR中记录由小到大归并入TR */
	{
		if (SR[i].key<SR[j].key)
		   TR[k].key=SR[i++].key;
		else
		   TR[k].key=SR[j++].key;
	}
	if(i<=m)
	{
	   for(l=0;l<=m-i;l++)
	   TR[k+l].key=SR[i+l].key;  /* 将剩余的SR[i..m]复制到TR */
	}
	if(j<=n)
	{
	   for(l=0;l<=n-j;l++)
	   TR[k+l].key=SR[j+l].key;  /* 将剩余的SR[j..n]复制到TR */
	}
}
/* 将SR[s..t]归并排序为TR1[s..t] */
Status MSort(RedType SR[],RedType TR1[],int s, int t)
{
    int m;
    RedType TR2[MAXSIZE+1];
    if(s==t)
    TR1[s].key=SR[s].key;
	else
	{
		m=(s+t)/2;   /* 将SR[s..t]平分为SR[s..m]和SR[m+1..t] */
		MSort(SR,TR2,s,m); /* 递归地将SR[s..m]归并为有序的TR2[s..m] */
		MSort(SR,TR2,m+1,t); /* 递归地将SR[m+1..t]归并为有序TR2[m+1..t] */
		Merge(TR2,TR1,s,m,t); /* 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] */
	}
}
void MergeSort(SqList &L)
{ 
   MSort(L.r,L.r,1,L.length);
}
//堆排序
void HeapAdjust(HeapType &H,int s,int m)
{
	//已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义本函数H.r[s]的关键字使用H.r[s...m]成为一个大顶堆
	//(对其中关键字而说)
	RedType rc=H.r[s];
	for(int j=2*s;j<=m;j*=2)//沿key较大的孩子结点筛选 
	{
		if(j<m&&LT(H.r[j].key,H.r[j+1].key))//j为key较大的记录的下标 
		{
			++j;
		} 
		if(!LT(rc.key,H.r[j].key))//rc应插入在位置s上 
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
	//对顺序表进行堆排序
	RedType temp;
	for(int i=H.length/2;i>0;--i)//把H.r[1....H.length]建成大顶堆 
	{
		HeapAdjust(H,i,H.length); 
	} 
	for(int i=H.length;i>1;--i)
	{
		temp=H.r[1];
		H.r[1]=H.r[i];
		H.r[i]=temp;
		HeapAdjust(H,1,i-1); //将H.r[1...i-1]重新调整为大顶堆 
	}
}
void Menu(void)
{
	printf("\t\t   ================排序=====================\n");
	printf("\t\t   =                                       =\n");
	printf("\t\t   =         请选择你的操作：              =\n");
	printf("\t\t   =         [1]创建表                     =\n");
	printf("\t\t   =         [2]输出表                     =\n");
	printf("\t\t   =         [3]直接插入排序               =\n");
	printf("\t\t   =         [4]快速排序                   =\n");
	printf("\t\t   =         [5]冒泡排序                   =\n");
	printf("\t\t   =         [6]简单选择排序               =\n");
	printf("\t\t   =         [7]希尔排序                   =\n");
	printf("\t\t   =         [8]归并排序                   =\n");
	printf("\t\t   =         [9]折半插入排序               =\n");
	printf("\t\t   =         [10]堆排序                    =\n");
	printf("\t\t   =========================================\n");
	
	printf("\n");
	printf("\n");
	printf("请选择你要进行的操作:\n");
}
int main(int argc, char** argv) 
{
	Menu();
	SqList A,B,C;
	Status i=0,n,key;
	int dlta[]={5,3,2,1};//增量因子 
	
	scanf("%d",&i);
	while(i!=11){
		switch(i){
			case 1:
				printf("请输入关键字个数：\n");
				scanf("%d",&n);
				if(Creat(A,n))
				{
					printf("创建成功！\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("遍历该表:\n");
				Print(A);
				Menu();
			    break;
			case 3:
				printf("直接插入排序：\n");
				InsertSort(A);
				Menu();
			    break;
			case 4:
				printf("快速排序：\n");
				Qsort(A,1,A.length);
				Menu();
				break; 
			case 5:
				printf("冒泡排序：\n");
				BubbleSort(A);
				Menu();
				break; 
			case 6:
				printf("简单选择排序\n"); 
				select_sort(A);
				Menu();
				break;
			case 7:
				printf("希尔排序:\n");
				ShellSort(A,dlta,A.length);
				Menu();
				break;
			case 8:
				printf("归并排序:\n");
				MergeSort(A);
				Menu();
				break;
			case 9:
				printf("折半插入排序:\n");
				BInsertSort(A);
				Menu();
				break;	
			case 10:
				printf("堆排序:\n");
				HeapSort(A); 
				Menu();
				break;
		    default:
				printf("输入有误,请重新输入!\n");
				Menu();
				break;
		}
		scanf("%d",&i);

	}
	return 0;
}
