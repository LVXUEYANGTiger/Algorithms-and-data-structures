#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <deque>
using namespace std;
#define MAXSIZE 10  //顶点最大个数
typedef string VertexType; //顶点类型
typedef int EdgeType;  //权值类型，有向图（0，1），无向图（权值，无穷大）
#define INFINITY 0xffff
typedef struct  
{
	VertexType Vexs[MAXSIZE];  //顶点向量
	EdgeType arcs[MAXSIZE][MAXSIZE]; //邻接矩阵，可看作为边表
	int iVexNum;  //顶点个数
	int iArcNum;  //边数
}MGraph;
#define SUCCESS 1
#define UNSUCCESS 0
typedef int Status; 
//由顶点值得到顶点索引
int GetIndexByVertexVal(const MGraph &MG,VertexType val)
{
	Status i;
	for(i=0;i<MG.iVexNum;++i)
	{
		if(val==MG.Vexs[i])
		{
			return i;
		}
	}
	return -1;
} 
//创建无向图
Status GreateGraph(MGraph &MG)
{
	cout<<"输入顶点个数以及边数"<<endl;
	cin>>MG.iVexNum>>MG.iArcNum;
	cout<<"请输入"<<MG.iVexNum<<"个顶点:";
	
	Status i,j,m,n;
	VertexType first;
	VertexType second;
	EdgeType weight;
	
	for(i=0;i<MG.iVexNum;i++)
	{
		cin>>MG.Vexs[i];
	} 
	for(i=0;i<MG.iVexNum;i++)
	{
		for(j=0;j<MG.iVexNum;j++)
		{
			MG.arcs[i][j]=INFINITY;
		}
	}
	cout<<"请输入由俩点构成的边及其权值:";
	for(i=0;i<MG.iArcNum;i++)
	{
		cin>>first>>second>>weight;
		m = GetIndexByVertexVal( MG, first );
		n = GetIndexByVertexVal( MG, second ); 
		if(m==-1||n==-1)
		{
			return UNSUCCESS;
		}
		MG.arcs[m][n]=MG.arcs[n][m]=weight;

	}
	return SUCCESS;
} 
typedef struct{
	int begin;
	int end;
	int weight;//权值 
}Edge;
//在并集中查找
int FindInUFS(int *parent,int k)
{
	while(parent[k]!=k)
	{
		k=parent[k];
	}
	return k;
} 
//克鲁斯卡尔算法求最小生成树
void MiniSpanTree_Kruskal(const MGraph &G)
{
	//转换为边集数组
	Edge *pEdge=new Edge[G.iArcNum];
	memset(pEdge,0,G.iArcNum*sizeof(Edge));
	int i,j,m,k,temp,n;
	m=0;
	
	for(i=1;i<G.iVexNum;i++)
	{
		k=i-1;
		for(j=0;j<=k;++j)
		{
			if(G.arcs[i][j]!=INFINITY)
			{
				pEdge[m].begin=i;
				pEdge[m].end=j;
				pEdge[m].weight=G.arcs[i][j];
				++m;
			}
		}
	} 
	//权值从小到大进行排序
	for(i=1;i<G.iArcNum-1;++i)
	{
		bool flag=false;//布尔类型
		for(j=0;j<G.iArcNum-i;++j)
		{
			if(pEdge[j].weight>pEdge[j+1].weight)
			{
				temp=pEdge[j].begin;
				pEdge[j].begin=pEdge[j+1].begin;
				pEdge[j+1].begin=temp;
				
				temp = pEdge[j].end;
				pEdge[j].end = pEdge[j+1].end;
				pEdge[j+1].end = temp;
				
				temp=pEdge[j].weight;
				pEdge[j].weight=pEdge[j+1].weight;
				pEdge[j+1].weight=temp;
				flag=true;
			}
		}
		if(!flag)
		{
			break;
		} 
	} 
	//查找并集
	int *parent=new int[G.iArcNum];
	for(i=0;i<G.iArcNum;++i)
	{
		parent[i]=i;
	} 
	for(i=0;i<G.iArcNum;i++)
	{
		m=FindInUFS(parent,pEdge[i].begin);
		n=FindInUFS(parent,pEdge[i].end);
		if(m!=n)
		{
			cout<<"("<<pEdge[i].begin<<","<<pEdge[i].end
			<<","<<pEdge[i].weight<<"("<<endl;
			parent[m]=n;
		}
	}
	if(!pEdge)
	{
		delete[] pEdge;
		pEdge=NULL;
	}
	if(!parent)
	{
		delete[] parent;
		parent=NULL;
	}
}
int main(int argc, char** argv) 
{
	MGraph MG;
	GreateGraph( MG );
 
	//克鲁斯卡尔算法求最小生成树
	cout << "普里姆算法求解最小生成数:" << endl;
	MiniSpanTree_Kruskal( MG );
	cout << endl;

	return 0;
}
