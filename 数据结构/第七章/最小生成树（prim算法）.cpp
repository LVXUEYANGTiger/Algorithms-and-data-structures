#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#define MAX_VERTEX_NUM 20   //最大顶点数
#define MAX MAX_VERTEX_NUM
 
#define INFINITY INT_MAX //INT_MAX  
 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int VRType;//顶点关系类型
typedef int InfoType;  
typedef char VertexType; //顶点值类型
typedef enum{DG, DN, UDG, UDN}GraphKind;  //{有向图，有向网，无向图，无向网}
typedef struct ArcCell
{
	VRType adj;  //VRType是顶点关系类型，对无权图，用1或0表示相邻否
				//对带权图，则为权值类型
	InfoType *info;  //该弧相关信息的指针
}ArcCell, AdjMatric[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 
typedef struct  
{
	VertexType vexs[MAX_VERTEX_NUM];  //顶点向量
	AdjMatric arcs;  //邻接矩阵
	int vexnum, arcnum;  //图的当前顶点数与弧数
	GraphKind kind;  //图的种类标志
}MGraph;

typedef struct closedg{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];
 
int LocateVex(const MGraph &G, VertexType u)
{
	//初始条件：图G存在，u与G中顶点有相同特征
	//操作结果：若G中存在顶点u，则返回该顶点在图中位置，否则返回-1
	for(int i=0; i < G.vexnum; ++i)
	{
		if(u == (G.vexs[i]))
			return i;
	}
	return -1;
}

int minimum(closedge close,int n)
{
	int min=INFINITY,k=0,i;
    for(i=0;i<n;i++)
    {
        if(close[i].lowcost != 0 && close[i].lowcost < min)
        {
            min = close[i].lowcost;
            k = i;
        }
    }	
	return k; 
} 


Status CreateUDN(MGraph &G)
{
	//采用数组（邻接矩阵）表示法，构造无向网G
	printf("请输入无向网的顶点数与边数：\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	getchar();//取出输入流中的回车符
	int i,j;
	printf("请输入%d个顶点的值:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)//构造顶点向量
	{
		scanf("%c",&G.vexs[i]);
	}
	for(i=0; i<G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;  
			G.arcs[i][j].info = NULL;  //表示无边的相关信息
		}
	}
 
	int k;
	VertexType v1, v2;//顶点的临时存储变量
	VRType w;  //顶点关系，此时代表权值
	for(k=0; k<G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点及权值:\n", k+1);
		getchar();//取出输入流中的回车符
		scanf("%c%c%d",&v1, &v2, &w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //无此顶点，构造失败，返回出错信息
		G.arcs[i][j].adj = w;
		//因为边没有其他的相关信息，G.arcs[i][j].info== NULL，保持不变
		G.arcs[j][i].adj = G.arcs[i][j].adj;  //置<v1,v2>的对称弧<v2,v1>;
	}
	G.kind = UDN;  //无向网
	return OK;
}

void MiniSpanTree_PRIM(MGraph G,VertexType u){
	//用普利姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。
	//记录从顶点集U到V-U的代价最小的边的辅助数组定义： 
	closedge close;
	int k=LocateVex(G,u);
	for(int j=0;j<G.vexnum;++j)
	{		//辅助数组初始化 
		if(j!=k){
			close[j].adjvex=u;
			close[j].lowcost=G.arcs[k][j].adj;
		}
	}
	close[k].lowcost=0;			//初始，U={u}
	for(int i=1;i<G.vexnum;++i)		//选择其余G.vexnum-1个顶点 
	{
		k=minimum(close,G.vexnum);			//求出T的下一个节点：第k顶点 
		//此时close[k].lowcost=
			//Min{close[vi].lowcost | close[vi].lowcost>0,vi∈V-U 
		printf("%c%c\n",close[k].adjvex,G.vexs[k]);		//输出生成树的边 
		close[k].lowcost=0;			//第k顶点并入U集 
		for(int j=0;j<G.vexnum;++j)
		{
			if(G.arcs[k][j].adj<close[j].lowcost)		//新的顶点并入U后重新选择最小边。
			{
				close[j].adjvex=G.vexs[k];
				close[j].lowcost=G.arcs[k][j].adj;
			} 
		}
	} 
}

int main(int argc, char** argv) {
	MGraph G;
	VertexType u;
	CreateUDN(G);
	printf("请输入想要开始出发的顶点:\n");
	getchar();
	scanf("%c",&u); 
	MiniSpanTree_PRIM(G,u);
	return 0;
}
