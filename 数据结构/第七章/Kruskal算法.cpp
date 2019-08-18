#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <deque>
using namespace std;
#define MAXSIZE 10  //����������
typedef string VertexType; //��������
typedef int EdgeType;  //Ȩֵ���ͣ�����ͼ��0��1��������ͼ��Ȩֵ�������
#define INFINITY 0xffff
typedef struct  
{
	VertexType Vexs[MAXSIZE];  //��������
	EdgeType arcs[MAXSIZE][MAXSIZE]; //�ڽӾ��󣬿ɿ���Ϊ�߱�
	int iVexNum;  //�������
	int iArcNum;  //����
}MGraph;
#define SUCCESS 1
#define UNSUCCESS 0
typedef int Status; 
//�ɶ���ֵ�õ���������
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
//��������ͼ
Status GreateGraph(MGraph &MG)
{
	cout<<"���붥������Լ�����"<<endl;
	cin>>MG.iVexNum>>MG.iArcNum;
	cout<<"������"<<MG.iVexNum<<"������:";
	
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
	cout<<"�����������㹹�ɵı߼���Ȩֵ:";
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
	int weight;//Ȩֵ 
}Edge;
//�ڲ����в���
int FindInUFS(int *parent,int k)
{
	while(parent[k]!=k)
	{
		k=parent[k];
	}
	return k;
} 
//��³˹�����㷨����С������
void MiniSpanTree_Kruskal(const MGraph &G)
{
	//ת��Ϊ�߼�����
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
	//Ȩֵ��С�����������
	for(i=1;i<G.iArcNum-1;++i)
	{
		bool flag=false;//��������
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
	//���Ҳ���
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
 
	//��³˹�����㷨����С������
	cout << "����ķ�㷨�����С������:" << endl;
	MiniSpanTree_Kruskal( MG );
	cout << endl;

	return 0;
}
