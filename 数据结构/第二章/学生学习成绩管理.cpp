#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student{
    long number;//学号 
    char name[10];//姓名 
    char sex[3];//性别 
    int age;//年龄 
    float Chinese;//语文 
    float Math;//数学 
    float English;//英语 
    float sum;//求和 
    float average;//平均分 
    struct student *next;
}Stu,*StuList;
//函数声明
//---------------------------------------------------------------------------------------------------------------------------------------------------------------- 
StuList   creat(void);//总创建 
StuList   creat1(void);//键盘接收 
StuList   creat2(void);//读取文件 
StuList   changes(StuList head);//更新 
StuList   modify(StuList head,long num);//修改 
StuList   del(StuList head,long num);//删除 
StuList   insert(StuList head,StuList stud);//插入 
StuList   input(StuList head,StuList p1);//录取信息 
void sort(StuList head);//排序 
void total_average_sort(StuList head);//求总分排序 
void chinese_sort(StuList head);//求语文排序 
void math_sort(StuList head);//数学排序 
void english_sort(StuList head);//英语排序 
void print(StuList head);//遍历 
void Statistics(StuList head);//统计 
void search(StuList head);//查找 
void numsearch(StuList head,long num);//学号查找 
void namesearch(StuList head,char name[]);//名字查找 
int n;//计算学生的总个数 
//----------------------------------------------------------------------------------------------------------------------------------------------------------------- 
StuList creat(void)//总创建 
{
	StuList   head;
	int k;
	head=NULL;
	printf("输入学生信息的方式：1.从键盘输入   2.从文件读入   0.退出\n");
	printf("请选择：");
	scanf("%d",&k);
	switch(k)
	{
		case 1:head=creat1();break;
		case 2:head=creat2();break;
		case 0:break;
		default:printf("输入错误，请重新输入！\n");
	}
	return head;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   creat1(void)//从键盘接入 
{
    StuList head,p1;
    n=0;
    p1=(StuList)malloc(sizeof(Stu));//生成一个新的节点 
    printf("请输入学生信息！\n");
	head=NULL;
    p1=input(head,p1);//让p1指向已经赋值的结构体 
    while(p1->number!=0)
	{
        head=insert(head,p1);
        p1=(StuList)malloc(sizeof(Stu));
        p1=input(head,p1);
	}
    return head;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   creat2(void)//从文件读取 
{
	FILE *fp;
	StuList head,p1;
	n=0;
	head=NULL;
	if((fp=fopen("1.txt","r"))==NULL)
	{
		printf("打开文件失败！\n");
	    exit(0);
	}
	p1=(StuList)malloc(sizeof(Stu));
	while(!feof(fp))//检测文件是否处在文件末尾如文件处在末尾则为1否则为0 
	{
		fscanf(fp,"%ld%s%s%d%f%f%f%f%f\n",&p1->number,p1->name,p1->sex,&p1->age,&p1->Chinese,&p1->Math,&p1->English,&p1->sum,&p1->average);
		head=insert(head,p1);
		p1=(StuList)malloc(sizeof(Stu));
	};
	fclose(fp);
	return head;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   input(StuList head,StuList p1)//录取信息的函数 
{
	int i,f,k;
	StuList   p2;
    loop:printf("学号（为整数，输入0时返回上一级）:");
    scanf("%ld",&p1->number);
    if(p1->number<0)
	{
        printf("学号不能为负数，请重新输入！\n");
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
	   		printf("学号不能重复，请重新输入！\n");
			goto loop;
		}
	}
    printf("姓名:");
    scanf("%s",p1->name);
    loop1:printf("性别:  1.男   2.女\n");
	printf("请选择性别:");
    scanf("%d",&k);
	switch(k)
	{
		case 1:strcpy(p1->sex,"男");break;
		case 2:strcpy(p1->sex,"女");break;
		default:printf("性别只能是“男”或“女”，请重新输入！\n");
		goto loop1;
	}
    printf("年龄:");
    scanf("%d",&p1->age);
    while(p1->age<0||p1->age>120)
	{
	    printf("你输入的年龄不符合实际情况，请重新输入！\n");
		printf("年龄:");
	    scanf("%d",&p1->age);
	}
    printf("语文成绩:");
    scanf("%f",&p1->Chinese);
	while(p1->Chinese<0||p1->Chinese>100)
	{
		printf("你输入的语文成绩不符合实际情况，请重新输入！\n");
		printf("语文成绩:");
		scanf("%f",&p1->Chinese);
	}
    printf("数学成绩:");
    scanf("%f",&p1->Math);
	while(p1->Math<0||p1->Math>100)
	{
		printf("你输入的数学成绩不符合实际情况，请重新输入！\n");
		printf("数学成绩:");
		scanf("%f",&p1->Math);
	}
    printf("英语成绩:");
    scanf("%f",&p1->English);
	while(p1->English<0||p1->English>100)
	{
		printf("你输入的英语成绩不符合实际情况，请重新输入！\n");
		printf("英语成绩:");
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
		printf("数据库为空，没有学生的记录！\n");
		return;
	}
    else{
        do{
            printf("1. 按学号查找    2. 按姓名查找    0. 返回上一级\n");
            printf("请选择:");
            scanf("%d",&k);
            switch(k)
			{
            case 1:do{
                     printf("学号（为整数，输入0时跳出按学号查找）:");
                     scanf("%ld",&num);
                     if(num>0)
                          numsearch(head,num);
					 if(num<0)
                          printf("输入错误，请重新选择！\n");
				   }while(num!=0);
                   break;
            case 2:do{
				     printf("姓名（输入0时跳出按姓名查找）:");
				     scanf("%s",name);
					 printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
                     namesearch(head,name);
				   }while(strcmp(name,"0")!=0);
                   break;
            case 0:break;
            default:printf("输入错误，请重新选择！\n");
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
			printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
            printf("%ld\t%s\t%s\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
			return;
		}
        p1=p1->next;
	}
    printf("没有找到你要查找的学生信息！\n");
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
		printf("没有找到你要查找的学生信息！\n");
	} 
        
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   changes(StuList   head)
{
    StuList   p1;
    int k;
    long num;
    do{
    printf("1. 修改    2. 删除     3. 插入    0. 返回上一级\n");
    printf("请选择:");
    scanf("%d",&k);
    switch(k)
    {
    case 1:if(n==0)
		{
	        printf("数据库为空，没有学生的记录！\n");break;
		}
        else
		do{
              printf("请输入学生的学号（学号应为整数，输入0时跳出修改数据）:");
              scanf("%ld",&num);
              if(num>0)
			  head=modify(head,num);
			  if(num<0)
                   printf("学号不能为负数，请重新输入！\n");
      }while(num!=0);
      break;
    case 2:if(n==0)
		{
			printf("数据库为空，没有学生信息！\n");
			break;
		}
        else
			do{
            printf("请输入要删除的学生的学号（学号应为整数，输入0时跳出删除元素）:");
            scanf("%ld",&num);
            if(num>0)
			head=del(head,num);
		    if(num<0)
                   printf("学号不能为负数，请重新输入！\n");
     }while(num!=0);
     break;
     case 3:printf("请输入学生信息！\n");
            p1=(StuList )malloc(sizeof(Stu));
            p1=input(head,p1);
            while(p1->number!=0)
			{
				head=insert(head,p1);
	            print(head);
	            printf("请输入学生信息！\n");
	            p1=(StuList )malloc(sizeof(Stu));
	            p1=input(head,p1);
			}
            break;
     case 0:break;
     default:printf("输入错误，请重新输入！\n");
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
        printf("1.姓名   2.性别   3.年龄   4.语文成绩    5.数学成绩   6.英语成绩   0.返回上一级\n");
        printf("请选择:");
        scanf("%d",&k);
        switch(k)
		{
            case 1:printf("姓名:");scanf("%s",p1->name);printf("修改成功！\n");break;
            case 2:loop2:printf("性别:  1.男   2.女\n");
	               printf("请选择性别:");
                   scanf("%d",&m);
	               switch(m)
				   {
	                case 1:strcpy(p1->sex,"男");break;
	                case 2:strcpy(p1->sex,"女");break;
	                default:printf("性别只能是“男”或“女”，请重新输入！\n");goto loop2;}
				   printf("修改成功！\n");
				   break;
            case 3:printf("年龄:");
                   scanf("%d",&p1->age);
                   while(p1->age<0||p1->age>120)
				   {
                        printf("你输入的年龄不符合实际情况，请重新输入！\n");
	                    printf("年龄:");
                        scanf("%d",&p1->age);
				   }
				   printf("修改成功！\n");
				   break;
            case 4:printf("语文成绩:");
                   scanf("%f",&p1->Chinese);
	               while(p1->Chinese<0||p1->Chinese>100)
				   {
		                 printf("你输入的语文成绩不符合实际情况，请重新输入！\n");
		                 printf("语文成绩:");
		                 scanf("%f",&p1->Chinese);
					}
				         p1->sum=p1->Chinese+p1->Math+p1->English;
                         p1->average=p1->sum/3;
						 printf("修改成功！\n");
						 break;
            case 5:printf("数学成绩:");
                   scanf("%f",&p1->Math);
	               while(p1->Math<0||p1->Math>100){
		                 printf("你输入的数学成绩不符合实际情况，请重新输入！\n");
		                 printf("数学成绩:");
		                 scanf("%f",&p1->Math);}
				         p1->sum=p1->Chinese+p1->Math+p1->English;
                         p1->average=p1->sum/3;
						 printf("修改成功！\n");
						 break;
            case 6:printf("英语成绩:");
                   scanf("%f",&p1->English);
	               while(p1->English<0||p1->English>100){
		           printf("年输入的英语成绩不符合实际情况，请重新输入！\n");
		           printf("英语成绩:");
		           scanf("%f",&p1->English);}
				   p1->sum=p1->Chinese+p1->Math+p1->English;
                   p1->average=p1->sum/3;
				   printf("修改成功！\n");break;
            case 0:break;
            default:printf("输入错误，请重新选择！\n");
		}
		}while(k!=0);
		print(head);
	}
    else
        printf("没有找到你要修改的学生的信息！\n");
    return(head);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void total_average_sort(StuList   head)
{
	StuList   p1,p2;
	int j=0;
	float max,k=301;
	printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
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
	printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
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
	printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
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
	printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
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
		printf("数据库为空，没有学生记录！\n");
		return;
	}
	do{
	   printf("1.按学号排序   2.按总分和平均分排序   3.按语文成绩排序   4.按数学成绩排序   5.按英语成绩排序    0.返回上一级\n");
       printf("请选择:");
	   scanf("%d",&k);
	   switch(k)
	   {
	   case 1:print(head);break;
	   case 2:total_average_sort(head);break;
	   case 3:chinese_sort(head);break;
	   case 4:math_sort(head);break;
	   case 5:english_sort(head);break;
	   case 0:break;
	   default:printf("输入错误，请重新输入！\n");
	   }
	}while(k!=0);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
StuList   del(StuList   head,long num)
{
    StuList   p1,p2;
    if(head==NULL)
	{	
		printf("数据库为空，没有学生记录！ \n");
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
			printf("删除成功！\n");
		}
        else 
		{
			p2->next=p1->next;
			printf("删除成功！\n");
		}
        n=n-1;
		print(head);
	}
    else printf("没有找到你要删除的学生信息！\n",num);
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
		printf("数据库为空，没有学生的信息！\n");
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
    printf("总成绩最高分:%5.1f\n",summax);
    printf("平成绩最高分:%5.1f\n",averagemax);
    printf("语文成绩最高粉:%5.1f\n",cmax);
    printf("数学成绩最高分:%5.1f\n",mmax);
    printf("英语成绩最高分:%5.1f\n",emax);
    printf("语文成绩没有及格的人数:%d\n",c);
    printf("数学成绩没有及格的人数:%d\n",m);
    printf("英语成绩没有及格的人数:%d\n",e);
    printf("\n");
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void print(StuList   head)
{
    StuList   p1;
	if(n==0)
	{
		printf("数据库为空，没有学生信息！\n");
		return;
	}
    printf("\n现在的%d个学生记录为:\n",n);
    p1=head;
    if(head!=NULL)
	{
		printf("学号\t\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\n");
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
		printf("你还没有建立数据库！请先建立数据库！\n");
		return;
	}
	if((fp=fopen("1.txt","w+"))==NULL)
	{
		printf("不能打开文件！\n");
		exit(0);
	}
	for(p1=head;p1!=NULL;p1=p1->next)
		fprintf(fp,"%ld\t%s\t%s\t%d\t%5.1f\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n",p1->number,p1->name,p1->sex,p1->age,p1->Chinese,p1->Math,p1->English,p1->sum,p1->average);
	printf("保存成功！\n");
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
        printf("^_^_^_^_^_^_^_^_^_^_^_^_^_^欢迎来到学生成绩管理系统!^_^_^_^_^_^_^_^_^_^_^_^_^_^\n");
        printf("                                                                               \n");
        printf("                          学生成绩管理系统的基本功能：                         \n");
        printf("                                   1. 新建;                                    \n");
        printf("                                   2. 查找;                                    \n");
        printf("                                   3. 更新;                                    \n");
		printf("                                   4. 排序;                                    \n");
        printf("                                   5. 统计;                                    \n");
        printf("                                   6. 显示;                                    \n");
		printf("                                   7. 保存;                                    \n");
		printf("                                   0. 跳出;                                    \n");
        printf("                                                                               \n");
        printf("                               按键选择，回车确定!                             \n");
        printf("                                                                               \n");
        printf("^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n");
        printf("*******************************************************************************\n");
        printf("请选择：");
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
            default:printf("输入错误，请重新选择!\n");
		}
	}while(choice!=0);
}

