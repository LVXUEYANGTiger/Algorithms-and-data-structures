#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#define MAX_VERTEX_NUM 20   //��󶥵���
#define MAX MAX_VERTEX_NUM
 
#define INFINITY INT_MAX //INT_MAX  
 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int VRType;//�����ϵ����
typedef int InfoType;  
typedef char VertexType; //����ֵ����
typedef enum{DG, DN, UDG, UDN}GraphKind;  //{����ͼ��������������ͼ��������}
typedef struct ArcCell
{
	VRType adj;  //VRType�Ƕ����ϵ���ͣ�����Ȩͼ����1��0��ʾ���ڷ�
				//�Դ�Ȩͼ����ΪȨֵ����
	InfoType *info;  //�û������Ϣ��ָ��
}ArcCell, AdjMatric[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 
typedef struct  
{
	VertexType vexs[MAX_VERTEX_NUM];  //��������
	AdjMatric arcs;  //�ڽӾ���
	int vexnum, arcnum;  //ͼ�ĵ�ǰ�������뻡��
	GraphKind kind;  //ͼ�������־
}MGraph;

typedef struct closedg{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];
 
int LocateVex(const MGraph &G, VertexType u)
{
	//��ʼ������ͼG���ڣ�u��G�ж�������ͬ����
	//�����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
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
	//�������飨�ڽӾ��󣩱�ʾ��������������G
	printf("�������������Ķ������������\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	getchar();//ȡ���������еĻس���
	int i,j;
	printf("������%d�������ֵ:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)//���춥������
	{
		scanf("%c",&G.vexs[i]);
	}
	for(i=0; i<G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;  
			G.arcs[i][j].info = NULL;  //��ʾ�ޱߵ������Ϣ
		}
	}
 
	int k;
	VertexType v1, v2;//�������ʱ�洢����
	VRType w;  //�����ϵ����ʱ����Ȩֵ
	for(k=0; k<G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ��㼰Ȩֵ:\n", k+1);
		getchar();//ȡ���������еĻس���
		scanf("%c%c%d",&v1, &v2, &w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //�޴˶��㣬����ʧ�ܣ����س�����Ϣ
		G.arcs[i][j].adj = w;
		//��Ϊ��û�������������Ϣ��G.arcs[i][j].info== NULL�����ֲ���
		G.arcs[j][i].adj = G.arcs[i][j].adj;  //��<v1,v2>�ĶԳƻ�<v2,v1>;
	}
	G.kind = UDN;  //������
	return OK;
}

void MiniSpanTree_PRIM(MGraph G,VertexType u){
	//������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߡ�
	//��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨�壺 
	closedge close;
	int k=LocateVex(G,u);
	for(int j=0;j<G.vexnum;++j)
	{		//���������ʼ�� 
		if(j!=k){
			close[j].adjvex=u;
			close[j].lowcost=G.arcs[k][j].adj;
		}
	}
	close[k].lowcost=0;			//��ʼ��U={u}
	for(int i=1;i<G.vexnum;++i)		//ѡ������G.vexnum-1������ 
	{
		k=minimum(close,G.vexnum);			//���T����һ���ڵ㣺��k���� 
		//��ʱclose[k].lowcost=
			//Min{close[vi].lowcost | close[vi].lowcost>0,vi��V-U 
		printf("%c%c\n",close[k].adjvex,G.vexs[k]);		//����������ı� 
		close[k].lowcost=0;			//��k���㲢��U�� 
		for(int j=0;j<G.vexnum;++j)
		{
			if(G.arcs[k][j].adj<close[j].lowcost)		//�µĶ��㲢��U������ѡ����С�ߡ�
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
	printf("��������Ҫ��ʼ�����Ķ���:\n");
	getchar();
	scanf("%c",&u); 
	MiniSpanTree_PRIM(G,u);
	return 0;
}
