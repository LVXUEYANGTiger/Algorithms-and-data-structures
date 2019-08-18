#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
//-------------------------------------------------------------------------------------------------- 
//		基本思想：
//		在M的三元组顺序表中依次找出第0
//		列第1列...直到最后一列的三元组
//		并将找到的每个三元组的行列交换后
//		顺序存储到T的顺序表中 
//---------------------------------稀疏矩阵的三元组顺序表存储表示-----------------------------------
#define MAXSIZE 12500 //假设非零元个数的最大值为12500 
typedef int Status;
typedef int ElemType;
typedef struct{
	int i,j;//该非零元的行下标和列下标
	ElemType e; 
}Triple; 
typedef struct{
	Triple data[MAXSIZE+1];//非零元三元组
	int mu,nu,tu;//矩阵的行数列数和非零元个数 
}TSMatrix;
//----------------------------------------------------------------------------------------------------
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
{
	//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T。
	//顺序取，直接存。即在M中依次取三元组，交换其行号和列号放到T中适当位置。
	
	Status num[1000],cpot[1000];//辅助数组 
	Status col=0,t=0,p=0,q=0;
		
//----------------------------------辅助数组的公式如下-------------------------------------------------------
//num[col]表示矩阵M的第col列中非零元的个数。cpot[col]指示M中第col列的第一个非零元在B.data中的恰当位置 
//								{
//									cpot[0]=0;
//									cpot[col]=cpot[col-1]+num[col-1] 
//								} 
//--------------------------------------------------------------------------------------------------------------
	T.mu=M.nu;//把M的列数给T的行数 
	T.nu=M.mu;//把M的行数给T的列数 
	T.tu=M.tu;//把M的非零元个数给T的非零元个数
	
	if(T.tu)
	{
		for(col=0;col<M.nu;++col)
		{
			num[col]=0;
		}
		for(t=0;t<M.tu;++t)
		{
			++num[M.data[t].j];//求每一列所含的非零元的个数 
		}
		cpot[0]=0;
		//求第col列中第一个非零元在b.data的序号
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
    printf("请输入稀疏矩阵的行数:\n");
    scanf("%d",&M.mu);
    printf("请输入稀疏矩阵的列数:\n");
    scanf("%d",&M.nu);
    printf("请输入矩阵中非零元素的个数:\n");
    scanf("%d",&M.tu);
     
    int i;
    for(i=0;i<M.tu;i++)
    {
        printf("请输入第%d个元素的行号和列号及其元素的值:\n",i+1);
        scanf("%d %d %d",&M.data[i].i,&M.data[i].j,&M.data[i].e);
    }
}
//-------------------------------------------------------------------------------------------------------------
Status Print(TSMatrix M)
{
	//打印矩阵元素 
	int i,j,k=0,e=0;
	
	printf("矩阵元素为:\n"); 
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
	
	printf("请输入M:\n");
	CreatTSMatrix(M);
	Print(M);
	FastTransposeSMatrix(M,T);
	Print(T);
	return 0;
}
