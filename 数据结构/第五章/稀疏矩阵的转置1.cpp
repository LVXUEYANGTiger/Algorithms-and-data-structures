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
Status TransposeSMatrix(TSMatrix M,TSMatrix &T)
{
//	采用三元组表的存储表示求稀疏矩阵M的转置矩阵T
	Status q,col,p; 

	T.mu=M.nu;  //将M的列数给T的行数
	T.nu=M.mu;	//将M的行数给T的列数
	T.tu=M.tu; 	//将M非零元个数给T的非零元个数 
	

	if(T.tu)//判断非零元个数是否是0是0不执行不是0执行 
	{
		q=0;//设置元素的开始位置 
		
		//从非零元的元素中
		for(col=0;col<T.mu;++col) 
		{
			for(p=0;p<M.tu;++p)
			{
				if(M.data[p].j==col) 
				{
					T.data[q].i=M.data[p].j;
					T.data[q].j=M.data[p].i;
					T.data[q].e=M.data[p].e;
					++q;
				}
			}
		} 
	}
	return OK; 
} 
//-----------------------------------------------时间复杂度解析-------------------------------------------
					/*该算法的主要时间耗费是在col和p的两重循环上。
					对于一个m行n列且非零元素个数为t的稀疏矩阵而言，该算法的时间复杂度为O(t*n)。
					例：若矩阵有200行，200列，10,000个非零元素，总共有2,000,000次处理。
					最坏情况是，当稀疏矩阵中的非零元素个数t与mn同数量级时，上述算法的时间复杂度就为O(mn2)。
					显然这种情况下，该算法效率较低	*/		 
//---------------------------------------------------------------------------------------------------------
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
	
	printf("请输入矩阵M元素:\n");
	CreatTSMatrix(M);
	Print(M);
	
	TransposeSMatrix(M,T);
	printf("转置矩阵为T:\n");
	Print(T);
	return 0;
}
