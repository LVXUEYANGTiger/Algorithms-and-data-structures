#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE  100 //顺序表存储空间的初始分配量
#define OK 1
#define ERROR 0
#define LT(a,b) ((a)<=(b)) 
typedef int KeyType;
typedef int Status;
typedef struct{
	KeyType key;
}ElemType;
typedef struct{
	ElemType *elem;
	Status length;
}SSTable;
Status Init_Sq(SSTable &ST)//构造一个空的线性表 
{
	ST.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	ST.length=0;
	return OK;	
} 
Status Create_Sq(SSTable &ST,int n)//创建一个非空顺序表 
{
	Status i;
	if(n<0)
	{
		return ERROR;
	} 
	Init_Sq(ST);
	ST.length=n;
	printf("请输入%d个数字\n",n);
	for(i=1;i<=ST.length;i++)
	{
		scanf("%d",&ST.elem[i].key);
	}
	return OK;
}
Status Output_Sq(SSTable ST)//输出顺序表 
{
	Status i;
	printf("顺序表各元素为:\n");
	for(i=1;i<=ST.length;i++)
	{
		printf("%d  ",ST.elem[i].key);
	}
	printf("\n");
}
Status Search_Sq(SSTable ST,KeyType key)
{
	Status i;
	ST.elem[0].key=key;
	for(i=ST.length;ST.elem[i].key!=key;--i);
	return i;
	
} 
Status Sort(SSTable &ST)
{
	int i,j,temp;
	for(i=1;i<=ST.length;i++)
	{
		for(j=1;j<=ST.length-i;j++)
		{
			if(ST.elem[j].key>ST.elem[j+1].key)
			{
				temp=ST.elem[j+1].key;
				ST.elem[j+1].key=ST.elem[j].key;
				ST.elem[j].key=temp;
			}
		}
	}
}
Status Search_Bin(SSTable ST,KeyType key)
{
	//在该有序表ST中折半查找关键字等于key的数据元素。若找到，则函数值为
	//该元素在表中的位置否则为0
	Status mid;
	Status low=1;
	Status high=ST.length;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(key==ST.elem[mid].key)
		{
			return mid;
		}
		else if(LT(key,ST.elem[mid].key))
		{
			high=mid-1;
		}
		else
		{
			low=mid+1;
		}
	} 
	return 0;
}
Status Destory(SSTable &ST)
{

	free(ST.elem);
	ST.elem=NULL;
	ST.length=0;
	
	return 1;
} 
void Menu(void)
{
printf("\t\t   ===============静态顺序表===============\n");
printf("\t\t   =                                       =\n");
printf("\t\t   =         请选择你的操作：              =\n");
printf("\t\t   =         [1]创建顺序表                 =\n");
printf("\t\t   =         [2]查找一个元素               =\n");
printf("\t\t   =         [3]二分查找元素               =\n");
printf("\t\t   =         [4]对顺序表进行排序           =\n");
printf("\t\t   =         [5]显示顺序表                 =\n");
printf("\t\t   =         [6]销毁                       =\n");
printf("\t\t   =         [7]退出                       =\n");
printf("\t\t   =========================================\n");

printf("\n");
printf("\n");
printf("请选择你要进行的操作:\n");
}
int main(int argc, char** argv) 
{
	Status i,j,n,key,temp;
	SSTable ST;
	Init_Sq(ST);//构造一个空的顺序表
	
	Menu();
	scanf("%d",&i);
	while(i!=7){
		switch(i){
			case 1:
				printf("请输入顺序表的关键字个数：\n");
				scanf("%d",&n);
				//创建一个非空的顺序表
				if(Create_Sq(ST,n))
				{
					printf("创建成功！\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("请输入想要查找的关键字:\n");
				scanf("%d",&key);
				temp=Search_Sq(ST,key);
				if(temp==0)
				{
					printf("该表没有这个元素!!!\n");
				}
				else
				{
					printf("该元素的位置为%d\n",temp);
				}
				Menu();
			    break;
			case 3:
				printf("请输入想要查找的关键字:\n");
				scanf("%d",&key);
				temp=Search_Bin(ST,key); 
				if(temp==0)
				{
					printf("该表没有这个元素!!!\n");
				}
				else
				{
					printf("该元素的位置为%d\n",temp);
				}
				Menu();
			    break;
			case 4:
				printf("对顺序表进行排序!!!\n");
				Sort(ST);
				Menu();
				break; 
			case 5:
				printf("输出这个表:\n"); 
				Output_Sq(ST);
				Menu();
				break; 
			case 6:
				printf("销毁这个表:\n"); 
				temp=Destory(ST); 
				if(temp==1)
				{
					printf("销毁成功!!!\n");
				}
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
