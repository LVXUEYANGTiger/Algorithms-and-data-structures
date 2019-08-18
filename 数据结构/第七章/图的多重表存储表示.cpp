#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
 
#define MAXVEXSIZE 10
#define SUCCESS 1
#define UNSUCCESS 0
typedef int Status;
int visited[MAXVEXSIZE];  //ָʾ�����Ƿ񱻷���
 
 
typedef string VertexType;  //��������
typedef struct ArcType  
{
	int ivex; //�û������������λ��
	int jvex;  //
	int weight;  //Ȩֵ
	ArcType* ilink;  //�ֱ�ָ�������û�����һ����
	ArcType* jlink; 
}ArcType;
typedef struct  
{
	VertexType data;
	ArcType* firstArc; //ָ���һ����
 
}VertexNode;
typedef VertexNode MulAdjList[MAXVEXSIZE];
 
typedef struct  
{
	MulAdjList mulAdjList; //�����ڽӱ�
	int iVexNum;
	int iArcNum;  
}MulAdjGraph;
 
 
//�ɶ���ֵ�õ���������
int GetIndexByVertexVal( const MulAdjGraph& G, VertexType val )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( val == G.mulAdjList[i].data )
			return i;
	}
	return -1;
}
 
//��������ͼ
Status CreateCrossGraph( MulAdjGraph& G )
{
	cout << "���붥������Լ�������";
	cin >> G.iVexNum >> G.iArcNum;
	cout << "������" << G.iVexNum << "������:";
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		cin >> G.mulAdjList[i].data;
		G.mulAdjList[i].firstArc = NULL;
	}
 
	cout << "�����������㹹�ɵı�(" << G.iArcNum << "��):";
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
		pArc->weight = 0;  //Ȩֵ��ʱ����
 
		pArc->ilink = G.mulAdjList[m].firstArc;//��ͷ���뷨
		G.mulAdjList[m].firstArc = pArc;
 
		pArc->jlink = G.mulAdjList[n].firstArc;//��ͷ���뷨
		G.mulAdjList[n].firstArc = pArc;
 
	}
	return SUCCESS;
}
 
 
//�󶥵�Ķ�
int GetVertexDegree( const MulAdjGraph& G, VertexType val )
{
	int m = GetIndexByVertexVal( G, val );  //�õ�������ڶ�����е�����
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
 
 
//������ȱ���
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
 
//������ȱ���
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
 
 
//����ͼ
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
			//��m�Ŷ������ҵ�ǰ�ߵ�ǰһ����
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
			//��n�Ŷ������ҵ�ǰ�ߵ�ǰһ����
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
	//��������ͼ
	MulAdjGraph G;
	CreateCrossGraph( G );
 
	//������ȱ���ͼ
	cout << "������ȱ���:" << endl;
	DFSTraverse( G );
	cout << endl << endl;
 
	//������ȱ���ͼ
	cout << "������ȱ���:" << endl;
	BFSTraverse( G );
	cout << endl << endl;
 
	//���Ķ�
	cout << "������ȵĽ��:";
	VertexType v;
	cin >> v;
	cout << "��Ϊ��" << GetVertexDegree( G, v ) << endl;
 
	cout << "��������ȵĽ��:";
	cin >> v;
	cout << "��Ϊ��" << GetVertexDegree( G, v ) << endl;
 
	cout << "��������ȵĽ��:";
	cin >> v;
	cout << "��Ϊ��" << GetVertexDegree( G, v ) << endl;
 
	//��������ͼ
	DestroyGraph( G );
 
 
	return 0;
}

