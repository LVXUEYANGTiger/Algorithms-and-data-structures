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
	int ivex; //该弧依附的两点的位置
	int jvex;  //
	int weight;  //权值
	ArcType* ilink;  //分别指向依附该弧的下一条弧
	ArcType* jlink; 
}ArcType;
typedef struct  
{
	VertexType data;
	ArcType* firstArc; //指向第一条弧
 
}VertexNode;
typedef VertexNode MulAdjList[MAXVEXSIZE];
 
typedef struct  
{
	MulAdjList mulAdjList; //多重邻接表
	int iVexNum;
	int iArcNum;  
}MulAdjGraph;
 
 
//由顶点值得到顶点索引
int GetIndexByVertexVal( const MulAdjGraph& G, VertexType val )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( val == G.mulAdjList[i].data )
			return i;
	}
	return -1;
}
 
//创建无向图
Status CreateCrossGraph( MulAdjGraph& G )
{
	cout << "输入顶点个数以及边数：";
	cin >> G.iVexNum >> G.iArcNum;
	cout << "请输入" << G.iVexNum << "个顶点:";
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		cin >> G.mulAdjList[i].data;
		G.mulAdjList[i].firstArc = NULL;
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
		memset( pArc, 0, sizeof(ArcType));
		pArc->ivex = m;
		pArc->jvex = n;
		pArc->weight = 0;  //权值暂时不用
 
		pArc->ilink = G.mulAdjList[m].firstArc;//表头插入法
		G.mulAdjList[m].firstArc = pArc;
 
		pArc->jlink = G.mulAdjList[n].firstArc;//表头插入法
		G.mulAdjList[n].firstArc = pArc;
 
	}
	return SUCCESS;
}
 
 
//求顶点的度
int GetVertexDegree( const MulAdjGraph& G, VertexType val )
{
	int m = GetIndexByVertexVal( G, val );  //得到顶点的在顶点表中的索引
	if ( -1 == m )
		return -1;
 
	int TD = 0;
	ArcType* pArc = G.mulAdjList[m].firstArc;
	while ( pArc )
	{
		++TD;
		if ( m == pArc->ivex )
			pArc = pArc->ilink;
		else
			pArc = pArc->jlink;
	}
	return TD;
}
 
 
//深度优先遍历
void DFS( const MulAdjGraph& G, int i )
{
	cout << G.mulAdjList[i].data << " ";
	visited[i] = true;
 
	ArcType* pArc = G.mulAdjList[i].firstArc;
	while( pArc )
	{
		int iVex = pArc->jvex;
		if ( !visited[iVex] )
		{
			DFS( G, iVex );
		}
		pArc = pArc->ilink;
	}
}
void DFSTraverse( const MulAdjGraph& G )
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
void BFSTraverse( const MulAdjGraph& G )
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
			cout << G.mulAdjList[i].data << " ";
			visited[i] = true;
			Q.push( i );
 
			while ( !Q.empty() )
			{
				int iVex = Q.front();
				Q.pop();
 
				ArcType* pArc = G.mulAdjList[iVex].firstArc;
				while ( pArc )
				{
					int j = pArc->jvex;
					if ( !visited[j] )
					{
						cout << G.mulAdjList[j].data << " ";
						visited[j] = true;
						Q.push( j );
					}
					pArc = pArc->ilink;
				}
			}
 
		}
	}
}
 
 
//销毁图
void DestroyGraph( MulAdjGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		ArcType* pArc = G.mulAdjList[i].firstArc;
		while( pArc )
		{
			ArcType* q = pArc;
			pArc = pArc->ilink;
 
			int m = q->ivex;
			//在m号顶点下找当前边的前一条边
			ArcType* pmArc = G.mulAdjList[m].firstArc;
			ArcType* pmPreArc = NULL;
			while ( pmArc != q )
			{
				pmPreArc = pmArc;
				if ( m == pmArc->ivex )
				{
					pmArc = pmArc->ilink;
				}
				else 
				{
					pmArc = pmArc->jlink;
				}
			}
			if ( !pmPreArc )
			{
				G.mulAdjList[m].firstArc = q->ilink;
			}
			else
			{
				if ( m == pmPreArc->ivex )
				{
					pmPreArc->ilink = q->ilink;
				}
				else 
				{
					 pmPreArc->jlink = q->ilink;
				}
			}
 
 
			int n = q->jvex;
			//在n号顶点下找当前边的前一条边
			ArcType* pnArc = G.mulAdjList[n].firstArc;
			ArcType* pnPreArc = NULL;
			while ( pnArc != q )
			{
				pnPreArc = pnArc;
				if ( n == pnArc->ivex )
				{
					pnArc = pnArc->ilink;
				}
				else 
				{
					pnArc = pnArc->jlink;
				}
			}
			if ( !pnPreArc )
			{
				G.mulAdjList[n].firstArc = q->jlink;
			}
			else
			{
				if ( n == pnPreArc->ivex )
				{
					pnPreArc->ilink = q->jlink;
				}
				else 
				{
					pnPreArc->jlink = q->jlink;
				}
			}
			delete q;
		}
	}
	G.iVexNum = 0;
	G.iArcNum = 0;
}
 
 
int main(void)
{
	//创建有向图
	MulAdjGraph G;
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
 
	cout << "再输入求度的结点:";
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;
 
	cout << "再输入求度的结点:";
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;
 
	//销毁有向图
	DestroyGraph( G );
 
 
	return 0;
}

