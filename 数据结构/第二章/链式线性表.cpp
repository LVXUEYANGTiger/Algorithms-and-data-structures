#include <iostream>
#include <stdlib.h> 
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h> 
#define ERROR 0
#define OK 1 
typedef float ElemType;
typedef int  Status;
//定义一个结构体模板
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//函数声明

LinkList Creat_listhead(LinkList &head);//头插法 
LinkList Creat_listtail(LinkList &head);//尾插法 
Status ListInsert_L(LinkList &L,Status i,ElemType e);//在链表插入一个元素
Status ListDelete_L(LinkList &L,Status i,ElemType &e);//删除链表中的一个元素 
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc);//合并链表
void printlist(LinkList L);//显示链表元素
Status ListSearch_L(LinkList L,ElemType e,Status &i);//查找一个元素;
void writeFile(LinkList head);//写入文件 
void PutFile(LinkList head);//输出文件 
void heart();
void color(const unsigned short color1);
//创建一个新的链表（用的头插法）
LinkList Creat_listhead(LinkList &head)
{
	LinkList q,node;
	Status count=0,i=0;
	head=(LinkList)malloc(sizeof(LNode));//  为头指针开辟内存空间
	q=head;
	q->next=NULL; 
	printf("请输入表的节点数:\n");
	scanf("%d", &count);
	for (i = 0; i < count;i++) 
	{
		node = (LinkList)malloc(sizeof(LNode));          //  为新结点开辟新内存
		scanf("%f",&node->data);                          
		q->next = node;                      		
		q=node;
	}
	node->next = NULL;
}
//创建一个新的链表 (用的尾插法)
LinkList Creat_listtail(LinkList &head) 
{
	Status count=0,i=0;
	LinkList p;
	head=(LinkList)malloc(sizeof(LNode));
	head->next=NULL;
	printf("请输入表的节点数:\n");
	scanf("%d", &count);
	for (i = count; i >0;--i) 
	{
		p = (LinkList)malloc(sizeof(LNode));          //  为新结点开辟新内存
		scanf("%f",&p->data);                          
		p->next =head->next;                      		
		head->next=p;
	}
}

//在链表插入一个元素
Status ListInsert_L(LinkList &L,Status i,ElemType e)
{
	//在带头节点的单链线性表L中的第i个位置之前插入元素e
	LinkList p,s;
	Status j=0;
	p=L;
	j=0; 
	
	while(p&&j<i-1)
	{
		p=p->next;//寻找第i个节点 
		++j;
	}
	if(!p||j>i-1)//i小于1或者大于表长加1 
	{
		return ERROR;
	} 
	s=(LinkList)malloc(sizeof(LNode)); 
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
} 
//删除一个元素
Status ListDelete_L(LinkList &L,Status i,ElemType &e)
{
	//在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
	LinkList p,q;
	Status j=0;
	p=L; 
	while(p->next&&j<i-1)
	{
		p=p->next;
		++j; 
	}
	if(!(p->next)||j>i-1)
	{
		return ERROR;//删除位置不合理 
	}
	q=p->next;
	p->next=q->next;//删除并释放结点 
	e=q->data;
	free(q);
	return OK; 
} 
//合并链表
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	//已知线性表La和Lb的元素安值非递减排列
	LinkList pa,pb,pc;
	pa=La->next; 
	pb=Lb->next;
	Lc=pc=La;//用La的头节点作为Lc的头结点
	while(pa&&pb)
	{
		if(pa->data<=pb->data)
		{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}
		else
		{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	} 
	pc->next=pa?pa:pb;//插入剩余段
	free(Lb); 
} 
//显示链表元素
void printlist(LinkList L)
{
	LinkList p;
	p=L->next;
	while(p!=NULL)
	{
		printf("%4.2f ",p->data);
		p=p->next;
	}
} 
//对链表进行查找 
Status ListSearch_L(LinkList L,ElemType e,Status &i)
{	
	while(L!=NULL)
	{
		if(L->data==e)
		{
			return 0; 
		}
		i++;
		L=L->next;
	}
	return 0; 
}
void writeFile(LinkList head) 
{
	FILE *outf;
	LinkList p=head;
	if((outf = fopen("data.txt","wt+")) == NULL) 
	{
		printf("不能打开数据文件。\n");
		exit(1);
	}
	while(p) 
	{
		fwrite(p,sizeof(LNode),1,outf);
		p = p->next;
	}
	fclose(outf);
}
void PutFile(LinkList head) 
{
	FILE *outf;
	LinkList p=head;
	if((outf = fopen("data.txt","wt+")) == NULL) 
	{
		printf("不能打开数据文件。\n");
		exit(1);
	}
	while(p) 
	{
		fread(p,sizeof(LNode),1,outf);
		printf("%f ",p->next->data);
		p = p->next;
	}
	fclose(outf);
}
void color(const unsigned short color1)
{        /*仅限改变0-15的颜色;如果在0-15那么实现他的颜色   因为如果超过15后面的改变的是文本背景色。*/
        if(color1>=0&&color1<=15)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
        /*如果不在0-15的范围颜色，那么改为默认的颜色白色；*/
    else
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void heart() 
{    
		for (float y = 1.5f; y > -1.5f; y -= 0.1f) 
{

        for (float x = -1.5f; x < 1.5f; x += 0.05f) {

            float a = x * x + y * y - 1;

            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');

        }

        printf("\n");

    }
}


int main(int argc, char** argv) 
{
	Status n,i=0,t,j;
	char a;
	LinkList La,Lb,Lc;
	ElemType e;
	time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
	
	//喜色红 
	color(4);
	printf("                                        欢迎您使用该程序！                                        \n");
	printf("                                        现在的时间%d.%d.%d.%d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,	p->tm_sec);
	heart();
  
	

	Sleep(3000); 
	system("cls");
	color(10);
	printf("                                        该程序有以下几个功能：                                   \n");
	printf("                                       -------------------------                                 \n");
	printf("                                       | 1.创建所需要的链表    |                                 \n");
	printf("                                       | 2.显示链表的元素值    |                                 \n");
	printf("                                       | 3.对链表进行插入操作  |                                 \n");
	printf("                                       | 4.对链表进行删除操作  |                                 \n");
	printf("                                       | 5.对链表进行查找操作  |                                 \n");
	printf("                                       | 6.对俩个链表进行合并  |                                 \n");
	printf("                                       | 7.把链表写入文件中    |                                 \n");
	printf("                                       | 8.文件的链表输入屏幕上|                                 \n"); 
	printf("                                       | 0.按0退出程序         |                                 \n");
	printf("                                       -------------------------                                 \n");
	printf("\n");
	
	Sleep(500);
	color(16);//白色 
	printf("请输入你想要的功能:\n");
	while(1)
	{
		scanf("%d",&t);
		switch(t)
		{
			case 0:{
				printf("退出成功!\n"); 
				return 0;
			};continue;
			case 1:{
				printf("\n请输入你想要创建的链表方法(头插法0||尾插法1):\n");
				scanf("%d",&j);
				printf("请输入你想要创建的链表个数(1-2):\n");
				scanf("%d",&i);
				if(j==0)
				{
					if(i==1)
					{
						Creat_listhead(La);
					}
					else if(i==2)
					{
						Creat_listhead(La);
						Creat_listhead(Lb);
					}	
				} 
				else if(j==1)
				{
					if(i==1)
					{
						Creat_listtail(La);
					}
					else if(i==2)
					{
						Creat_listtail(La);
						Creat_listtail(Lb);
					}
				}
				else if(j!=1||j!=2)
				{
					printf("该程序只能生成两个表后续功能正在积极更新\n");
				}
				
			
			};continue;
			case 2:{
				    printf("显示链表的元素值:\n");
				    printf("请输入链表的名字:\n");
				    scanf("%c",&a);
				    if('a'==a)
				    {
				    	printlist(La);
					}
					else if('b'==a)
					{
						printlist(Lb);
					}
					
				
			};continue;
			case 3:{
				char m;
				printf("请输入你想要插入表的名字(a和b)\n");
				scanf("%c",&m);
				if(m=='a')
				{
					printf("请输入插入位置和插入元素\n");
					scanf("%d%f",&i,&e);
					ListInsert_L(La,i,e);
				}
				else if(m=='b')
				{
					printf("请输入插入位置和插入元素\n");
					scanf("%d%f",&i,&e);
					ListInsert_L(Lb,i,e);
				} 	
			};continue;
			case 4:{
				char m;
				printf("请输入你想要删除表的名字(a和b)\n");
				scanf("%c",&m);
				if(m=='a')
				{
					printf("请输入删除a表的一个元素的位置");
					scanf("%d",&i);
					ListDelete_L(La,i,e);
					printf("删除的元素为%f\n",e);
				}
				else if(m=='b')
				{
					printf("请输入删除b表的一个元素的位置:\n");
					scanf("%d",&i);
					ListDelete_L(Lb,i,e);
					printf("删除的元素为%f\n",e);
				} 
			};continue;
			case 5:{
				char m;
				printf("请输入你想要查找表的名字(a和b)\n");
				scanf("%c",&m);
				if('a'==m)
				{
					printf("请输入查找的元素\n");
					scanf("%f",&e);
					i=0;
					ListSearch_L(La,e,i);
					printf("该元素的位序是%d\n",i); 
				}
				else if('b'==m)
				{
					printf("请输入查找的元素\n");
					scanf("%f",&e);
					i=0;
					ListSearch_L(Lb,e,i);
					printf("该元素的位序是%d\n",i); 
				} 	 
			};continue;
			case 6:{
				printf("实现ab俩表的合并:\n");
				MergeList_L(La,Lb,Lc);
			};continue;
			case 7:{
				printf("把链表写入文件中:\n");//把信息录到文件中 
				writeFile(La);
			};continue;
			case 8:{
				printf("把文件中的链表输入到屏幕上:\n");//把信息录到文件中 
				PutFile(La);
			};continue;
		}
	} 
	
	
	return 0;
}

