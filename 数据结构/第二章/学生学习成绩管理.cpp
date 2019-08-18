#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student{
    long number;//ѧ�� 
    char name[10];//���� 
    char sex[3];//�Ա� 
    int age;//���� 
    float Chinese;//���� 
    float Math;//��ѧ 
    float English;//Ӣ�� 
    float sum;//��� 
    float average;//ƽ���� 
    struct student *next;
}Stu,*StuList;
//��������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------- 
StuList   creat(void);//�ܴ��� 
StuList   creat1(void);//���̽��� 
StuList   creat2(void);//��ȡ�ļ� 
StuList   changes(StuList head);//���� 
StuList   modify(StuList head,long num);//�޸� 
StuList   del(StuList head,long num);//ɾ�� 
StuList   insert(StuList head,StuList stud);//���� 
StuList   input(StuList head,StuList p1);//¼ȡ��Ϣ 
void sort(StuList head);//���� 
void total_average_sort(StuList head);//���ܷ����� 
void chinese_sort(StuList head);//���������� 
void math_sort(StuList head);//��ѧ���� 
void english_sort(StuList head);//Ӣ������ 
void print(StuList head);//���� 
void Statistics(StuList head);//ͳ�� 
void search(StuList head);//���� 
void numsearch(StuList head,long num);//ѧ�Ų��� 
void namesearch(StuList head,char name[]);//���ֲ��� 
int n;//����ѧ�����ܸ��� 
//----------------------------------------------------------------------------------------------------------------------------------------------------------------- 
StuList creat(void)//�ܴ��� 
{
	StuList   head;
	int k;
	head=NULL;
	printf("����ѧ����Ϣ�ķ�ʽ��1.�Ӽ�������   2.���ļ�����   0.�˳�\n");
	printf("��ѡ��");
	scanf("%d",&k);
	switch(k)
	{
		case 1:head=creat1();break;
		case 2:head=creat2();break;
		case 0:break;
		default:printf("����������������룡\n");
	}
	return head;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   creat1(void)//�Ӽ��̽��� 
{
    StuList head,p1;
    n=0;
    p1=(StuList)malloc(sizeof(Stu));//����һ���µĽڵ� 
    printf("������ѧ����Ϣ��\n");
	head=NULL;
    p1=input(head,p1);//��p1ָ���Ѿ���ֵ�Ľṹ�� 
    while(p1->number!=0)
	{
        head=insert(head,p1);
        p1=(StuList)malloc(sizeof(Stu));
        p1=input(head,p1);
	}
    return head;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   creat2(void)//���ļ���ȡ 
{
	FILE *fp;
	StuList head,p1;
	n=0;
	head=NULL;
	if((fp=fopen("1.txt","r"))==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
	    exit(0);
	}
	p1=(StuList)malloc(sizeof(Stu));
	while(!feof(fp))//����ļ��Ƿ����ļ�ĩβ���ļ�����ĩβ��Ϊ1����Ϊ0 
	{
		fscanf(fp,"%ld%s%s%d%f%f%f%f%f\n",&p1->number,p1->name,p1->sex,&p1->age,&p1->Chinese,&p1->Math,&p1->English,&p1->sum,&p1->average);
		head=insert(head,p1);
		p1=(StuList)malloc(sizeof(Stu));
	};
	fclose(fp);
	return head;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   input(StuList head,StuList p1)//¼ȡ��Ϣ�ĺ��� 
{
	int i,f,k;
	StuList   p2;
    loop:printf("ѧ�ţ�Ϊ����������0ʱ������һ����:");
    scanf("%ld",&p1->number);
    if(p1->number<0)
	{
        printf("ѧ�Ų���Ϊ���������������룡\n");
        goto loop;
	}
	else{
		if(p1->number==0)
           return p1; 
		else
		{
			p2=head;
			f=0;
			for(i=1;i<=n;i++)
			{
				if(p1->number==p2->number)
				{
					f=1;
					break;
				}
				p2=p2->next;
			}
		}
       if(f)
	   {
	   		printf("ѧ�Ų����ظ������������룡\n");
			goto loop;
		}
	}
    printf("����:");
    scanf("%s",p1->name);
    loop1:printf("�Ա�:  1.��   2.Ů\n");
	printf("��ѡ���Ա�:");
    scanf("%d",&k);
	switch(k)
	{
		case 1:strcpy(p1->sex,"��");break;
		case 2:strcpy(p1->sex,"Ů");break;
		default:printf("�Ա�ֻ���ǡ��С���Ů�������������룡\n");
		goto loop1;
	}
    printf("����:");
    scanf("%d",&p1->age);
    while(p1->age<0||p1->age>120)
	{
	    printf("����������䲻����ʵ����������������룡\n");
		printf("����:");
	    scanf("%d",&p1->age);
	}
    printf("���ĳɼ�:");
    scanf("%f",&p1->Chinese);
	while(p1->Chinese<0||p1->Chinese>100)
	{
		printf("����������ĳɼ�������ʵ����������������룡\n");
		printf("���ĳɼ�:");
		scanf("%f",&p1->Chinese);
	}
    printf("��ѧ�ɼ�:");
    scanf("%f",&p1->Math);
	while(p1->Math<0||p1->Math>100)
	{
		printf("���������ѧ�ɼ�������ʵ����������������룡\n");
		printf("��ѧ�ɼ�:");
		scanf("%f",&p1->Math);
	}
    printf("Ӣ��ɼ�:");
    scanf("%f",&p1->English);
	while(p1->English<0||p1->English>100)
	{
		printf("�������Ӣ��ɼ�������ʵ����������������룡\n");
		printf("Ӣ��ɼ�:");
		scanf("%f",&p1->English);
	}
    p1->sum=p1->Chinese+p1->Math+p1->English;
    p1->average=p1->sum/3;
    return p1;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   insert(StuList   head,StuList   stud)
{
    StuList p0,p1,p2;
    p1=head;
    p0=stud;
    if(head==NULL)
	{
		head=p0;p0->next=NULL;
	}
    else
	{
		while((p0->number>p1->number)&&(p1->next!=NULL))
		{
	        p2=p1;
	        p1=p1->next;
		}
	    if(p0->number<=p1->number)
		{
	        if(head==p1)
	        {
	        	head=p0;
			}
	        else 
	        {
	        	p2->next=p0;
	        	p0->next=p1;
			}
				
		}
	    else
		{
	        p1->next=p0;
			p0->next=NULL;
		}
	}
    n=n+1;
    return head;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void search(StuList head)
{
    int k;
    long num;
    char name[10];
    if(n==0)
	{
		printf("���ݿ�Ϊ�գ�û��ѧ���ļ�¼��\n");
		return;
	}
    else{
        do{
            printf("1. ��ѧ�Ų���    2. ����������    0. ������һ��\n");
            printf("��ѡ��:");
            scanf("%d",&k);
            switch(k)
			{
            case 1:do{
                     printf("ѧ�ţ�Ϊ����������0ʱ������ѧ�Ų��ң�:");
                     scanf("%ld",&num);
                     if(num>0)
                          numsearch(head,num);
					 if(num<0)
                          printf("�������������ѡ��\n");
				   }while(num!=0);
                   break;
            case 2:do{
				     printf("����������0ʱ�������������ң�:");
				     scanf("%s",name);
					 printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
                     namesearch(head,name);
				   }while(strcmp(name,"0")!=0);
                   break;
            case 0:break;
            default:printf("�������������ѡ��\n");
			}
		}while(k!=0);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void numsearch(StuList   head,long num)
{
    StuList   p1;
    p1=head;
    while(p1!=NULL)
	{
        if(num==p1->number)
		{
			printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
            printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
			return;
		}
        p1=p1->next;
	}
    printf("û���ҵ���Ҫ���ҵ�ѧ����Ϣ��\n");
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void namesearch(StuList   head,char name[])
{
	int a=1;
    StuList   p1;
    p1=head;
    while(p1!=NULL)
	{
        if(strcmp(name,p1->name)==0)
		{
			printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
			a=0;
		}
        	p1=p1->next;
	}
	if(a)
	{
		printf("û���ҵ���Ҫ���ҵ�ѧ����Ϣ��\n");
	} 
        
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   changes(StuList   head)
{
    StuList   p1;
    int k;
    long num;
    do{
    printf("1. �޸�    2. ɾ��     3. ����    0. ������һ��\n");
    printf("��ѡ��:");
    scanf("%d",&k);
    switch(k)
    {
    case 1:if(n==0)
		{
	        printf("���ݿ�Ϊ�գ�û��ѧ���ļ�¼��\n");break;
		}
        else
		do{
              printf("������ѧ����ѧ�ţ�ѧ��ӦΪ����������0ʱ�����޸����ݣ�:");
              scanf("%ld",&num);
              if(num>0)
			  head=modify(head,num);
			  if(num<0)
                   printf("ѧ�Ų���Ϊ���������������룡\n");
      }while(num!=0);
      break;
    case 2:if(n==0)
		{
			printf("���ݿ�Ϊ�գ�û��ѧ����Ϣ��\n");
			break;
		}
        else
			do{
            printf("������Ҫɾ����ѧ����ѧ�ţ�ѧ��ӦΪ����������0ʱ����ɾ��Ԫ�أ�:");
            scanf("%ld",&num);
            if(num>0)
			head=del(head,num);
		    if(num<0)
                   printf("ѧ�Ų���Ϊ���������������룡\n");
     }while(num!=0);
     break;
     case 3:printf("������ѧ����Ϣ��\n");
            p1=(StuList )malloc(sizeof(Stu));
            p1=input(head,p1);
            while(p1->number!=0)
			{
				head=insert(head,p1);
	            print(head);
	            printf("������ѧ����Ϣ��\n");
	            p1=(StuList )malloc(sizeof(Stu));
	            p1=input(head,p1);
			}
            break;
     case 0:break;
     default:printf("����������������룡\n");
	}
	}while(k!=0);
    return(head);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   modify(StuList   head,long num)
{
    StuList   p1;
    int k,m;
    p1=head;
    while(p1->next!=NULL)
	{
        if(p1->number==num)
            break;
        p1=p1->next;
	}
    if(p1->number==num)
	{
        do{
        printf("1.����   2.�Ա�   3.����   4.���ĳɼ�    5.��ѧ�ɼ�   6.Ӣ��ɼ�   0.������һ��\n");
        printf("��ѡ��:");
        scanf("%d",&k);
        switch(k)
		{
            case 1:printf("����:");scanf("%s",p1->name);printf("�޸ĳɹ���\n");break;
            case 2:loop2:printf("�Ա�:  1.��   2.Ů\n");
	               printf("��ѡ���Ա�:");
                   scanf("%d",&m);
	               switch(m)
				   {
	                case 1:strcpy(p1->sex,"��");break;
	                case 2:strcpy(p1->sex,"Ů");break;
	                default:printf("�Ա�ֻ���ǡ��С���Ů�������������룡\n");goto loop2;}
				   printf("�޸ĳɹ���\n");
				   break;
            case 3:printf("����:");
                   scanf("%d",&p1->age);
                   while(p1->age<0||p1->age>120)
				   {
                        printf("����������䲻����ʵ����������������룡\n");
	                    printf("����:");
                        scanf("%d",&p1->age);
				   }
				   printf("�޸ĳɹ���\n");
				   break;
            case 4:printf("���ĳɼ�:");
                   scanf("%f",&p1->Chinese);
	               while(p1->Chinese<0||p1->Chinese>100)
				   {
		                 printf("����������ĳɼ�������ʵ����������������룡\n");
		                 printf("���ĳɼ�:");
		                 scanf("%f",&p1->Chinese);
					}
				         p1->sum=p1->Chinese+p1->Math+p1->English;
                         p1->average=p1->sum/3;
						 printf("�޸ĳɹ���\n");
						 break;
            case 5:printf("��ѧ�ɼ�:");
                   scanf("%f",&p1->Math);
	               while(p1->Math<0||p1->Math>100){
		                 printf("���������ѧ�ɼ�������ʵ����������������룡\n");
		                 printf("��ѧ�ɼ�:");
		                 scanf("%f",&p1->Math);}
				         p1->sum=p1->Chinese+p1->Math+p1->English;
                         p1->average=p1->sum/3;
						 printf("�޸ĳɹ���\n");
						 break;
            case 6:printf("Ӣ��ɼ�:");
                   scanf("%f",&p1->English);
	               while(p1->English<0||p1->English>100){
		           printf("�������Ӣ��ɼ�������ʵ����������������룡\n");
		           printf("Ӣ��ɼ�:");
		           scanf("%f",&p1->English);}
				   p1->sum=p1->Chinese+p1->Math+p1->English;
                   p1->average=p1->sum/3;
				   printf("�޸ĳɹ���\n");break;
            case 0:break;
            default:printf("�������������ѡ��\n");
		}
		}while(k!=0);
		print(head);
	}
    else
        printf("û���ҵ���Ҫ�޸ĵ�ѧ������Ϣ��\n");
    return(head);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void total_average_sort(StuList   head)
{
	StuList   p1,p2;
	int j=0;
	float max,k=301;
	printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
	do{
		max=0;
		for(p1=head;p1;p1=p1->next)
			if(p1->sum>max&&p1->sum<k)
			{
				max=p1->sum;
				p2=p1;
			}
	    k=max;
		for(p1=p2;p1;p1=p1->next)
			if(p1->sum==max)
			{
				printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
				j++;
			}
	}while(j<n);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void chinese_sort(StuList   head)
{
	int j=0;
	float k=101,max;
	StuList   p1,p2;
	printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
	do{
		max=0;
		for(p1=head;p1;p1=p1->next)
			if(p1->Chinese>max&&p1->Chinese<k)
			{
				max=p1->Chinese;
			    p2=p1;
			}
		k=max;
		for(p1=p2;p1;p1=p1->next)
			if(p1->Chinese==max)
			{
				printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
				j++;
			}
	}while(j<n);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void math_sort(StuList   head)
{
	int j=0;
	float k=101,max;
	StuList   p1,p2;
	printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
	do{
		max=0;
		for(p1=head;p1;p1=p1->next)
			if(p1->Math>max&&p1->Math<k){
				max=p1->Math;
				p2=p1;}
		k=max;
		for(p1=p2;p1;p1=p1->next)
			if(p1->Math==max){
				printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
				j++;}
	}while(j<n);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void english_sort(StuList   head)
{
	int j=0;
	float k=101,max;
	StuList   p1,p2;
	printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
	do{
		max=0;
		for(p1=head;p1;p1=p1->next)
			if(p1->English>max&&p1->English<k){
				max=p1->English;
			    p2=p1;}
		k=max;
		for(p1=p2;p1;p1=p1->next)
			if(p1->English==max){
				printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
				j++;}
	}while(j<n);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void sort(StuList   head)
{
	int k;
    if(n==0)
	{	
		printf("���ݿ�Ϊ�գ�û��ѧ����¼��\n");
		return;
	}
	do{
	   printf("1.��ѧ������   2.���ֺܷ�ƽ��������   3.�����ĳɼ�����   4.����ѧ�ɼ�����   5.��Ӣ��ɼ�����    0.������һ��\n");
       printf("��ѡ��:");
	   scanf("%d",&k);
	   switch(k)
	   {
	   case 1:print(head);break;
	   case 2:total_average_sort(head);break;
	   case 3:chinese_sort(head);break;
	   case 4:math_sort(head);break;
	   case 5:english_sort(head);break;
	   case 0:break;
	   default:printf("����������������룡\n");
	   }
	}while(k!=0);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   del(StuList   head,long num)
{
    StuList   p1,p2;
    if(head==NULL)
	{	
		printf("���ݿ�Ϊ�գ�û��ѧ����¼�� \n");
		goto end;
	}
    p1=head;
    while(num!=p1->number&&p1->next!=NULL)
	{
        p2=p1;p1=p1->next;
	}
    if(num==p1->number)
	{
        if(p1==head)
		{
			head=p1->next;
			printf("ɾ���ɹ���\n");
		}
        else 
		{
			p2->next=p1->next;
			printf("ɾ���ɹ���\n");
		}
        n=n-1;
		print(head);
	}
    else printf("û���ҵ���Ҫɾ����ѧ����Ϣ��\n",num);
    end:;
    return head;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void Statistics(StuList   head)
{
    StuList   p1;
    int i,c=0,m=0,e=0;
    float cmax=0,mmax=0,emax=0,summax=0,averagemax=0;
	if(n==0)
	{
		printf("���ݿ�Ϊ�գ�û��ѧ������Ϣ��\n");
		return;
	}
    p1=head;
    for(i=1;i<=n;i++)
	{
        if(p1->Chinese>=cmax)
            cmax=p1->Chinese;
        if(p1->Math>=mmax)
            mmax=p1->Math;
        if(p1->English>=emax)
            emax=p1->English;
        if(p1->sum>=summax)
            summax=p1->sum;
        if(p1->average>=averagemax)
            averagemax=p1->average;
        if(p1->Chinese<60)
            c++;
        if(p1->Math<60)
            m++;
        if(p1->English<60)
            e++;
		p1=p1->next;
	}
    printf("�ܳɼ���߷�:%5.1f\n",summax);
    printf("ƽ�ɼ���߷�:%5.1f\n",averagemax);
    printf("���ĳɼ���߷�:%5.1f\n",cmax);
    printf("��ѧ�ɼ���߷�:%5.1f\n",mmax);
    printf("Ӣ��ɼ���߷�:%5.1f\n",emax);
    printf("���ĳɼ�û�м��������:%d\n",c);
    printf("��ѧ�ɼ�û�м��������:%d\n",m);
    printf("Ӣ��ɼ�û�м��������:%d\n",e);
    printf("\n");
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void print(StuList   head)
{
    StuList   p1;
	if(n==0)
	{
		printf("���ݿ�Ϊ�գ�û��ѧ����Ϣ��\n");
		return;
	}
    printf("\n���ڵ�%d��ѧ����¼Ϊ:\n",n);
    p1=head;
    if(head!=NULL)
	{
		printf("ѧ��\t\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
        do {
            printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
            p1=p1->next;
		}while(p1!=NULL);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void save(StuList   head)
{
	FILE *fp;
	StuList   p1;
	if(n==0)
	{
		printf("�㻹û�н������ݿ⣡���Ƚ������ݿ⣡\n");
		return;
	}
	if((fp=fopen("1.txt","w+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		exit(0);
	}
	for(p1=head;p1!=NULL;p1=p1->next)
		fprintf(fp,"%ld\t%s\t%s\t%d\t%5.1f\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
	printf("����ɹ���\n");
	fclose(fp);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    int choice;
    StuList   head;
	head=NULL;
    do{
   
        printf("*******************************************************************************\n");
        printf("^_^_^_^_^_^_^_^_^_^_^_^_^_^��ӭ����ѧ���ɼ�����ϵͳ!^_^_^_^_^_^_^_^_^_^_^_^_^_^\n");
        printf("                                                                               \n");
        printf("                          ѧ���ɼ�����ϵͳ�Ļ������ܣ�                         \n");
        printf("                                   1. �½�;                                    \n");
        printf("                                   2. ����;                                    \n");
        printf("                                   3. ����;                                    \n");
		printf("                                   4. ����;                                    \n");
        printf("                                   5. ͳ��;                                    \n");
        printf("                                   6. ��ʾ;                                    \n");
		printf("                                   7. ����;                                    \n");
		printf("                                   0. ����;                                    \n");
        printf("                                                                               \n");
        printf("                               ����ѡ�񣬻س�ȷ��!                             \n");
        printf("                                                                               \n");
        printf("^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n");
        printf("*******************************************************************************\n");
        printf("��ѡ��");
        scanf("%d",&choice);
        while(getchar()!='\n');
        switch(choice)
		{
            case 1:head=creat();print(head);break;
            case 2:search(head);break;
            case 3:head=changes(head);break;
			case 4:sort(head);break;
            case 5:Statistics(head);break;
            case 6:print(head);break;
			case 7:save(head);break;
            case 0:break;
            default:printf("�������������ѡ��!\n");
		}
	}while(choice!=0);
}

