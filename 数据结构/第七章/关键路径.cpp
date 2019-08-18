#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define StackSize 100
#define TURE 1
#define FLASE 0
#define OVERFLOW -2

/*-----------------------------------------数据结构--栈-------------------------------------------*/

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;
typedef int Status;

typedef struct {
	SElemType *base,*top;
	int stacksize;
}Sqstack;

Status InitStack(Sqstack &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status StackEmpty(Sqstack S)
{
	if(S.top==S.base)
		return TURE;
	else
		return FLASE;
}

Status GetTop(Sqstack S,SElemType &e)
{
	if(S.top==S.base){
		printf("栈已空！");
		return ERROR;
	}	
	e=*(S.top-1);
	return OK;
}
Status Push(Sqstack &S,SElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*(S.top++)=e;
	return OK;
}
Status Pop(Sqstack &S,SElemType &e)
{
	if(S.top==S.base){
		printf("栈中没有元素，不能出栈！");
		return ERROR;
	}	
	e=*(--S.top);
	return OK; 
}
int StackLength(Sqstack S)
{
    return S.top-S.base;
}
void ClearStack(Sqstack &S)    
{
	S.base=S.top=0;
}

/*-----------------------------------------数据结构--栈-------------------------------------------*/

/*----------------------------------------图的邻接表类型-------------------------------------------*/
typedef char VertexType[4];
typedef int InfoPtr;            /*定义为整型，为了存放权值*/
typedef int VRType;
#define MaxSize 50              /*最大顶点个数*/
typedef enum{DG,DN,UG,UN}GraphKind;     /*图的类型：有向图、有向网、无向图和无向网*/
typedef struct ArcNode          /*边结点的类型定义*/
{
    int adjvex;                 /*弧指向的顶点的位置*/
    InfoPtr *info;              /*弧的权值*/
    struct ArcNode *nextarc;    /*指示下一个与该顶点相邻接的顶点*/
}ArcNode;
typedef struct VNode            /*头结点的类型定义*/
{
    VertexType data;            /*用于存储顶点*/
    ArcNode *firstarc;          /*指示第一个与该顶点邻接的顶点*/
}VNode,AdjList[MaxSize];
typedef struct                  /*图的类型定义*/
{
    AdjList vertex;
    int vexnum,arcnum;          /*图的顶点数目与弧的数目*/
    GraphKind kind;             /*图的类型*/
}AdjGraph;


int LocateVertex(AdjGraph G,VertexType v)
/*返回图中顶点对应的位置*/
{
    for(int i=0;i<G.vexnum;i++)
        if(strcmp(G.vertex[i].data,v)==0)
            return i;
    return -1;
}
void CreateGraph(AdjGraph &G)
/*采用邻接表存储结构，创建有向网N*/
{
    int i,j,k,w;
    VertexType v1,v2;                   /*定义两个弧v1和v2*/
    ArcNode *p;
    printf("请输入图的顶点数,边数(以逗号分隔): ");
    scanf("%d,%d",&G.vexnum,&G.arcnum);
    printf("请输入%d个顶点的值:",G.vexnum);
    for(i=0;i<G.vexnum;i++)            /*将顶点存储在头结点中*/
    {
        scanf("%s",G.vertex[i].data);
        G.vertex[i].firstarc=NULL;     /*将相关联的顶点置为空*/
    }
    printf("请输入弧尾、弧头和权值(以空格作为分隔):\n");
    for(k=0;k<G.arcnum;k++)            /*建立边链表*/
    {
        scanf("%s%s%*c%d",v1,v2,&w);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        /*j为弧头i为弧尾创建邻接表*/
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
        *(p->info)=w;
        /*将p指向的结点插入到边表中*/
        p->nextarc=G.vertex[i].firstarc;
        G.vertex[i].firstarc=p;
    }
    G.kind=DN;
}

void DisplayGraph(AdjGraph G)
/*网的邻接矩阵N的输出*/
{
    int i;
    ArcNode *p;
    printf("该网中有%d个顶点：",G.vexnum);
    for(i=0;i<G.vexnum;i++)
        printf("%s ",G.vertex[i].data);
    printf("\n网中共有%d条弧:\n",G.arcnum);
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertex[i].firstarc;
        while(p)
        {
            printf("<%s,%s,%d> ",G.vertex[i].data,G.vertex[p->adjvex].data,*(p->info));
            p=p->nextarc;
        }
        printf("\n");
    }
}

void DestroyGraph(AdjGraph &G)
{
    int i;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;++i)        /*释放网中的边表结点*/
    {
        p=G.vertex[i].firstarc;    /*p指向边表的第一个结点*/
        if(p!=NULL)                 /*如果边表不为空，则释放边表的结点*/
        {
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    G.vexnum=0;                  /*将顶点数置为0*/
    G.arcnum=0;                  /*将边的数目置为0*/
}

/*----------------------------------------图的邻接表类型-------------------------------------------*/

int ve[MaxSize];                /*全局变量ve存放事件最早发生时间*/
Status TopologicalOrder(AdjGraph G,Sqstack &T){
/*采用邻接表存储结构的有向网G的拓扑排序，并求各顶点对应事件的最早发生时间ve(全局变量)*/
/*T为拓扑序列顶点栈，S为零入度顶点栈*/
/*如果G无回路，则用用栈T返回G的一个拓扑序列,且函数值为OK，否则为ERROR*/
    int i,k,count=0;
    Sqstack S;
    ArcNode *p;
    int indegree[MaxSize];      /*数组indegree存储各顶点的入度*/
    /*将图中各顶点的入度保存在数组indegree中*/
    for(i=0;i<G.vexnum;i++)     /*将数组indegree赋初值*/
        indegree[i]=0;
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertex[i].firstarc;
        while(p!=NULL)
        {
            k=p->adjvex;
            indegree[k]++;
            p=p->nextarc;
        }
    }
    InitStack(S);              /*初始化栈S*/
    printf("拓扑序列：");
    for(i=0;i<G.vexnum;i++)
        if(!indegree[i])        /*将入度为零的顶点入栈*/
            Push(S,i);
        InitStack(T);           /*初始化拓扑序列顶点栈*/
        for(i=0;i<G.vexnum;i++) /*初始化ve*/
            ve[i]=0;
        while(!StackEmpty(S))   /*如果栈S不为空*/
        {
            Pop(S,i);    /*从栈S将已拓扑排序的顶点j弹出*/
            printf("%s ",G.vertex[i].data);
            Push(T,i);     		/*j号顶点入逆拓扑排序栈T*/
            count++;            /*对入栈T的顶点计数*/
            for(p=G.vertex[i].firstarc;p;p=p->nextarc)  /*处理编号为i的顶点的每个邻接点*/
            {
                k=p->adjvex;            /*顶点序号为k*/
                if(--indegree[k]==0)    /*如果k的入度减1后变为0，则将k入栈S*/
                    Push(S,k);
                if(ve[i]+*(p->info)>ve[k]) /*计算顶点k对应的事件的最早发生时间*/
                    ve[k]=ve[i]+*(p->info);
            }
        }
        if(count<G.vexnum)
        {
            printf("该有向网有回路\n");
            return ERROR;
        }
        else
            return OK;
}

Status CriticalPath(AdjGraph G){/*输出G的关键路径*/
    int vl[MaxSize];                /*事件最晚发生时间*/
    Sqstack T;
    int i,j,k,e,l,dut,value,count,e1[MaxSize],e2[MaxSize];
    ArcNode *p;
    if(!TopologicalOrder(G,T))     /*如果有环存在，则返回ERROR*/
        return ERROR;
    value=ve[0];
    for(i=1;i<G.vexnum;i++)
        if(ve[i]>value)
            value=ve[i];            /*value为事件的最早发生时间的最大值*/
        for(i=0;i<G.vexnum;i++)     /*将顶点事件的最晚发生时间初始化*/
            vl[i]=value;
        while(!StackEmpty(T))       /*按逆拓扑排序求各顶点的vl值*/
            for(Pop(T,j),p=G.vertex[j].firstarc;p;p=p->nextarc){ /*弹出栈T的元素,赋给j,p指向j的后继事件k*/
                k=p->adjvex;
                dut=*(p->info);     /*dut为弧<j,k>的权值*/
                if(vl[k]-dut<vl[j]) /*计算事件j的最迟发生时间*/
                    vl[j]=vl[k]-dut;
            }
        printf("\n事件的最早发生时间和最晚发生时间\ni ve[i] vl[i]\n");
        for(i=0;i<G.vexnum;i++)     /*输出顶点对应的事件的最早发生时间最晚发生时间*/
            printf("%d   %d     %d\n",i,ve[i],vl[i]);
        printf("关键路径为：(");
        for(i=0;i<G.vexnum;i++)     /*输出关键路径经过的顶点*/
            if(ve[i]==vl[i])
                printf("%s ",G.vertex[i].data);
        printf(")\n");
        count=0;
        printf("活动最早开始时间和最晚开始时间\n   弧    e   l   l-e\n");
        for(j=0;j<G.vexnum;j++)     /*求活动的最早开始时间e和最晚开始时间l*/
            for(p=G.vertex[j].firstarc;p;p=p->nextarc)
            {
                k=p->adjvex;
                dut=*(p->info);     /*dut为弧<j,k>的权值*/
                e=ve[j];            /*e就是活动<j,k>的最早开始时间*/
                l=vl[k]-dut;        /*l就是活动<j,k>的最晚开始时间*/
                printf("%s→%s %3d %3d %3d\n",G.vertex[j].data,G.vertex[k].data,e,l,l-e);
                if(e==l)            /*将关键活动保存在数组中*/
                {
                    e1[count]=j;
                    e2[count]=k;
                    count++;
                }
            }
        printf("关键活动为：");
        for(k=0;k<count;k++)        /*输出关键路径*/
        {
            i=e1[k];
            j=e2[k];
            printf("(%s→%s) ",G.vertex[i].data,G.vertex[j].data);
        }
        printf("\n");
    return OK;
}


int main(int argc,char **argv){
    AdjGraph G;
    CreateGraph(G);        /*采用邻接表存储结构创建有向网G*/
    DisplayGraph(G);        /*输出有向网G*/
    CriticalPath(G);        /*求网G的关键路径*/
    DestroyGraph(G);       /*销毁网G*/
    return 0;
}


