#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define MAXSIZE 1000 //链表的最大长度
typedef float ElemType;//定义float的别名
typedef int Status;//定义int的别名 
typedef struct{
	ElemType data;
	Status cur;//游标 
}component,SLinkList[MAXSIZE]; 
//函数的声明
Status LocateElem_SL(SLinkList S,ElemType e);//在表中查找 
void InitSpace_SL(SLinkList &space);//将一个数组初始化为一个链表 
Status Malloc_SL(SLinkList &space);//取一个节点 
void Free_SL(SLinkList &space,Status k);//将空闲节点链接在备用链表上
void difference(SLinkList &space,Status &S);//(A-B)U(B-A);

Status LocateElem_SL(SLinkList S,ElemType e)//在表中进行查找 
{
	Status i;
	//在静态单链线性表中L查找第一个值为e的元素
	//若找到则返回他在L中的位序,否则返回0
	i=S[0].cur;//表示第一个节点 
	while(i!=0&&S[i].data!=e)
	{
		i=S[i].cur;//相当于p=p->data；向后移动 
	}
	return i;
} 
void InitSpace_SL(SLinkList &space)//将一个数组初始化为一个链表 
{
	//将一维数组space中个分量链成一个备用链表，space[0].cur为头指针
	//0表示空指针
	Status i;
	for(i=0;i<MAXSIZE-1;i++)
	{
		space[i].cur=i+1;
	} 
	space[MAXSIZE-1].cur=0;//尾指针后面不指向任何东西所以设为 0
}
Status Malloc_SL(SLinkList &space)//取一个节点 
{
	Status i;
	//若备用空间链表非空，则返回分配的节点下标，否则返回0
	i=space[0].cur;
	if(space[0].cur!=0)
	{
		space[0].cur=space[i].cur;	
	} 
	return i;
} 
void Free_SL(SLinkList &space,Status k)//将空闲节点链接在备用链表上 
{
	//将下标为k的空闲节点回收到备用链表中
	space[k].cur=space[0].cur;
	space[0].cur=k;
} 
void difference(SLinkList &space,Status &S)
{
	Status i,j,m,n,r,p,k; 
	ElemType b;
	//依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)U(B-A)
	//的静态链表S为其头指针假设备用空间足够大space[0].cur为头指针 
	InitSpace_SL(space);//初始化备用空间
	S=Malloc_SL(space);//生成S的头结点
	r=S;//r指向S的当前最后节点
	scanf("%d%d",&m,&n); //输入A和B的元素个数
	for(j=1;j<=m;j++)//建立集合A的链表 
	{
		i=Malloc_SL(space);//分配节点
		scanf("%f",&space[i].data);//输入A的元素值
		space[r].cur=i;//插入表尾 
		r=i; 
	} 
	space[r].cur=0;//尾节点的指针为空
	for(j=1;j<=n;j++)//依次输入B的元素若在A中则删除若不在A中则插入 
	{
		scanf("%f",&b);//k指向集合A中的第一个节点 
		p=S;
		k=space[S].cur;
		while(k!=space[r].cur&&space[k].data!=b)//在当前表中查找 
		{
			p=k;
			k=space[k].cur; 
		}
		if(k==space[r].cur)//当前表中不存在该元素插入在r所指的节点之后且r的位置不变 
		{
			i=Malloc_SL(space);
			space[i].data=b;
			space[i].cur=space[r].cur;
			space[r].cur=i;
		}
		else//若表中已存在该元素删除之 
		{
			space[p].cur=space[k].cur;
			Free_SL(space,k);
			if(r==k)
			{
				r=p;//若删除的是r所指的节点，则修改尾指针 
			}
		}
	} 
	
}

int main(int argc, char** argv) 
{
	SLinkList space;
	Status s=0;
	difference(space,s);
	for(s=2;s<8;s++)//好进行测试输入6个数 
	{
		printf("%4.2f ",space[s].data);
	}
	return 0;
}
