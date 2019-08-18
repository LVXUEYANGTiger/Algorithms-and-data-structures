#include <stdio.h>
#define MAX_TREE_SIZE 100
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int TElemType;
typedef int Status;
typedef struct PTNode  //结点结构
{
	TElemType data;
	int parent;  //双亲位置域
}PTNode;
 
typedef struct //树结构
{
	PTNode nodes[MAX_TREE_SIZE];
	int n;   //树的结点数
}PTree;
 
Status InitialTree(PTree &T)  //树的初始化
{
	T.n = 0;  //置根的结点数为0
	return OK;
}
 
Status CreateTree(PTree &T)
{
	printf("请输入结点数:\n");
	scanf("%d",&T.n);
	printf("按编号1-n依次输入结点数值及对应的双亲位置（根结点的双亲请用-1表示）:\n");
	for(int i = 0; i < T.n; ++i)
	{
		scanf("%d %d",&T.nodes[i].data, &T.nodes[i].parent);
	}
	return OK;
}
 
Status FindParentOfNode(PTree &T, TElemType node, TElemType &parent)
{
	//求结点node的双亲
	for(int i = 0; i < T.n; ++i)
	{
		if(T.nodes[i].data == node)
		{
			if(T.nodes[i].parent == -1)
			{
				return FALSE;//根结点无双亲	
			}
			else
			{
				parent = T.nodes[i].parent;//找到双亲，用parent带回
				return TRUE;
			}
		}
	}
	return FALSE;  //无此结点返回
}
 
Status FindChildOfNode(PTree &T, TElemType node)
{
	//求结点node的孩子
	int count = 0;  //记录孩子的个数
	for(int i = 0; i < T.n; ++i)
	{
		if(T.nodes[i].data == node)
		{
			for(int j = i+1; j < T.n; ++j)//因为我们是按编号1-n的顺序存储的树，所以此时j没必要从0开始
			{
				if(T.nodes[j].parent == i)
				{
					++count;  //找到一个孩子，孩子个数加1
					printf("结点%c的第%d个孩子%d\n", node, count, T.nodes[j]); 
				}
 
			}
		}
	}
	if(!count)
	{
		return FALSE;//未找到孩子
	}
	printf("总共有%d个孩子\n",count);
	return TRUE;  //找到孩子
}
 
int main()//测试
{
	PTree T;
	InitialTree(T);
	CreateTree(T);
	TElemType parent;
	TElemType node;
	printf("请输入一个结点:\n");
	scanf("%d",&node);
	if(FindParentOfNode(T,node,parent))
	{
		printf("结点%d的双亲为:%d\n",node,parent);
	}
	printf("\n");
	if(!FindChildOfNode(T,node))
	{
		printf("\n结点%d没有孩子\n",node);
	}
	return 0;
}

