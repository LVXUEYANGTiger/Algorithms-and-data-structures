#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 20
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int TElemType;
typedef int Status;
#define OK 1
 
//--------------���ĺ�������洢��ʾ----------------------
typedef struct CTNode
{
	//���ӽ��
	int child;
	struct CTNode *next;
}*ChildPtr;
 
typedef struct  
{
	TElemType data;//���ֵ
	ChildPtr firstchild; //��������ͷָ��
	           //����һ��˫�׵����ܷ�����ҵ���˫�ס�int Parent;
}CTBox;
 
typedef struct 
{
	CTBox nodes[MAX_TREE_SIZE];  //
	int n, r;  //������͸���λ�� 
}CTree;
 
Status CreateTree(CTree &T)
{
	//����һ����
	printf("������������������λ���±꣺\n");
	scanf("%d %d",&T.n, &T.r);
	printf("��������ڵ��ֵ\n");
	for(int i = 0; i < T.n; ++i)
	{
		scanf("%d",&T.nodes[i].data);
		T.nodes[i].firstchild = NULL;
	}
	printf("����ÿ�����ĺ��ӽ��...\n");
	system("pause");
	for(int i = 0; i < T.n; ++i)
	{
		printf("������λ��Ϊ%d�Ľ��ĺ��Ӹ�����>=0��,�к��������뺢���ǵ�λ�ã�\n",i);
		int nChild=0;
		scanf("%d",&nChild);
		ChildPtr p=NULL;  //pָ����뺢��λ�õ�ǰһ��λ��
		ChildPtr q=NULL;  //q������ʾ�����������b����������
		for(int j = 0; j < nChild; ++j)
		{
			q= (ChildPtr)malloc(sizeof(struct CTNode));//Ϊ���ӵ�λ�ÿ���һ���ռ�	
			if(!q)
				exit(OVERFLOW);
			scanf("%d",&(q->child));  //����������������λ��ֵ
			q->next = NULL;
			if(j == 0)//����������ͷ���ָ���������һ�����
			{
				T.nodes[i].firstchild = q;
			}
			else
			{
				p->next = q;
			}
			p = q;	
		}
	}
	return OK;
}
 
 
 
Status PrintChild(const ChildPtr &C)
{//��ӡ�����ĺ���
	if(C)
	{
		ChildPtr p;
		p = C;
		while(p)
		{
			printf("%d ->",p->child);
			p = p->next;
		}
		printf("NULL");
		return TRUE;
	}
	else
	{
		printf("NULL");
		return FALSE;
	}
	
}
void PrintChildTree(const CTree &T)//������Ľ�㼰���ǵĺ���
{
	printf("\nλ��%dΪ���ĸ�%d\n\n", T.r, T.nodes[T.r].data);
	for(int i = 0; i < T.n; ++i)
	{
		printf("λ��%d,���ֵ%d ->", i, T.nodes[i].data);
		PrintChild(T.nodes[i].firstchild);
		printf("\n");
		
	}
}
 
Status FindChildOfNode(const CTree &T, TElemType e)//�ҽ��e�ĺ���
{
	for(int i = 0; i < T.n; i++)
	{
		if(T.nodes[i].data == e)
		{
			printf("���%d ->",e);
			PrintChild(T.nodes[i].firstchild);
			printf("\n");
			return TRUE;
		}
	}
	printf("�޴˽��\n");
	return FALSE;
}
 
 
int main()  //����
{
	CTree T;
	CreateTree(T);
	PrintChildTree(T);
	while(1)
	{
		int data;
		printf("��������Ҫ�����亢�ӵĽ��\n");
		scanf("%d",&data);
		FindChildOfNode(T,data);
		system("pause");
	}
	return 0;
}

