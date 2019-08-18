#include <stdio.h>
//#include <limits.h>  //提供INT_MAX的定义
#define INFINITY 10000
#define MAX_VERTEX_NUM 20
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
typedef enum{DG, DN, UDG, UDN} GraphKind;   //有向图、有向网、无向图、无向网
typedef int VRType;		//顶点的关系类型
typedef int InfoType;	//弧相关信息的指针类型
typedef int VertexType;  //顶点的值类型
typedef int Status;
typedef struct ArcCell
{
	VRType adj;  //VRType是顶点关系类型，对无权图，用1(是)或0(否)
				//表示相邻否；对带权图，则为权值类型
	//InfoType *info;  //该弧相关信息的指针,可以不要
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct 
{
	VertexType vexs[MAX_VERTEX_NUM];  //顶点向量
	AdjMatrix arcs;			//邻接矩阵
	int vexnum, arcnum;  //图的当前顶点数与弧数
	GraphKind kind;		//图的种类标志
}MGraph;
 
Status LocateVex(const MGraph &G, const VertexType &u)
{
	//图G存在，u和G中顶点有相同特征
	//若G中存在顶点u，则返回该顶点在图中位置；否则返回ERROR
	for(int i = 0; i < G.vexnum; ++i)
		if(u == G.vexs[i])
			return i;  //返回顶点在图中位置
	return ERROR;
}
 
 
Status CreateDG(MGraph &G)
{
	//构造有向图，用邻接矩阵表示
	printf("请输入有向图的顶点数与弧数：\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	printf("请输入所有的顶点:\n");
	for(int index = 0; index < G.vexnum; ++ index)
	{
		scanf("%d", &G.vexs[index]);
	}
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0; //初始化邻接矩阵
		}
	}
	VertexType v1, v2;
	int m, n;  //用以保存顶点的位置
	for(int k = 0; k < G.vexnum; ++k)
	{
		printf("请输入一条边依附的两个顶点：\n");
		scanf("%d %d", &v1, &v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = 1;  //1表示有向图
	}
	G.kind = DG;  //G是有向图
	printf("邻接矩阵为：\n");
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
	//构造无向图，用邻接矩阵表示
	printf("请输入无向图的顶点数与弧数：\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	printf("请输入所有的顶点:\n");
	for(int index = 0; index < G.vexnum; ++ index)
	{
		scanf("%d", &G.vexs[index]);
	}
	for(int i = 0; i < G.vexnum; ++i)
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0; //初始化邻接矩阵
		}
	}
	VertexType v1, v2;
	int m, n;  //用以保存顶点的位置
	for(int k = 0; k < G.vexnum; ++k)
	{
		printf("请输入一条边依附的两个顶点：\n");
		scanf("%d %d", &v1, &v2);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = 1;  //1表示有向图
		G.arcs[n][m] = G.arcs[m][n];  //置<v1,v2>的对称弧<v2,v1>
	}
	G.kind = UDG;  //G是无向图
	printf("邻接矩阵为：\n");
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
	//采用数组（邻接矩阵）表示法，构造有向网
	printf("请输入有向网的顶点个数以及边数：\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	printf("请输入所有的顶点：\n");
	for(int i = 0; i < G.vexnum; ++i)
	{
		//构造顶点向量
		scanf("%d", &G.vexs[i]);
	}
	for(int i = 0; i < G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	VertexType v1, v2;
	VRType w;
	int m, n;  //用以保存顶点的位置
	for(int k = 0; k < G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点以及权值:\n", k+1);
		scanf("%d %d %d",&v1, &v2, &w);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = w;  //弧<v1, v2>的权值
	}
	G.kind = DN;  //DN是无向网
	printf("邻接矩阵为：\n");
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
	//采用数组(邻接矩阵)表示法，构造无向网G
	printf("请输入无向网的顶点个数以及边数：\n");
	scanf("%d %d", &G.vexnum, &G.arcnum);
	printf("请输入所有的顶点:\n");
	for(int index = 0; index < G.vexnum; ++ index)
	{
		//构造顶点向量
		scanf("%d", &G.vexs[index]);
	}
	for(int i = 0; i < G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	VertexType v1, v2;
	VRType w;
	int m, n;  //用以保存顶点的位置
	for(int k = 0; k < G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点以及权值:\n", k+1);
		scanf("%d %d %d",&v1, &v2, &w);
		m = LocateVex(G,v1);
		n = LocateVex(G,v2);
		G.arcs[m][n].adj = w;  //弧<v1, v2>的权值
		G.arcs[n][m] = G.arcs[m][n];  //置<v1,v2>的对称弧<v2,v1>
	}
	G.kind = UDN;  //UDN是无向网
	printf("邻接矩阵为：\n");
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
	//构造图
	printf("请输入你要构造哪种图:\n0:有向图\t1:有向网\n2:无向图\t3:无向网\n");
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
 
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //最短路径数组
typedef int ShortPathTable[MAX_VERTEX_NUM];  //最短路径的长度数组
 
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &p, ShortPathTable &D)
{
	// 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v]
	// 若P[v][w]为TRUE,则w是从v0到v当前求得最短路径上的顶点。
	// final[v]为TRUE当且仅当v∈S,即已经求得从v0到v的最短路径。
	int v,w,i,j;
	int final[MAX_VERTEX_NUM];  
	for(v=0; v<G.vexnum; ++v)
	{
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for(w=0; w<G.vexnum; ++w)
		{
			p[v][w] = FALSE;  //设所有的路径为空
		}
		if(D[v] < INFINITY)
		{
			p[v][v0] = 1;  //访问的起始点标记v0
			p[v][v] = 2;  //访问的第二个点v
		}
	}
 
	D[v0] = 0; final[v0] = TRUE;  //初始化，v0顶点属于S集
 
	int min;
	//开始主循环，每次求得v0到某个v顶点的最短路径，并加v到S集
	for(i=1; i < G.vexnum; ++i)  //其余G.vexnum - 1个顶点
	{
		min = INFINITY;  //当前所知离v0顶点的最近距离
		for(w=0; w < G.vexnum; ++w)
		{
			if(!final[w])  //w顶点在V-S中
				if(D[w] < min)
				{
					v = w;
					min = D[w];  //w顶点离v0顶点更近
				}
		}
		final[v] = TRUE;  //离v0顶点最近的v加入S集
	
		for(w = 0; w < G.vexnum; ++w)  //更新当前最短路径及距离
		{
			if(!final[w] && (min + G.arcs[v][w].adj < D[w])) //修改D[w]和P[w],w属于V-S
			{	
				D[w] = min + G.arcs[v][w].adj;
				int cnt = 1;  //记录已访问的顶点数
				for(j = 0; j < G.vexnum; ++j)
				{
					p[w][j] = p[v][j];
					if(p[v][j] != 0)
						++cnt;
				}
				p[w][w] = cnt;  //对w顶点的访问次序进行赋值
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
	printf("请输入源点：");
	scanf("%d",&v0);
	ShortestPath_DIJ(G,v0,p,D);
 
	int i;
	printf("路径长度（10000表示无路径）：\n");
	for(i=0; i < G.vexnum; ++i)
		printf("%6d",D[i]);
	printf("\n");
 
	printf("路径数组：\n");
	DisplayPathMatrix(G,p);
	return 0;
}

