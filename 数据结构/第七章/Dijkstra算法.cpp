#include <stdio.h>
//#include <limits.h>  //�ṩINT_MAX�Ķ���
#define INFINITY 10000
#define MAX_VERTEX_NUM 20
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
typedef enum{DG, DN, UDG, UDN} GraphKind;   //����ͼ��������������ͼ��������
typedef int VRType;		//����Ĺ�ϵ����
typedef int InfoType;	//�������Ϣ��ָ������
typedef int VertexType;  //�����ֵ����
typedef int Status;
typedef struct ArcCell
{
	VRType adj;  //VRType�Ƕ����ϵ���ͣ�����Ȩͼ����1(��)��0(��)
				//��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ����
	//InfoType *info;  //�û������Ϣ��ָ��,���Բ�Ҫ
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct 
{
	VertexType vexs[MAX_VERTEX_NUM];  //��������
	AdjMatrix arcs;			//�ڽӾ���
	int vexnum, arcnum;  //ͼ�ĵ�ǰ�������뻡��
	GraphKind kind;		//ͼ�������־
}MGraph;
 
Status LocateVex(const MGraph &G, const VertexType &u)
{
	//ͼG���ڣ�u��G�ж�������ͬ����
	//��G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�ERROR
	for(int i = 0; i < G.vexnum; ++i)
		if(u == G.vexs[i])
			return i;  //���ض�����ͼ��λ��
	return ERROR;
}
 
 
Status CreateDG(MGraph &G)
{
	//��������ͼ�����ڽӾ����ʾ
	printf("����������ͼ�Ķ������뻡����\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	printf("���������еĶ���:\n");
	for(int index = 0; index < G.vexnum; ++ index)
	{
		scanf("%d", &G.vexs[index]);
	}
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0; //��ʼ���ڽӾ���
		}
	}
	VertexType v1, v2;
	int m, n;  //���Ա��涥���λ��
	for(int k = 0; k < G.vexnum; ++k)
	{
		printf("������һ�����������������㣺\n");
		scanf("%d %d", &v1, &v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = 1;  //1��ʾ����ͼ
	}
	G.kind = DG;  //G������ͼ
	printf("�ڽӾ���Ϊ��\n");
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			printf("%4d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
	return OK;
}
 
Status CreateUDG(MGraph &G)
{
	//��������ͼ�����ڽӾ����ʾ
	printf("����������ͼ�Ķ������뻡����\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	printf("���������еĶ���:\n");
	for(int index = 0; index < G.vexnum; ++ index)
	{
		scanf("%d", &G.vexs[index]);
	}
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0; //��ʼ���ڽӾ���
		}
	}
	VertexType v1, v2;
	int m, n;  //���Ա��涥���λ��
	for(int k = 0; k < G.vexnum; ++k)
	{
		printf("������һ�����������������㣺\n");
		scanf("%d %d", &v1, &v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = 1;  //1��ʾ����ͼ
		G.arcs[n][m] = G.arcs[m][n];  //��<v1,v2>�ĶԳƻ�<v2,v1>
	}
	G.kind = UDG;  //G������ͼ
	printf("�ڽӾ���Ϊ��\n");
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			printf("%4d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
	return OK;
}
 
Status CreateDN(MGraph &G)
{
	//�������飨�ڽӾ��󣩱�ʾ��������������
	printf("�������������Ķ�������Լ�������\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	printf("���������еĶ��㣺\n");
	for(int i = 0; i < G.vexnum; ++i)
	{
		//���춥������
		scanf("%d", &G.vexs[i]);
	}
	for(int i = 0; i < G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	VertexType v1, v2;
	VRType w;
	int m, n;  //���Ա��涥���λ��
	for(int k = 0; k < G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ����Լ�Ȩֵ:\n", k+1);
		scanf("%d %d %d",&v1, &v2, &w);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = w;  //��<v1, v2>��Ȩֵ
	}
	G.kind = DN;  //DN��������
	printf("�ڽӾ���Ϊ��\n");
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			printf("%d\t", G.arcs[i][j].adj);
		}
		printf("\n");
	}
	return OK;
 
}
 
Status CreateUDN(MGraph &G)
{
	//��������(�ڽӾ���)��ʾ��������������G
	printf("�������������Ķ�������Լ�������\n");
	scanf("%d %d", &G.vexnum, &G.arcnum);
	printf("���������еĶ���:\n");
	for(int index = 0; index < G.vexnum; ++ index)
	{
		//���춥������
		scanf("%d", &G.vexs[index]);
	}
	for(int i = 0; i < G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	VertexType v1, v2;
	VRType w;
	int m, n;  //���Ա��涥���λ��
	for(int k = 0; k < G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ����Լ�Ȩֵ:\n", k+1);
		scanf("%d %d %d",&v1, &v2, &w);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = w;  //��<v1, v2>��Ȩֵ
		G.arcs[n][m] = G.arcs[m][n];  //��<v1,v2>�ĶԳƻ�<v2,v1>
	}
	G.kind = UDN;  //UDN��������
	printf("�ڽӾ���Ϊ��\n");
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			printf("%d\t", G.arcs[i][j].adj);
		}
		printf("\n");
	}
	return OK;
 
}
 
 
Status CreateGraph(MGraph &G)
{
	//����ͼ
	printf("��������Ҫ��������ͼ:\n0:����ͼ\t1:������\n2:����ͼ\t3:������\n");
	scanf("%d", &G.kind);
	switch(G.kind)
	{
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);
	case UDN:return CreateUDN(G);
	default:return ERROR;
	}
}
 
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //���·������
typedef int ShortPathTable[MAX_VERTEX_NUM];  //���·���ĳ�������
 
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &p, ShortPathTable &D)
{
	// ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v]
	// ��P[v][w]ΪTRUE,��w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
	// final[v]ΪTRUE���ҽ���v��S,���Ѿ���ô�v0��v�����·����
	int v,w,i,j;
	int final[MAX_VERTEX_NUM];  
	for(v=0; v<G.vexnum; ++v)
	{
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for(w=0; w<G.vexnum; ++w)
		{
			p[v][w] = FALSE;  //�����е�·��Ϊ��
		}
		if(D[v] < INFINITY)
		{
			p[v][v0] = 1;  //���ʵ���ʼ����v0
			p[v][v] = 2;  //���ʵĵڶ�����v
		}
	}
 
	D[v0] = 0; final[v0] = TRUE;  //��ʼ����v0��������S��
 
	int min;
	//��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��������v��S��
	for(i=1; i < G.vexnum; ++i)  //����G.vexnum - 1������
	{
		min = INFINITY;  //��ǰ��֪��v0������������
		for(w=0; w < G.vexnum; ++w)
		{
			if(!final[w])  //w������V-S��
				if(D[w] < min)
				{
					v = w;
					min = D[w];  //w������v0�������
				}
		}
		final[v] = TRUE;  //��v0���������v����S��
	
		for(w = 0; w < G.vexnum; ++w)  //���µ�ǰ���·��������
		{
			if(!final[w] && (min + G.arcs[v][w].adj < D[w])) //�޸�D[w]��P[w],w����V-S
			{	
				D[w] = min + G.arcs[v][w].adj;
				int cnt = 1;  //��¼�ѷ��ʵĶ�����
				for(j = 0; j < G.vexnum; ++j)
				{
					p[w][j] = p[v][j];
					if(p[v][j] != 0)
						++cnt;
				}
				p[w][w] = cnt;  //��w����ķ��ʴ�����и�ֵ
			}
		}
	}
}
 
void DisplayPathMatrix(MGraph &G, PathMatrix &p)
{
	int i,j;
	for(i=0; i <= G.vexnum; ++i)
	{
		if(i == 0)
			printf("     ");
		else
			printf("v%-3d",i-1);
		
	}
	printf("\n");
 
	for(i=0; i < G.vexnum; ++i)
	{
		printf("v%d",i);
		for(j=0; j < G.vexnum; ++j)
		{
			printf("%4d",p[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	MGraph G;
	CreateGraph(G);
 
	PathMatrix p;
	ShortPathTable D;
	
	VertexType v0;
	printf("������Դ�㣺");
	scanf("%d",&v0);
	ShortestPath_DIJ(G,v0,p,D);
 
	int i;
	printf("·�����ȣ�10000��ʾ��·������\n");
	for(i=0; i < G.vexnum; ++i)
		printf("%6d",D[i]);
	printf("\n");
 
	printf("·�����飺\n");
	DisplayPathMatrix(G,p);
	return 0;
}

