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
	int tailvex; //��ͷ�±�
	int headvex;  //��β�±�
	int weight;  //Ȩֵ
	ArcType* headlink;  //ָ����һ��ͬһ��ͷ�Ļ�
	ArcType* taillink; //ָ����һ��ͬһ��β�Ļ�
}ArcType;
typedef struct  
{
	VertexType data;
	ArcType* firstin; //ָ���һ���뻡
	ArcType* firstout; //ָ���һ������
 
}VertexNode;
typedef VertexNode CrossList[MAXVEXSIZE];
 
typedef struct  
{
	CrossList crossList; //ʮ������
	int iVexNum;
	int iArcNum;  
}CrossGraph;
 
 
//�ɶ���ֵ�õ���������
int GetIndexByVertexVal( const CrossGraph& G, VertexType val )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( val == G.crossList[i].data )
			return i;
	}
	return -1;
}
 
//��������ͼ
Status CreateCrossGraph( CrossGraph& G )
{
	cout << "���붥������Լ�������";
	cin >> G.iVexNum >> G.iArcNum;
	cout << "������" << G.iVexNum << "������:";
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		cin >> G.crossList[i].data;
		G.crossList[i].firstin = NULL;
		G.crossList[i].firstout = NULL;
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
		memset( pArc, 0, sizeof(ArcType) );
		pArc->headvex = m;
		pArc->tailvex = n;
		pArc->weight = 0;  //Ȩֵ��ʱ����
 
		pArc->taillink = G.crossList[m].firstout;//��ͷ���뷨
		G.crossList[m].firstout = pArc;
 
		pArc->headlink = G.crossList[n].firstin;//��ͷ���뷨
		G.crossList[n].firstin = pArc;
	}
	return SUCCESS;
}
 
 
//�󶥵�Ķȣ���ʮ�������л���ͦ����ģ���Ϊ�����ڽӱ������ڽӱ�Ľ����
int GetVertexDegree( const CrossGraph& G, VertexType val )
{
	int m = GetIndexByVertexVal( G, val );  //�õ�������ڶ�����е�����
	if ( -1 == m )
		return -1;
	
	int TD = 0;
	//�������
	ArcType* pArcOut = G.crossList[m].firstout;
	while ( pArcOut )
	{
		++TD;
		pArcOut = pArcOut->taillink;
	}
 
	//���ۼ����
	ArcType* pArcIn = G.crossList[m].firstin;
	while( pArcIn )
	{
		++TD;
		pArcIn = pArcIn->headlink;
	}
	return TD;
}
 
 
//������ȱ���
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
 
//������ȱ���
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
 
 
//����ͼ
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
	//��������ͼ
	CrossGraph G;
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
 
	//��������ͼ
	DestroyGraph( G );
 
 
	return 0;
}

