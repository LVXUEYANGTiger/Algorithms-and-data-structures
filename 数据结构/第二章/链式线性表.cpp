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
//����һ���ṹ��ģ��
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//��������

LinkList Creat_listhead(LinkList &head);//ͷ�巨 
LinkList Creat_listtail(LinkList &head);//β�巨 
Status ListInsert_L(LinkList &L,Status i,ElemType e);//���������һ��Ԫ��
Status ListDelete_L(LinkList &L,Status i,ElemType &e);//ɾ�������е�һ��Ԫ�� 
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc);//�ϲ�����
void printlist(LinkList L);//��ʾ����Ԫ��
Status ListSearch_L(LinkList L,ElemType e,Status &i);//����һ��Ԫ��;
void writeFile(LinkList head);//д���ļ� 
void PutFile(LinkList head);//����ļ� 
void heart();
void color(const unsigned short color1);
//����һ���µ������õ�ͷ�巨��
LinkList Creat_listhead(LinkList &head)
{
	LinkList q,node;
	Status count=0,i=0;
	head=(LinkList)malloc(sizeof(LNode));//  Ϊͷָ�뿪���ڴ�ռ�
	q=head;
	q->next=NULL; 
	printf("�������Ľڵ���:\n");
	scanf("%d", &count);
	for (i = 0; i < count;i++) 
	{
		node = (LinkList)malloc(sizeof(LNode));          //  Ϊ�½�㿪�����ڴ�
		scanf("%f",&node->data);                          
		q->next = node;                      		
		q=node;
	}
	node->next = NULL;
}
//����һ���µ����� (�õ�β�巨)
LinkList Creat_listtail(LinkList &head) 
{
	Status count=0,i=0;
	LinkList p;
	head=(LinkList)malloc(sizeof(LNode));
	head->next=NULL;
	printf("�������Ľڵ���:\n");
	scanf("%d", &count);
	for (i = count; i >0;--i) 
	{
		p = (LinkList)malloc(sizeof(LNode));          //  Ϊ�½�㿪�����ڴ�
		scanf("%f",&p->data);                          
		p->next =head->next;                      		
		head->next=p;
	}
}

//���������һ��Ԫ��
Status ListInsert_L(LinkList &L,Status i,ElemType e)
{
	//�ڴ�ͷ�ڵ�ĵ������Ա�L�еĵ�i��λ��֮ǰ����Ԫ��e
	LinkList p,s;
	Status j=0;
	p=L;
	j=0; 
	
	while(p&&j<i-1)
	{
		p=p->next;//Ѱ�ҵ�i���ڵ� 
		++j;
	}
	if(!p||j>i-1)//iС��1���ߴ��ڱ���1 
	{
		return ERROR;
	} 
	s=(LinkList)malloc(sizeof(LNode)); 
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
} 
//ɾ��һ��Ԫ��
Status ListDelete_L(LinkList &L,Status i,ElemType &e)
{
	//�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
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
		return ERROR;//ɾ��λ�ò����� 
	}
	q=p->next;
	p->next=q->next;//ɾ�����ͷŽ�� 
	e=q->data;
	free(q);
	return OK; 
} 
//�ϲ�����
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	//��֪���Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	LinkList pa,pb,pc;
	pa=La->next; 
	pb=Lb->next;
	Lc=pc=La;//��La��ͷ�ڵ���ΪLc��ͷ���
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
	pc->next=pa?pa:pb;//����ʣ���
	free(Lb); 
} 
//��ʾ����Ԫ��
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
//��������в��� 
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
		printf("���ܴ������ļ���\n");
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
		printf("���ܴ������ļ���\n");
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
{        /*���޸ı�0-15����ɫ;�����0-15��ôʵ��������ɫ   ��Ϊ�������15����ĸı�����ı�����ɫ��*/
        if(color1>=0&&color1<=15)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
        /*�������0-15�ķ�Χ��ɫ����ô��ΪĬ�ϵ���ɫ��ɫ��*/
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
	
	//ϲɫ�� 
	color(4);
	printf("                                        ��ӭ��ʹ�øó���                                        \n");
	printf("                                        ���ڵ�ʱ��%d.%d.%d.%d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,	p->tm_sec);
	heart();
  
	

	Sleep(3000); 
	system("cls");
	color(10);
	printf("                                        �ó��������¼������ܣ�                                   \n");
	printf("                                       -------------------------                                 \n");
	printf("                                       | 1.��������Ҫ������    |                                 \n");
	printf("                                       | 2.��ʾ�����Ԫ��ֵ    |                                 \n");
	printf("                                       | 3.��������в������  |                                 \n");
	printf("                                       | 4.���������ɾ������  |                                 \n");
	printf("                                       | 5.��������в��Ҳ���  |                                 \n");
	printf("                                       | 6.������������кϲ�  |                                 \n");
	printf("                                       | 7.������д���ļ���    |                                 \n");
	printf("                                       | 8.�ļ�������������Ļ��|                                 \n"); 
	printf("                                       | 0.��0�˳�����         |                                 \n");
	printf("                                       -------------------------                                 \n");
	printf("\n");
	
	Sleep(500);
	color(16);//��ɫ 
	printf("����������Ҫ�Ĺ���:\n");
	while(1)
	{
		scanf("%d",&t);
		switch(t)
		{
			case 0:{
				printf("�˳��ɹ�!\n"); 
				return 0;
			};continue;
			case 1:{
				printf("\n����������Ҫ������������(ͷ�巨0||β�巨1):\n");
				scanf("%d",&j);
				printf("����������Ҫ�������������(1-2):\n");
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
					printf("�ó���ֻ����������������������ڻ�������\n");
				}
				
			
			};continue;
			case 2:{
				    printf("��ʾ�����Ԫ��ֵ:\n");
				    printf("���������������:\n");
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
				printf("����������Ҫ����������(a��b)\n");
				scanf("%c",&m);
				if(m=='a')
				{
					printf("���������λ�úͲ���Ԫ��\n");
					scanf("%d%f",&i,&e);
					ListInsert_L(La,i,e);
				}
				else if(m=='b')
				{
					printf("���������λ�úͲ���Ԫ��\n");
					scanf("%d%f",&i,&e);
					ListInsert_L(Lb,i,e);
				} 	
			};continue;
			case 4:{
				char m;
				printf("����������Ҫɾ���������(a��b)\n");
				scanf("%c",&m);
				if(m=='a')
				{
					printf("������ɾ��a���һ��Ԫ�ص�λ��");
					scanf("%d",&i);
					ListDelete_L(La,i,e);
					printf("ɾ����Ԫ��Ϊ%f\n",e);
				}
				else if(m=='b')
				{
					printf("������ɾ��b���һ��Ԫ�ص�λ��:\n");
					scanf("%d",&i);
					ListDelete_L(Lb,i,e);
					printf("ɾ����Ԫ��Ϊ%f\n",e);
				} 
			};continue;
			case 5:{
				char m;
				printf("����������Ҫ���ұ������(a��b)\n");
				scanf("%c",&m);
				if('a'==m)
				{
					printf("��������ҵ�Ԫ��\n");
					scanf("%f",&e);
					i=0;
					ListSearch_L(La,e,i);
					printf("��Ԫ�ص�λ����%d\n",i); 
				}
				else if('b'==m)
				{
					printf("��������ҵ�Ԫ��\n");
					scanf("%f",&e);
					i=0;
					ListSearch_L(Lb,e,i);
					printf("��Ԫ�ص�λ����%d\n",i); 
				} 	 
			};continue;
			case 6:{
				printf("ʵ��ab����ĺϲ�:\n");
				MergeList_L(La,Lb,Lc);
			};continue;
			case 7:{
				printf("������д���ļ���:\n");//����Ϣ¼���ļ��� 
				writeFile(La);
			};continue;
			case 8:{
				printf("���ļ��е��������뵽��Ļ��:\n");//����Ϣ¼���ļ��� 
				PutFile(La);
			};continue;
		}
	} 
	
	
	return 0;
}

