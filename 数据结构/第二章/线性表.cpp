#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <cstdlib>
#define LIST_INIT_SIZE 100 //���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10 //���Ա�洢�ռ�ķ�����
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef float ElemType;
typedef int Status;
typedef struct{
	ElemType *elem;//�洢�ռ��ַ 
	Status length;//��ǰ����
	Status listsize;//��ǰ����Ĵ洢���� 
}SqList;
//��������
Status InitList_Sq(SqList &L);//�ձ��ʼ��  
Status ListInsert_Sq(SqList &L,Status i,ElemType e);//���� 
Status ListDelete_Sq(SqList &L,Status i,ElemType &e);//ɾ�� 
Status LocateElem_Sq(SqList L,ElemType e);//���� 
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc); 

Status InitList_Sq(SqList &L)//�ձ��ʼ�� 
{
	//����һ���յ��߱�L 
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(L.elem==NULL)//�ж��ڴ��Ƿ����ʧ�� 
	{
		exit(OVERFLOW);
	}
	L.length=0;//�ձ���Ϊ0 
	L.listsize=LIST_INIT_SIZE;//��ʼ�洢�������ŵ�Ԫ�ظ�����
	return OK; 
}
//����һ��ֵ 
Status ListInsert_Sq(SqList &L,Status i,ElemType e)
{
	ElemType *newbase ,*q,*p;
	if(i<1||i>L.length)//�ж�iֵ�Ƿ�Ϸ� 
	{
		return ERROR;
	}
	if(L.length>=L.listsize)//�жϴ洢�ռ��Ƿ����� 
	{
		newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL)
		{
			exit(OVERFLOW);//�ж��Ƿ����·���ɹ� 
		}
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;
	}
	q=&(L.elem[i-1]);//qΪ����λ��
	for(p = &(L.elem[L.length-1]);p>=q;--p)//pΪ���һ��Ԫ�ص�λ�� 
	{
		*(p+1)=*p;//����Ԫ������		
	} 
	*q = e;
	++L.length;
	return  OK;	
} 
//ɾ��һ��ֵ
Status ListDelete_Sq(SqList &L,Status i,ElemType &e)
{
	ElemType *p,*q; 
	//��˳�����ɾ����i��Ԫ�ز���e���ؽ��
	if((i<1)||(i>L.length))//�ж�iֵ�Ƿ�Ϸ� 
	{
		return ERROR;
	} 
	p = &(L.elem[i-1]);//pΪɾ����λ�� 
	e = *p;//��ɾ����Ԫ�ص�ֵ��e 
	q = L.elem+L.length-1; //��βԪ�ص�λ�� 
	for(++p;p<=q;++p)
	{
		*(p-1)=*p;//��ɾ����Ԫ��֮������ 
	}
	--L.length;
	return OK; 
}
//�����Ա���в���
Status LocateElem_Sq(SqList L,ElemType e)
{
	//��˳����в�ѯ��һ�������ж�����������Ԫ��
	//��Ԫ�ش����򷵻�����λ�򣬷����򷵻�0
	Status i;//i�ĳ�ʼֵΪ��һ��Ԫ�ص�λ��
	i=1; 
	while(i<=L.length&&L.elem[i-1]!=e)
	{
		++i;
	}
	if(i<=L.length)
	{
		return i;
	}
	else
	{
		return 0;
	}
}
//��a,b�����������ϲ�C
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc)
{
	ElemType *pa,*pb,*pc,*pa_last,*pb_last;
	//��֪���Ա��Ԫ�ذ�����Ԫ������
	//�鲢La��Lb�õ��±�Lc
	pa=La.elem;
	pb=Lb.elem;
	Lc.listsize=Lc.length=La.length+Lb.length;
	pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
	if(!Lc.elem)//�ж��Ƿ����ʧ�� 
	{
		exit(OVERFLOW); 
	}
	pa_last=La.elem+La.length-1;
	pb_last=Lb.elem+Lb.length-1;
	while((pa<=pa_last)&&(pb<=pb_last))
	{
		if(*pa<=*pb)
		{
			*pc++=*pa++;
		}
		else
		{
			*pc++=*pb++;
		}
	}
	while(pa<=pa_last)//��a��ʣ���Ԫ�ظ��Ƶ�c�� 
	{
		*pc++=*pa++;
	}
	while(pb<=pb_last)//��b��ʣ���Ԫ�ظ��Ƶ�c�� 
	{
		*pc++=*pb++;
	}
}
int main(int argc, char** argv) 
{
	SqList La,Lb,Lc;//����3����
	ElemType e;
	Status i=0,a,b,flag; 
	InitList_Sq(La);//��ʼ���ձ�a 
	InitList_Sq(Lb);//��ʼ���ձ�b
	InitList_Sq(Lc);//��ʼ���ձ�c
	
	//��ab��ֵ 
	printf("����������Ҫ��a�������Ԫ�ظ���:\n"); 
	scanf("%d",&a);
	La.length=a;
	for(i=0;i<a;i++)
	{
		scanf("%f",&La.elem[i]);
	}
	printf("����������Ҫ��b�������Ԫ�ظ���:\n"); 
	scanf("%d",&b);
	Lb.length=b;
	for(i=0;i<b;i++)
	{
		scanf("%f",&Lb.elem[i]);
	}
	
	//����һ��ֵ
	printf("������������a������Ԫ��λ�ú�Ԫ��:\n");
	La.length=(a+1)*sizeof(ElemType);
	scanf("%d%f",&i,&e); 
	ListInsert_Sq(La,i,e);
	for(i=0;i<a+1;i++)
	{
		printf("%4.2f ",La.elem[i]);
	}
	
	printf("\n");
	//ɾ��һ��ֵ
	printf("������������a����ɾ����Ԫ��λ��:\n");
	scanf("%d",&i); 
	La.length=(a-1)*sizeof(ElemType);
	ListDelete_Sq(La,i,e);
	for(i=0;i<a;i++)
	{
		printf("%4.2f ",La.elem[i]);
	}
	printf("\n");
	printf("ɾ����Ԫ��Ϊ%f:\n",e);
	
	//�����Ա���в���
	printf("������������a�������ҵ���Ԫ��:\n");
	scanf("%f",&e); 
	i=LocateElem_Sq(La,e);
	printf("Ԫ�ص�λ��Ϊ%d\n",i);
	printf("\n");
		
	//��a,b�����������ϲ�C	
	MergeList_Sq(La,Lb,Lc);
	printf("�ϳ�c��Ϊ:\n");
	for(i=0;i<a+b;i++)
	{	
		printf("%4.2f ",Lc.elem[i]);	
	}
	return 0;
}
