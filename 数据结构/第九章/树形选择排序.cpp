#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>//INT_MAX等
#define N 8
#define MAXSIZE 20 //一个用做示例的小顺序表的最大长度 
typedef int KeyType;//定义关键字类型为整数类型
typedef int InfoType;//定义其它数据项的类型
typedef struct{
	KeyType key;//关键字项
	InfoType otherinfo;//其它数据项 
}RedType; //记录类型
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或用做哨兵单元
	int length;//顺序表长度 
}SqList;//顺序表类型
//顺序表的建立
void CreateSqList(SqList &L)
{
	int i;
	printf("请输入要创建的顺序表的长度:\n");
	scanf("%d",&L.length);
	printf("请输入顺序表的值(以空格隔开)\n");
	for(i=1;i<=L.length;i++)
	{
		scanf("%d",&L.r[i].key);
		L.r[i].otherinfo=i;
	}
} 
//顺序表的输出
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
//树形选择排序
void TreeSort(SqList &L){
	int i,j,j1,k,k1,l,n=L.length;
	RedType *t;
	l=(int)ceil(log(n)/log(2))+1; 				//完全二叉树的层数 
	k=(int)pow(2,l)-1; 							//l层完全二叉树的结点总数  
	k1=(int)pow(2,l-1)-1; 						//l-1层完全二叉树的结点总数 
	t=(RedType*)malloc(k*sizeof(RedType)); 		//二叉树采用顺序存储结构  
	for(i=1;i<=n;i++) 							//将L.r赋给叶子结点 
		t[k1+i-1]=L.r[i];
	for(i=k1+n;i<k;i++) 						//给多余的叶子的关键字赋无穷大 
		t[i].key=INT_MAX;
	j1=k1;
	j=k;
	while(j1){ 									//给非叶子结点赋值 
		for(i=j1;i<j;i+=2)
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
		j=j1;
		j1=(j1-1)/2;
	}
	for(i=0;i<n;i++){
		L.r[i+1]=t[0]; 							//将当前最小值赋给L.r[i] 
		j1=0;
		for(j=1;j<l;j++) 						//沿树根找结点t[0]在叶子中的序号j1 
			t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		t[j1].key=INT_MAX;
		while(j1){
			j1=(j1+1)/2-1; 						//序号为j1的结点的双亲结点序号 
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	free(t);
}
 
int main(int argc,char**argv)
{
	SqList L;
	CreateSqList(L);
	printf("直接插入排序后的结果为：\n");
	TreeSort(L);
	PrintSqList(L);
	return 0;
}
