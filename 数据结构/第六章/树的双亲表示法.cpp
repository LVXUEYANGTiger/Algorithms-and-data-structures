#include <stdio.h>
#define MAX_TREE_SIZE 100
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int TElemType;
typedef int Status;
typedef struct PTNode  //���ṹ
{
	TElemType data;
	int parent;  //˫��λ����
}PTNode;
 
typedef struct //���ṹ
{
	PTNode nodes[MAX_TREE_SIZE];
	int n;   //���Ľ����
}PTree;
 
Status InitialTree(PTree &T)  //���ĳ�ʼ��
{
	T.n = 0;  //�ø��Ľ����Ϊ0
	return OK;
}
 
Status CreateTree(PTree &T)
{
	printf("����������:\n");
	scanf("%d",&T.n);
	printf("�����1-n������������ֵ����Ӧ��˫��λ�ã�������˫������-1��ʾ��:\n");
	for(int i = 0; i < T.n; ++i)
	{
		scanf("%d %d",&T.nodes[i].data, &T.nodes[i].parent);
	}
	return OK;
}
 
Status FindParentOfNode(PTree &T, TElemType node, TElemType &parent)
{
	//����node��˫��
	for(int i = 0; i < T.n; ++i)
	{
		if(T.nodes[i].data == node)
		{
			if(T.nodes[i].parent == -1)
			{
				return FALSE;//�������˫��	
			}
			else
			{
				parent = T.nodes[i].parent;//�ҵ�˫�ף���parent����
				return TRUE;
			}
		}
	}
	return FALSE;  //�޴˽�㷵��
}
 
Status FindChildOfNode(PTree &T, TElemType node)
{
	//����node�ĺ���
	int count = 0;  //��¼���ӵĸ���
	for(int i = 0; i < T.n; ++i)
	{
		if(T.nodes[i].data == node)
		{
			for(int j = i+1; j < T.n; ++j)//��Ϊ�����ǰ����1-n��˳��洢���������Դ�ʱjû��Ҫ��0��ʼ
			{
				if(T.nodes[j].parent == i)
				{
					++count;  //�ҵ�һ�����ӣ����Ӹ�����1
					printf("���%c�ĵ�%d������%d\n", node, count, T.nodes[j]); 
				}
 
			}
		}
	}
	if(!count)
	{
		return FALSE;//δ�ҵ�����
	}
	printf("�ܹ���%d������\n",count);
	return TRUE;  //�ҵ�����
}
 
int main()//����
{
	PTree T;
	InitialTree(T);
	CreateTree(T);
	TElemType parent;
	TElemType node;
	printf("������һ�����:\n");
	scanf("%d",&node);
	if(FindParentOfNode(T,node,parent))
	{
		printf("���%d��˫��Ϊ:%d\n",node,parent);
	}
	printf("\n");
	if(!FindChildOfNode(T,node))
	{
		printf("\n���%dû�к���\n",node);
	}
	return 0;
}

