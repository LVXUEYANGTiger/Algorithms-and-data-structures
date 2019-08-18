#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <cstdlib>
#define LIST_INIT_SIZE 100 //线性表存储空间的初始量分配
#define LISTINCREMENT 10 //线性表存储空间的分配量
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef float ElemType;
typedef int Status;
typedef struct{
	ElemType *elem;//存储空间基址 
	Status length;//当前长度
	Status listsize;//当前分配的存储容量 
}SqList;
//函数声明
Status InitList_Sq(SqList &L);//空表初始化  
Status ListInsert_Sq(SqList &L,Status i,ElemType e);//插入 
Status ListDelete_Sq(SqList &L,Status i,ElemType &e);//删除 
Status LocateElem_Sq(SqList L,ElemType e);//查找 
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc); 

Status InitList_Sq(SqList &L)//空表初始化 
{
	//构造一个空的线表L 
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(L.elem==NULL)//判断内存是否分配失败 
	{
		exit(OVERFLOW);
	}
	L.length=0;//空表长度为0 
	L.listsize=LIST_INIT_SIZE;//初始存储量（所放的元素个数）
	return OK; 
}
//插入一个值 
Status ListInsert_Sq(SqList &L,Status i,ElemType e)
{
	ElemType *newbase ,*q,*p;
	if(i<1||i>L.length)//判断i值是否合法 
	{
		return ERROR;
	}
	if(L.length>=L.listsize)//判断存储空间是否已满 
	{
		newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL)
		{
			exit(OVERFLOW);//判断是否重新分配成功 
		}
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;
	}
	q=&(L.elem[i-1]);//q为插入位置
	for(p = &(L.elem[L.length-1]);p>=q;--p)//p为最后一个元素的位置 
	{
		*(p+1)=*p;//插入元素右移		
	} 
	*q = e;
	++L.length;
	return  OK;	
} 
//删除一个值
Status ListDelete_Sq(SqList &L,Status i,ElemType &e)
{
	ElemType *p,*q; 
	//在顺序表中删除第i个元素并用e返回结果
	if((i<1)||(i>L.length))//判断i值是否合法 
	{
		return ERROR;
	} 
	p = &(L.elem[i-1]);//p为删除的位置 
	e = *p;//把删除的元素的值给e 
	q = L.elem+L.length-1; //表尾元素的位置 
	for(++p;p<=q;++p)
	{
		*(p-1)=*p;//被删除的元素之后左移 
	}
	--L.length;
	return OK; 
}
//对线性表进行查找
Status LocateElem_Sq(SqList L,ElemType e)
{
	//在顺序表中查询第一个满足判定条件的数据元素
	//若元素存在则返回它的位序，否则则返回0
	Status i;//i的初始值为第一个元素的位序
	i=1; 
	while(i<=L.length&&L.elem[i-1]!=e)
	{
		++i;
	}
	if(i<=L.length)
	{
		return i;
	}
	else
	{
		return 0;
	}
}
//对a,b俩表进行有序合并C
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc)
{
	ElemType *pa,*pb,*pc,*pa_last,*pb_last;
	//已知线性表的元素按递增元素排序
	//归并La和Lb得到新表Lc
	pa=La.elem;
	pb=Lb.elem;
	Lc.listsize=Lc.length=La.length+Lb.length;
	pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
	if(!Lc.elem)//判断是否分配失败 
	{
		exit(OVERFLOW); 
	}
	pa_last=La.elem+La.length-1;
	pb_last=Lb.elem+Lb.length-1;
	while((pa<=pa_last)&&(pb<=pb_last))
	{
		if(*pa<=*pb)
		{
			*pc++=*pa++;
		}
		else
		{
			*pc++=*pb++;
		}
	}
	while(pa<=pa_last)//将a中剩余的元素复制到c中 
	{
		*pc++=*pa++;
	}
	while(pb<=pb_last)//将b中剩余的元素复制到c中 
	{
		*pc++=*pb++;
	}
}
int main(int argc, char** argv) 
{
	SqList La,Lb,Lc;//定义3个表
	ElemType e;
	Status i=0,a,b,flag; 
	InitList_Sq(La);//初始化空表a 
	InitList_Sq(Lb);//初始化空表b
	InitList_Sq(Lc);//初始化空表c
	
	//给ab表赋值 
	printf("请输入您想要在a中输入的元素个数:\n"); 
	scanf("%d",&a);
	La.length=a;
	for(i=0;i<a;i++)
	{
		scanf("%f",&La.elem[i]);
	}
	printf("请输入您想要在b中输入的元素个数:\n"); 
	scanf("%d",&b);
	Lb.length=b;
	for(i=0;i<b;i++)
	{
		scanf("%f",&Lb.elem[i]);
	}
	
	//插入一个值
	printf("请输入你想在a表插入的元素位置和元素:\n");
	La.length=(a+1)*sizeof(ElemType);
	scanf("%d%f",&i,&e); 
	ListInsert_Sq(La,i,e);
	for(i=0;i<a+1;i++)
	{
		printf("%4.2f ",La.elem[i]);
	}
	
	printf("\n");
	//删除一个值
	printf("请输入你想在a表中删除的元素位置:\n");
	scanf("%d",&i); 
	La.length=(a-1)*sizeof(ElemType);
	ListDelete_Sq(La,i,e);
	for(i=0;i<a;i++)
	{
		printf("%4.2f ",La.elem[i]);
	}
	printf("\n");
	printf("删除的元素为%f:\n",e);
	
	//对线性表进行查找
	printf("请输入你想在a表中想找到的元素:\n");
	scanf("%f",&e); 
	i=LocateElem_Sq(La,e);
	printf("元素的位置为%d\n",i);
	printf("\n");
		
	//对a,b俩表进行有序合并C	
	MergeList_Sq(La,Lb,Lc);
	printf("合成c表为:\n");
	for(i=0;i<a+b;i++)
	{	
		printf("%4.2f ",Lc.elem[i]);	
	}
	return 0;
}
