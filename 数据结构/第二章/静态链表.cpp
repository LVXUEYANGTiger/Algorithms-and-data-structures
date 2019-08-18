#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#define MAXSIZE 1000 //�������󳤶�
typedef float ElemType;//����float�ı���
typedef int Status;//����int�ı��� 
typedef struct{
	ElemType data;
	Status cur;//�α� 
}component,SLinkList[MAXSIZE]; 
//����������
Status LocateElem_SL(SLinkList S,ElemType e);//�ڱ��в��� 
void InitSpace_SL(SLinkList &space);//��һ�������ʼ��Ϊһ������ 
Status Malloc_SL(SLinkList &space);//ȡһ���ڵ� 
void Free_SL(SLinkList &space,Status k);//�����нڵ������ڱ���������
void difference(SLinkList &space,Status &S);//(A-B)U(B-A);

Status LocateElem_SL(SLinkList S,ElemType e)//�ڱ��н��в��� 
{
	Status i;
	//�ھ�̬�������Ա���L���ҵ�һ��ֵΪe��Ԫ��
	//���ҵ��򷵻�����L�е�λ��,���򷵻�0
	i=S[0].cur;//��ʾ��һ���ڵ� 
	while(i!=0&&S[i].data!=e)
	{
		i=S[i].cur;//�൱��p=p->data������ƶ� 
	}
	return i;
} 
void InitSpace_SL(SLinkList &space)//��һ�������ʼ��Ϊһ������ 
{
	//��һά����space�и���������һ����������space[0].curΪͷָ��
	//0��ʾ��ָ��
	Status i;
	for(i=0;i<MAXSIZE-1;i++)
	{
		space[i].cur=i+1;
	} 
	space[MAXSIZE-1].cur=0;//βָ����治ָ���κζ���������Ϊ 0
}
Status Malloc_SL(SLinkList &space)//ȡһ���ڵ� 
{
	Status i;
	//�����ÿռ�����ǿգ��򷵻ط���Ľڵ��±꣬���򷵻�0
	i=space[0].cur;
	if(space[0].cur!=0)
	{
		space[0].cur=space[i].cur;	
	} 
	return i;
} 
void Free_SL(SLinkList &space,Status k)//�����нڵ������ڱ��������� 
{
	//���±�Ϊk�Ŀ��нڵ���յ�����������
	space[k].cur=space[0].cur;
	space[0].cur=k;
} 
void difference(SLinkList &space,Status &S)
{
	Status i,j,m,n,r,p,k; 
	ElemType b;
	//�������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)U(B-A)
	//�ľ�̬����SΪ��ͷָ����豸�ÿռ��㹻��space[0].curΪͷָ�� 
	InitSpace_SL(space);//��ʼ�����ÿռ�
	S=Malloc_SL(space);//����S��ͷ���
	r=S;//rָ��S�ĵ�ǰ���ڵ�
	scanf("%d%d",&m,&n); //����A��B��Ԫ�ظ���
	for(j=1;j<=m;j++)//��������A������ 
	{
		i=Malloc_SL(space);//����ڵ�
		scanf("%f",&space[i].data);//����A��Ԫ��ֵ
		space[r].cur=i;//�����β 
		r=i; 
	} 
	space[r].cur=0;//β�ڵ��ָ��Ϊ��
	for(j=1;j<=n;j++)//��������B��Ԫ������A����ɾ��������A������� 
	{
		scanf("%f",&b);//kָ�򼯺�A�еĵ�һ���ڵ� 
		p=S;
		k=space[S].cur;
		while(k!=space[r].cur&&space[k].data!=b)//�ڵ�ǰ���в��� 
		{
			p=k;
			k=space[k].cur; 
		}
		if(k==space[r].cur)//��ǰ���в����ڸ�Ԫ�ز�����r��ָ�Ľڵ�֮����r��λ�ò��� 
		{
			i=Malloc_SL(space);
			space[i].data=b;
			space[i].cur=space[r].cur;
			space[r].cur=i;
		}
		else//�������Ѵ��ڸ�Ԫ��ɾ��֮ 
		{
			space[p].cur=space[k].cur;
			Free_SL(space,k);
			if(r==k)
			{
				r=p;//��ɾ������r��ָ�Ľڵ㣬���޸�βָ�� 
			}
		}
	} 
	
}

int main(int argc, char** argv) 
{
	SLinkList space;
	Status s=0;
	difference(space,s);
	for(s=2;s<8;s++)//�ý��в�������6���� 
	{
		printf("%4.2f ",space[s].data);
	}
	return 0;
}
