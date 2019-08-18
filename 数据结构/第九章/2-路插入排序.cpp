#include <stdio.h>
#include <stdlib.h>

#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
typedef int Status; 


#define MAXSIZE 20			//一个用做示例的小顺序表的最大长度 

typedef int KeyType;		//定义关键字类型为整数类型 
typedef int InfoType; 		//定义其它数据项的类型 

typedef struct{
	KeyType key;			//关键字项 
	InfoType otherinfo;		//其他数据项 
}RcdType;					//记录类型 

typedef struct{
	RcdType r[MAXSIZE+1];		//r[0]闲置或用作哨兵单元 
	int length;					//顺序表长度 
}SqList;						//顺序表类型 

//------------------------------顺序表L的建立----------------------------------------- 

Status CreateSqList(SqList &L){
	int i; 
	printf("请输入要创建的顺序表的长度：\n");
	scanf("%d",&L.length);
	printf("请输入顺序表的值(以空格隔开)\n");
	for(i=1;i<=L.length;++i){
		scanf("%d",&L.r[i].key);
	}
	return OK; 
} 
//----------------------------顺序表L的输出-------------------------------------------- 

void PrintSqList(SqList L)
{ 
	int i;
	for(i=1;i<=L.length;++i){
		printf("%4d",L.r[i].key);
	}
	printf("\n");
}
 
//-----------------------------2_路插入排序-------------------------------------------
void P2_InsertSort(SqList &L){											
	int i,j,first,final;
	RcdType *d;
	d=(RcdType*)malloc(L.length*sizeof(RcdType));					//生成L.length个记录的临时空间 
	d[0]=L.r[1];											//设L的第1个记录为d中排好序的记录(在位置[0]) 
	first=final=0;											//first、final分别指示d中排好序的记录的第1个和最后1个记录的位置 
	for(i=2;i<=L.length;++i)
	{															//依次将L的第2个～最后1个记录插入d中 
		if (L.r[i].key<d[first].key)
		{														//待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素) 
			first=(first-1+L.length)%L.length;					//设d为循环向量 
			d[first]=L.r[i];
		}
		else if(L.r[i].key>d[final].key)
		{							//待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素) 
			final=final+1;
			d[final]=L.r[i];
		}
		else{						//待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素) 
			j=final++;				//移动d的尾部元素以便按序插入记录 
			while(L.r[i].key<d[j].key)
			{
				d[(j+1)%L.length]=d[j];
				j=(j-1+L.length)%L.length;
			}
			d[j+1]=L.r[i];
		}
	}
	for(i=1;i<=L.length;i++) 					//把d赋给L.r 
		L.r[i]=d[(i+first-1)%L.length]; 		//线性关系  
}
int main(int argc,char **argv)
{
   SqList L;
   CreateSqList(L);
   int i;
   printf("排序前:\n");
   PrintSqList(L);
   P2_InsertSort(L);
   printf("2_路插入排序后:\n");
   PrintSqList(L);
	return 0;
}
