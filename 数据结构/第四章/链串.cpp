#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define linkNum 4//全局设置链表中节点存放数据的个数
typedef struct Link{
	char a[linkNum];//数据域可存放linkNum个数据
	struct Link* next;//代表指针域指向直接后继元素 
}link;//nk为节点名每个节点都是link结构体
//初始化链表其中head为头指针str为存储的字符串
link * initLink(link *head,char* str)
{
	int length=strlen(str);
	//根据字符串的长度计算出链表中使用节点的个数
	int num=length/linkNum;
	if(length%linkNum)
	{
		num++;
	} 
	//创建并初始化首元节点
	head=(link*)malloc(sizeof(link));
	head->next=NULL;
	link *temp=head;
	//初始化链表
	for(int i=0;i<num;i++)
	{
		int j=0;
		for(;j<linkNum;j++)
		{
			if(i*linkNum+j<length)
			{
				temp->a[j]=str[i*linkNum+j];
			}
			else
			{
				temp->a[j]='#';
			}
		}
		if(i*linkNum+j<length)
		{
			link * newlink=(link*)malloc(sizeof(link));
			newlink->next=NULL;
			temp->next=newlink;
			temp=newlink;
		}
	} 
	return head;
} 
//输出链表
void displayLink(link *head)
{
	link* temp=head;
	while(temp)
	{
		for(int i=0;i<linkNum;i++)
		{
			printf("%c",temp->a[i]);
		}
		temp=temp->next;
	}
} 
int main(int argc, char** argv) 
{
	link* head=NULL;
	int n=0;
	
	char a[1000];
	gets(a);
	head=initLink(head,a);
	displayLink(head);
	return 0;
}
