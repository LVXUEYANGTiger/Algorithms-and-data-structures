#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define linkNum 4//ȫ�����������нڵ������ݵĸ���
typedef struct Link{
	char a[linkNum];//������ɴ��linkNum������
	struct Link* next;//����ָ����ָ��ֱ�Ӻ��Ԫ�� 
}link;//nkΪ�ڵ���ÿ���ڵ㶼��link�ṹ��
//��ʼ����������headΪͷָ��strΪ�洢���ַ���
link * initLink(link *head,char* str)
{
	int length=strlen(str);
	//�����ַ����ĳ��ȼ����������ʹ�ýڵ�ĸ���
	int num=length/linkNum;
	if(length%linkNum)
	{
		num++;
	} 
	//��������ʼ����Ԫ�ڵ�
	head=(link*)malloc(sizeof(link));
	head->next=NULL;
	link *temp=head;
	//��ʼ������
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
//�������
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
