#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#define N 8
 
#define SIZE 100 				/* 静态链表容量 */
typedef int KeyType; 			/* 定义关键字类型为整型 */
typedef int InfoType; 			/* 定义其它数据项的类型 */
typedef struct{
	KeyType key; 				/* 关键字项 */
	InfoType otherinfo; 		/* 其它数据项，具体类型在主程中定义 */
}RedType; 						/* 记录类型 */

typedef struct{
	RedType rc; 				/* 记录项 */
	int next; 					/* 指针项 */
}SLNode; 						/* 表结点类型 */

typedef struct{
	SLNode r[SIZE]; 			/* 0号单元为表头结点 */
	int length; 				/* 链表当前长度 */
}SLinkListType; 				/* 静态链表类型 */

void CreateSLinkList(SLinkListType &SL){
	int i,p,q; 
	SL.r[0].next=0;
	printf("请输入要创建的顺序表的长度：\n");
	scanf("%d",&SL.length);
	printf("请输入顺序表的值(以空格隔开)\n");
	for(i=1;i<=SL.length;++i){
		scanf("%d",&SL.r[i].rc.key);
		SL.r[i].rc.otherinfo=i;
		q=0;
		p=SL.r[0].next;
		while(SL.r[p].rc.key<=SL.r[i].rc.key)
		{										//静态链表向后移 
			q=p;
			p=SL.r[p].next;
		}
		SL.r[i].next=p;						//将当前记录插入静态链表  
		SL.r[q].next=i;
	}
} 

void Arrange(SLinkListType &SL)
{			//根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字  
   			//非递减有序顺序排列 
   int i,p,q;
   SLNode t;
   p=SL.r[0].next;				//p指示第一个记录的当前位置  
   for(i=1;i<SL.length;++i)
   {						// SL.r[1..i-1]中记录已按关键字有序排列,第i个记录在SL中的当前位置应不小于i 
     while(p<i)
       p=SL.r[p].next;				//找到第i个记录，并用p指示其在SL中当前位置 
     q=SL.r[p].next;				//q指示尚未调整的表尾  
     if(p!=i)
     {
       t=SL.r[p];					//交换记录，使第i个记录到位 
       SL.r[p]=SL.r[i];
       SL.r[i]=t;
       SL.r[i].next=p;			//指/向被移走的记录，使得以后可由while循环找回 
     }
     p=q;						//p指示尚未调整的表尾，为找第i+1个记录作准备 
   }
}

void Sort(SLinkListType L,int adr[])
{	//求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号 
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
}

void Rearrange(SLinkListType &L,int adr[])
{				//adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 
   				//按adr重排L.r，使其有序. 
   int i,j,k;
   for(i=1;i<L.length;++i)
     if(adr[i]!=i)
     {
       j=i;
       L.r[0]=L.r[i];					//暂存记录(*L).r[i] 
       while(adr[j]!=i)
       {							//调整(*L).r[adr[j]]的记录到位直到adr[j]=i为止 
         k=adr[j];
         L.r[j]=L.r[k];
         adr[j]=j;
         j=k;						//记录按序到位 
       }
       L.r[j]=L.r[0];
       adr[j]=j;
    }
}

void print(SLinkListType L)
{
   int i;
   for(i=1;i<=L.length;i++)
    	printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
}
 

int main(int argc,char **argv)
{
	SLinkListType L1,L2;
	CreateSLinkList(L1);
	int *adr,i;
	L2=L1;								//复制静态链表l2与l1相同 */
	printf("排序前:\n");
	print(L1);
	Arrange(L1);
	printf("L1排序后:\n");
	print(L1);
	adr=(int*)malloc((L2.length+1)*sizeof(int));
	Sort(L2,adr);
	for(i=1;i<=L2.length;i++)
		printf("adr[%d]=%d ",i,adr[i]);
	printf("\n");
	Rearrange(L2,adr);
	printf("L2排序后:\n");
	print(L2);
	return 0;
}

