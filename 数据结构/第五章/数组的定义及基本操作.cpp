#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
struct Arr{
	int *pBase;//存储的是数组的第一个元素的地址
	int len;//数组所能容纳的最大元素的个数
	int cnt;//数组有效元素的个数 
}; 
//数组的初始化仅仅初始化的是一个有长度的数组,里面并没有值 
void init_arr(struct Arr *pArr,int len)
{
	pArr->pBase=(int *)malloc(sizeof(int)*len);
	if(pArr->pBase==NULL)
	{
		printf("内存动态分配失败\n");
	}
	else
	{
		pArr->len=len;
		pArr->cnt=0; 
	}
} 
//给数组赋值
void input_arr(struct Arr &pArr,int val)//val为元素的个数 
{
	int i=0;
	pArr.cnt=val;
	for(i=0;i<val;i++)
	{
		scanf("%d",&pArr.pBase[i]);
	}
} 
//判断数组是否为空
int is_empty(struct Arr* pArr)
{
	if(pArr->cnt==0)
	{
		return 0;//空 
	}
	else
	{
		return 1;//非空 
	}
} 
//输出数组元素
void show_arr(struct Arr *pArr)
{
	int i=0;
	if(is_empty(pArr)==0)
	{
		printf("当前的数组为空\n");
	}
	else
	{
		for(i=0;i<pArr->cnt;i++)
		{
			printf("%d ",pArr->pBase[i]);
		}
		printf("\n");
	}
} 
//判断元素是否已满
int is_full(struct Arr *pArr)
{
	if(pArr->len==pArr->cnt)
	{
		return 0;//已满 
	}
	else
	{
		return 1;//未满 
	}
} 
//在最后的位置追加元素 
int append_arr(struct Arr *pArr,int val)
{
	if(is_full(pArr)==0)
	{
		return 0;
	}
	else
	{
		pArr->pBase[pArr->cnt]=val;
		pArr->cnt++;
		return 1; 
	} 
}
int insert_arr(struct Arr &pArr,int pos,int val)
{
	int i;
	if(is_full(&pArr)==0)
	{
		return 0;//0表示当前数组已满无法再进行插入 
	}
	if(pos<0||pos>(pArr.len))
	{
		return 1;//插入位置不合法 
	} 
	for(i=pArr.cnt-1;i>=pos-1;--i)
	{
		pArr.pBase[i+1]=pArr.pBase[i];
	}
	pArr.pBase[pos-1]=val;
	pArr.cnt++;
	return 2;//表示插入成功 
}
int main(int argc, char** argv) 
{
	struct Arr pArr;
	int len,i,val,m,n; 
	
	printf("请输入想要创建数组长度:\n");
	scanf("%d",&len);
	init_arr(&pArr,len);
	printf("请输入数组元素的个数:\n"); 
	scanf("%d",&val);
	input_arr(pArr,val);
	show_arr(&pArr);
	printf("判断数组是否为空(空为0不空为1)%d\n",is_empty(&pArr));
	printf("判断数组元素是否为满(满为0不满为1)%d\n",is_full(&pArr)); 
	printf("请输入你想要插入的位置和元素:\n");
	scanf("%d%d",&m,&n);
	insert_arr(pArr,m,n);
	show_arr(&pArr); 
	//在最后一个元素位置之后追加一个元素
	append_arr(&pArr,9); 
	show_arr(&pArr); 
	return 0;
}
