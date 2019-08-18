#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20
#define MAX_NUM 5  //假设顶点最多由5个字符组成
#define INFINITY 0    //#define INFINITY INT_MAX  最大值，#include <limits.h>,本例中我们用0表示
#define OK 1
#define FALSE 0
#define ERROR 0
#define TRUE 1
#define OVERFLOW -2
typedef enum{DG,DN,UDG,UDN}GraphKind;  //{有向图，有向网，无向图，无向网}
typedef int InfoType;
typedef char VertexType[MAX_NUM];  //顶点用字符串表示
typedef int Status;
typedef struct ArcNode
{
	int adjvex;  //该弧所指向的顶点的位置
	struct ArcNode *nextarc;  //指向下一条弧的指针
	InfoType *info;  //该弧相关信息的指针,表示网时用来指示其权值，否则置为空
}ArcNode;  //表结点
 
typedef struct VNode
{
	VertexType data;  //顶点信息
	ArcNode *firstarc;  //指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];  //头结点
 
typedef struct  
{
	AdjList vertices;
	int vexnum, arcnum;  //图的当前顶点数与弧数
	int kind;  //图的种类标志
}ALGraph;  //图的数据结构
 
int LocateVex(ALGraph &G, VertexType u)
{
	//初始条件：图G存在，u和G中顶点有相同特征
	//操作结果：若G中存在顶点u，则返回该顶点的在图中的位置，否则返回-1
	for(int i=0; i < G.vexnum; ++i)
	{
		if(strcmp(u, G.vertices[i].data) == 0)
			return i;
	}
	return -1;
}
Status CreateUDG(ALGraph &G)
{
	//采用邻接表表示法，构造无向图
	printf("\n创建无向图...\n\n");
	printf("请输入顶点个数与弧数：");
	scanf("%d%d",&G.vexnum, &G.arcnum);
	getchar();
	int i;
	printf("请输入%d个顶点的信息，顶点之间以空格相隔:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)
	{
		scanf("%s",G.vertices[i].data);
		G.vertices[i].firstarc=NULL;
	}
	
	printf("请依次输入%d条弧各自依附的两个顶点(输入格式:顶点1 顶点2(Enter))\n",G.arcnum);
	VertexType v1,v2;
	int m,n;
	for(i=0; i<G.arcnum; ++i)
	{
		getchar(); //去掉输入流里的换行符
		scanf("%s%s",v1,v2);
		m=LocateVex(G,v1);
		n=LocateVex(G,v2);
		if(m==-1 || n == -1)
			return ERROR;
		ArcNode *p1,*p2;
		p1=(ArcNode*)malloc(sizeof(ArcNode));  //开辟表结点，存放顶点的弧信息
		p2=(ArcNode*)malloc(sizeof(ArcNode));
		if(!p1 || !p2)
			exit(OVERFLOW);
		p1->adjvex = m;
		p1->info = NULL;  //图无权值，直接置其为空
		p1->nextarc = G.vertices[n].firstarc; //表头插入与顶点相关的弧
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
	//初始条件：图G存在，v是G中某个顶点
	//返回序号为v的顶点的值
	if(v<0 || v>=G.vexnum)
		exit(OVERFLOW);
	return G.vertices[v].data;
}
 
Status PutVex(ALGraph &G,VertexType v,VertexType value)
{
	//对顶点v进行赋值value
	int i=LocateVex(G,v);
	if(i < 0)
		return ERROR;
	strcpy(G.vertices[i].data, value);
	return OK;
}
 
int FirstAdjVex(ALGraph &G,VertexType v)
{
	//返回v的第一个邻接顶点，若顶点在G中没有邻接顶点，则返回-1
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
	//返回v的（相对于w的）下一个邻接顶点，若w是v的最后一个邻接点，返回-1
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
	//增加一个新顶点，但并不增加关系，即弧
	strcpy(G.vertices[G.vexnum].data, v);
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
	return OK;
}
 
Status InsertArc(ALGraph &G, VertexType v, VertexType w)
{
	//在G中增添弧<v,w>，若G是无向的，则还增添对称弧<w,v>
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
 
 
void Display(ALGraph &G)//用邻接表输出图
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
	printf("请输入你要更改的结点值以及更改的值：");
	scanf("%s%s",a,value);
	PutVex(G,a,value);
	getchar();
	Display(G);
 
	printf("请输入你要插入的顶点:");
	scanf("%s",a);
	getchar();
	InsertVex(G,a);
	Display(G);
 
	printf("请输入你要插入的弧所依附的两个顶点:");
	scanf("%s%s",a,value);
	getchar();
	InsertArc(G,a,value);
	Display(G);
 
	return 0;
}

