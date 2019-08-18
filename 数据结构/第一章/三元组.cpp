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
//声明函数 
Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3);// 创建三元组 
Status DestroyTriplet(Triplet &T);//销毁三元组 
Status Get(Triplet &T,Status i,ElemType &e);//取三元组的一个数 
Status Put(Triplet &T,Status i,ElemType e);//在三元组中放一个数 
Status IsAscending(Triplet T);//判断三元组是否升序 
Status IsDescending(Triplet T);//判断三元组是否降序 
Status Max(Triplet T,ElemType &e);//求三元组中最大值 
Status Min(Triplet T,ElemType &e);//求三元组中最小值 

//创建三元组
Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3)
{
	T=(ElemType*)malloc(3*sizeof(ElemType));
	if(T==NULL)//判断是否分配成功 
	{
		exit(OVERFLOW);	
	}
	T[0]=v1;
	T[1]=v2;
	T[2]=v3;
	return OK;
} 
//销毁三元组
Status DestroyTriplet(Triplet &T)
{
	free(T);//先释放内存 
	T=NULL;
	return OK; 
}
//取三元组的一个数
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
//在三元组中存放一个数
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
//判断三元组是否升序
Status IsAscending(Triplet T)
{
	return(T[0]<T[1])&&(T[1]<T[2]);
}
//判断三元组是否降序
Status IsDescending(Triplet T)
{
	return(T[0]>T[1])&&(T[1]>T[2]);
} 
//求最大值
Status Max(Triplet T,ElemType &e)
{
	e=(T[0]>=T[1])?((T[0]>=T[2])?T[0]:T[2]):((T[1]>=T[2])?T[1]:T[2]);
	return OK;
} 
//求最小值
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
	
	printf("本程序可以完成以下功能：\n");
	printf("1.初始化三元组T\n2.取三元组的一个分量\n3.重置三元组的一个分量\n4.检测是否为升序函数\n5.检测是否为降序函数\n6.输出最大值\n7.输出最小值\n8.销毁三元组\n");
	printf("请输入你需要的功能:\n");
     
	
	
	
    while(1)
    {
  
    scanf("%d",&x);
    switch(x)
    {
    	case 1:{
				printf("请输入3个数字存入是三元组内:\n");
				scanf("%f%f%f",&v1,&v2,&v3);
				flag=InitTriplet(T,v1,v2,v3);
				if(flag==1)
				{
					printf("三元组初始化成功三元组的值分别为%4.2f %4.2f %4.2f\n",T[0],T[1],T[2]);
				}
				};continue;
    	case 2:{
				printf("请输入你想取到三元组中第几号元素的值\n");
				scanf("%d",&i); 
				flag=Get(T,i,e);
				printf("第%d号元素的值为%4.2f\n",i,e);
				};continue;
    	case 3:{
				printf("请输入你想要输入的位置和数值:\n"); 
				scanf("%d%f",&i,&e);
				Put(T,i,e);
				printf("新的三元组的值为:%4.2f %4.2f %4.2f\n",T[0],T[1],T[2]);
				};continue;
        case 4:{
				if(IsAscending(T))
				{
					printf("该三元组升序\n");
				} 
				};continue;
       	case 5:{	
		   		if(IsDescending(T))
				{
					printf("该三元组降序\n");
				} 
				else
				{
					printf("该三元组不降序\n");
				}
				};continue;
       	case 6:{
		   		Max(T,e);
				printf("该三元组中的最大值为：%4.2f\n",e);
				};continue;
   		case 7:{	
		   		Min(T,e);
				printf("该三元组中的最大小值为：%4.2f\n",e); 
				};continue;
	    case 8:{
				flag=DestroyTriplet(T);
				printf("销毁三元组输入0:\n");
				scanf("%d",&flag); 
				if(flag==0)
				{
					printf("三元组销毁成功\n");
				}
				};continue;    	
    }
	}

	
	return 0;
}
