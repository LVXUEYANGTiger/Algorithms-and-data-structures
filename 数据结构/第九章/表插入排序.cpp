#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#define N 8
 
#define SIZE 100 				/* ��̬�������� */
typedef int KeyType; 			/* ����ؼ�������Ϊ���� */
typedef int InfoType; 			/* ������������������� */
typedef struct{
	KeyType key; 				/* �ؼ����� */
	InfoType otherinfo; 		/* ������������������������ж��� */
}RedType; 						/* ��¼���� */

typedef struct{
	RedType rc; 				/* ��¼�� */
	int next; 					/* ָ���� */
}SLNode; 						/* �������� */

typedef struct{
	SLNode r[SIZE]; 			/* 0�ŵ�ԪΪ��ͷ��� */
	int length; 				/* ����ǰ���� */
}SLinkListType; 				/* ��̬�������� */

void CreateSLinkList(SLinkListType &SL){
	int i,p,q; 
	SL.r[0].next=0;
	printf("������Ҫ������˳���ĳ��ȣ�\n");
	scanf("%d",&SL.length);
	printf("������˳����ֵ(�Կո����)\n");
	for(i=1;i<=SL.length;++i){
		scanf("%d",&SL.r[i].rc.key);
		SL.r[i].rc.otherinfo=i;
		q=0;
		p=SL.r[0].next;
		while(SL.r[p].rc.key<=SL.r[i].rc.key)
		{										//��̬��������� 
			q=p;
			p=SL.r[p].next;
		}
		SL.r[i].next=p;						//����ǰ��¼���뾲̬����  
		SL.r[q].next=i;
	}
} 

void Arrange(SLinkListType &SL)
{			//���ݾ�̬����SL�и�����ָ��ֵ������¼λ�ã�ʹ��SL�м�¼���ؼ���  
   			//�ǵݼ�����˳������ 
   int i,p,q;
   SLNode t;
   p=SL.r[0].next;				//pָʾ��һ����¼�ĵ�ǰλ��  
   for(i=1;i<SL.length;++i)
   {						// SL.r[1..i-1]�м�¼�Ѱ��ؼ�����������,��i����¼��SL�еĵ�ǰλ��Ӧ��С��i 
     while(p<i)
       p=SL.r[p].next;				//�ҵ���i����¼������pָʾ����SL�е�ǰλ�� 
     q=SL.r[p].next;				//qָʾ��δ�����ı�β  
     if(p!=i)
     {
       t=SL.r[p];					//������¼��ʹ��i����¼��λ 
       SL.r[p]=SL.r[i];
       SL.r[i]=t;
       SL.r[i].next=p;			//ָ/�����ߵļ�¼��ʹ���Ժ����whileѭ���һ� 
     }
     p=q;						//pָʾ��δ�����ı�β��Ϊ�ҵ�i+1����¼��׼�� 
   }
}

void Sort(SLinkListType L,int adr[])
{	//���adr[1..L.length]��adr[i]Ϊ��̬����L�ĵ�i����С��¼����� 
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
}

void Rearrange(SLinkListType &L,int adr[])
{				//adr������̬����L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼�� 
   				//��adr����L.r��ʹ������. 
   int i,j,k;
   for(i=1;i<L.length;++i)
     if(adr[i]!=i)
     {
       j=i;
       L.r[0]=L.r[i];					//�ݴ��¼(*L).r[i] 
       while(adr[j]!=i)
       {							//����(*L).r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ 
         k=adr[j];
         L.r[j]=L.r[k];
         adr[j]=j;
         j=k;						//��¼����λ 
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
	L2=L1;								//���ƾ�̬����l2��l1��ͬ */
	printf("����ǰ:\n");
	print(L1);
	Arrange(L1);
	printf("L1�����:\n");
	print(L1);
	adr=(int*)malloc((L2.length+1)*sizeof(int));
	Sort(L2,adr);
	for(i=1;i<=L2.length;i++)
		printf("adr[%d]=%d ",i,adr[i]);
	printf("\n");
	Rearrange(L2,adr);
	printf("L2�����:\n");
	print(L2);
	return 0;
}

