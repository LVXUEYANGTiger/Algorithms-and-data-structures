#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20
#define MAX_NUM 5  //���趥�������5���ַ����
#define INFINITY 0    //#define INFINITY INT_MAX  ���ֵ��#include <limits.h>,������������0��ʾ
#define OK 1
#define FALSE 0
#define ERROR 0
#define TRUE 1
#define OVERFLOW -2
typedef enum{DG,DN,UDG,UDN}GraphKind;  //{����ͼ��������������ͼ��������}
typedef int InfoType;
typedef char VertexType[MAX_NUM];  //�������ַ�����ʾ
typedef int Status;
typedef struct ArcNode
{
	int adjvex;  //�û���ָ��Ķ����λ��
	struct ArcNode *nextarc;  //ָ����һ������ָ��
	InfoType *info;  //�û������Ϣ��ָ��,��ʾ��ʱ����ָʾ��Ȩֵ��������Ϊ��
}ArcNode;  //����
 
typedef struct VNode
{
	VertexType data;  //������Ϣ
	ArcNode *firstarc;  //ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];  //ͷ���
 
typedef struct  
{
	AdjList vertices;
	int vexnum, arcnum;  //ͼ�ĵ�ǰ�������뻡��
	int kind;  //ͼ�������־
}ALGraph;  //ͼ�����ݽṹ
 
int LocateVex(ALGraph &G, VertexType u)
{
	//��ʼ������ͼG���ڣ�u��G�ж�������ͬ����
	//�����������G�д��ڶ���u���򷵻ظö������ͼ�е�λ�ã����򷵻�-1
	for(int i=0; i < G.vexnum; ++i)
	{
		if(strcmp(u, G.vertices[i].data) == 0)
			return i;
	}
	return -1;
}
Status CreateUDG(ALGraph &G)
{
	//�����ڽӱ��ʾ������������ͼ
	printf("\n��������ͼ...\n\n");
	printf("�����붥������뻡����");
	scanf("%d%d",&G.vexnum, &G.arcnum);
	getchar();
	int i;
	printf("������%d���������Ϣ������֮���Կո����:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)
	{
		scanf("%s",G.vertices[i].data);
		G.vertices[i].firstarc=NULL;
	}
	
	printf("����������%d����������������������(�����ʽ:����1 ����2(Enter))\n",G.arcnum);
	VertexType v1,v2;
	int m,n;
	for(i=0; i<G.arcnum; ++i)
	{
		getchar(); //ȥ����������Ļ��з�
		scanf("%s%s",v1,v2);
		m=LocateVex(G,v1);
		n=LocateVex(G,v2);
		if(m==-1 || n == -1)
			return ERROR;
		ArcNode *p1,*p2;
		p1=(ArcNode*)malloc(sizeof(ArcNode));  //���ٱ��㣬��Ŷ���Ļ���Ϣ
		p2=(ArcNode*)malloc(sizeof(ArcNode));
		if(!p1 || !p2)
			exit(OVERFLOW);
		p1->adjvex = m;
		p1->info = NULL;  //ͼ��Ȩֵ��ֱ������Ϊ��
		p1->nextarc = G.vertices[n].firstarc; //��ͷ�����붥����صĻ�
		G.vertices[n].firstarc = p1;
 
		p2->adjvex = n;
		p2->info = NULL;
		p2->nextarc = G.vertices[m].firstarc;
		G.vertices[m].firstarc = p2;
	}
	G.kind = UDG;
	return OK;
}
 
VertexType& GetVex(ALGraph &G,int v)
{
	//��ʼ������ͼG���ڣ�v��G��ĳ������
	//�������Ϊv�Ķ����ֵ
	if(v<0 || v>=G.vexnum)
		exit(OVERFLOW);
	return G.vertices[v].data;
}
 
Status PutVex(ALGraph &G,VertexType v,VertexType value)
{
	//�Զ���v���и�ֵvalue
	int i=LocateVex(G,v);
	if(i < 0)
		return ERROR;
	strcpy(G.vertices[i].data, value);
	return OK;
}
 
int FirstAdjVex(ALGraph &G,VertexType v)
{
	//����v�ĵ�һ���ڽӶ��㣬��������G��û���ڽӶ��㣬�򷵻�-1
	int i=LocateVex(G,v);
	ArcNode *p;
	if(i<0)
		return -1;
	p=G.vertices[i].firstarc;
	if(!p)
		return -1;
	return p->adjvex;
}
 
int NextAdjVex(ALGraph &G, VertexType v, VertexType w)
{
	//����v�ģ������w�ģ���һ���ڽӶ��㣬��w��v�����һ���ڽӵ㣬����-1
	int i=LocateVex(G,v);
	int j=LocateVex(G,w);
	if(i<0 || j<0)
		exit(OVERFLOW);
	ArcNode *p;
	p = G.vertices[i].firstarc;
	while(p && p->adjvex!=j)
	{
		p=p->nextarc;
	}
	if(!p || !p->nextarc)
		return -1;
	return p->nextarc->adjvex;
}
 
Status InsertVex(ALGraph &G, VertexType v)
{
	//����һ���¶��㣬���������ӹ�ϵ������
	strcpy(G.vertices[G.vexnum].data, v);
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
	return OK;
}
 
Status InsertArc(ALGraph &G, VertexType v, VertexType w)
{
	//��G������<v,w>����G������ģ�������Գƻ�<w,v>
	int i=LocateVex(G,v);
	int j=LocateVex(G,w);
	if(i<0 || j<0)
		return ERROR;
	ArcNode *p, *q;
	p=(ArcNode*)malloc(sizeof(ArcNode));
	q=(ArcNode*)malloc(sizeof(ArcNode));
	if(!p || !q)
		exit(OVERFLOW);
	p->info=NULL;
	p->adjvex = i;
	
	q->info=NULL;
	q->adjvex = j;
 
	p->nextarc=G.vertices[j].firstarc;
	G.vertices[j].firstarc = p;
 
	q->nextarc=G.vertices[i].firstarc;
	G.vertices[i].firstarc=q;
 
	++G.arcnum;
	return OK;
}
 
 
void Display(ALGraph &G)//���ڽӱ����ͼ
{
	ArcNode *p;
	for(int i=0; i < G.vexnum; ++i)
	{
		printf("%d:%s->", i, G.vertices[i].data);
		p=G.vertices[i].firstarc;
		while(p)
		{
			printf("%-3d->",p->adjvex);
			p=p->nextarc;
		}
		printf("NULL\n");
	}
}
int main()
{
	ALGraph G;
	CreateUDG(G);
	Display(G);
 
	VertexType a,value;
	printf("��������Ҫ���ĵĽ��ֵ�Լ����ĵ�ֵ��");
	scanf("%s%s",a,value);
	PutVex(G,a,value);
	getchar();
	Display(G);
 
	printf("��������Ҫ����Ķ���:");
	scanf("%s",a);
	getchar();
	InsertVex(G,a);
	Display(G);
 
	printf("��������Ҫ����Ļ�����������������:");
	scanf("%s%s",a,value);
	getchar();
	InsertArc(G,a,value);
	Display(G);
 
	return 0;
}

