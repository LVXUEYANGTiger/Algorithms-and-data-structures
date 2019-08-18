#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
 
#define MAXVEXSIZE 10
#define SUCCESS 1
#define UNSUCCESS 0
typedef int Status;
int visited[MAXVEXSIZE];  //指示顶点是否被访问
 
 
typedef string VertexType;  //顶点类型
typedef struct ArcType  
{
	int tailvex; //弧头下标
	int headvex;  //弧尾下标
	int weight;  //权值
	ArcType* headlink;  //指向下一个同一弧头的弧
	ArcType* taillink; //指向下一个同一弧尾的弧
}ArcType;
typedef struct  
{
	VertexType data;
	ArcType* firstin; //指向第一条入弧
	ArcType* firstout; //指向第一条出弧
 
}VertexNode;
typedef VertexNode CrossList[MAXVEXSIZE];
 
typedef struct  
{
	CrossList crossList; //十字链表
	int iVexNum;
	int iArcNum;  
}CrossGraph;
 
 
//由顶点值得到顶点索引
int GetIndexByVertexVal( const CrossGraph& G, VertexType val )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( val == G.crossList[i].data )
			return i;
	}
	return -1;
}
 
//创建有向图
Status CreateCrossGraph( CrossGraph& G )
{
	cout << "输入顶点个数以及边数：";
	cin >> G.iVexNum >> G.iArcNum;
	cout << "请输入" << G.iVexNum << "个顶点:";
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		cin >> G.crossList[i].data;
		G.crossList[i].firstin = NULL;
		G.crossList[i].firstout = NULL;
	}
 
	cout << "请输入由两点构成的边(" << G.iArcNum << "条):";
	for ( int i = 0; i < G.iArcNum; ++i )
	{
		VertexType first;
		VertexType second;
		cin >> first >> second;
		int m = GetIndexByVertexVal( G, first );
		int n = GetIndexByVertexVal( G, second ); 
		if ( m == -1 || n == -1 )
			return UNSUCCESS;
 
		ArcType* pArc = new ArcType;
		memset( pArc, 0, sizeof(ArcType) );
		pArc->headvex = m;
		pArc->tailvex = n;
		pArc->weight = 0;  //权值暂时不用
 
		pArc->taillink = G.crossList[m].firstout;//表头插入法
		G.crossList[m].firstout = pArc;
 
		pArc->headlink = G.crossList[n].firstin;//表头插入法
		G.crossList[n].firstin = pArc;
	}
	return SUCCESS;
}
 
 
//求顶点的度，在十字链表中还是挺方便的，因为其是邻接表与逆邻接表的结合体
int GetVertexDegree( const CrossGraph& G, VertexType val )
{
	int m = GetIndexByVertexVal( G, val );  //得到顶点的在顶点表中的索引
	if ( -1 == m )
		return -1;
	
	int TD = 0;
	//先求出度
	ArcType* pArcOut = G.crossList[m].firstout;
	while ( pArcOut )
	{
		++TD;
		pArcOut = pArcOut->taillink;
	}
 
	//再累加入度
	ArcType* pArcIn = G.crossList[m].firstin;
	while( pArcIn )
	{
		++TD;
		pArcIn = pArcIn->headlink;
	}
	return TD;
}
 
 
//深度优先遍历
void DFS( const CrossGraph& G, int i )
{
	cout << G.crossList[i].data << " ";
	visited[i] = true;
 
	ArcType* pArc = G.crossList[i].firstout;
	while( pArc )
	{
		int iVex = pArc->tailvex;
		if ( !visited[iVex] )
		{
			DFS( G, iVex );
		}
		pArc = pArc->taillink;
	}
}
void DFSTraverse( const CrossGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		visited[i] = false;
	}
 
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( !visited[i] )
		{
			DFS( G, i );
		}
	}
}
 
//广度优先遍历
void BFSTraverse( const CrossGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		visited[i] = false;
	}
 
	queue<int> Q;
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( !visited[i] )
		{
			cout << G.crossList[i].data << " ";
			visited[i] = true;
			Q.push( i );
			 
			while ( !Q.empty() )
			{
				int iVex = Q.front();
				Q.pop();
 
				ArcType* pArc = G.crossList[iVex].firstout;
				while ( pArc )
				{
					int j = pArc->tailvex;
					if ( !visited[j] )
					{
						cout << G.crossList[j].data << " ";
						visited[j] = true;
						Q.push(j);
					}
					pArc = pArc->taillink;
				}
			}
 
		}
	}
}
 
 
//销毁图
void DestroyGraph( CrossGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		ArcType* pArc = G.crossList[i].firstout;
		while( pArc )
		{
			ArcType* q = pArc;
			pArc = pArc->taillink;
			delete q;
		}
		G.crossList[i].firstout = NULL;
		G.crossList[i].firstin = NULL;
	}
	G.iVexNum = 0;
	G.iArcNum = 0;
}
 
 
int main()
{
	//创建有向图
	CrossGraph G;
	CreateCrossGraph( G );
 
	//深度优先遍历图
	cout << "深度优先遍历:" << endl;
	DFSTraverse( G );
	cout << endl << endl;
 
	//广度优先遍历图
	cout << "广度优先遍历:" << endl;
	BFSTraverse( G );
	cout << endl << endl;
 
	//结点的度
	cout << "输入求度的结点:";
	VertexType v;
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;
 
	//销毁有向图
	DestroyGraph( G );
 
 
	return 0;
}

