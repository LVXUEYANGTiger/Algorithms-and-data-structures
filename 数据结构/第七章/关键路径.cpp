#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define StackSize 100
#define TURE 1
#define FLASE 0
#define OVERFLOW -2

/*-----------------------------------------���ݽṹ--ջ-------------------------------------------*/

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
		printf("ջ�ѿգ�");
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
		printf("ջ��û��Ԫ�أ����ܳ�ջ��");
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

/*-----------------------------------------���ݽṹ--ջ-------------------------------------------*/

/*----------------------------------------ͼ���ڽӱ�����-------------------------------------------*/
typedef char VertexType[4];
typedef int InfoPtr;            /*����Ϊ���ͣ�Ϊ�˴��Ȩֵ*/
typedef int VRType;
#define MaxSize 50              /*��󶥵����*/
typedef enum{DG,DN,UG,UN}GraphKind;     /*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef struct ArcNode          /*�߽������Ͷ���*/
{
    int adjvex;                 /*��ָ��Ķ����λ��*/
    InfoPtr *info;              /*����Ȩֵ*/
    struct ArcNode *nextarc;    /*ָʾ��һ����ö������ڽӵĶ���*/
}ArcNode;
typedef struct VNode            /*ͷ�������Ͷ���*/
{
    VertexType data;            /*���ڴ洢����*/
    ArcNode *firstarc;          /*ָʾ��һ����ö����ڽӵĶ���*/
}VNode,AdjList[MaxSize];
typedef struct                  /*ͼ�����Ͷ���*/
{
    AdjList vertex;
    int vexnum,arcnum;          /*ͼ�Ķ�����Ŀ�뻡����Ŀ*/
    GraphKind kind;             /*ͼ������*/
}AdjGraph;


int LocateVertex(AdjGraph G,VertexType v)
/*����ͼ�ж����Ӧ��λ��*/
{
    for(int i=0;i<G.vexnum;i++)
        if(strcmp(G.vertex[i].data,v)==0)
            return i;
    return -1;
}
void CreateGraph(AdjGraph &G)
/*�����ڽӱ�洢�ṹ������������N*/
{
    int i,j,k,w;
    VertexType v1,v2;                   /*����������v1��v2*/
    ArcNode *p;
    printf("������ͼ�Ķ�����,����(�Զ��ŷָ�): ");
    scanf("%d,%d",&G.vexnum,&G.arcnum);
    printf("������%d�������ֵ:",G.vexnum);
    for(i=0;i<G.vexnum;i++)            /*������洢��ͷ�����*/
    {
        scanf("%s",G.vertex[i].data);
        G.vertex[i].firstarc=NULL;     /*��������Ķ�����Ϊ��*/
    }
    printf("�����뻡β����ͷ��Ȩֵ(�Կո���Ϊ�ָ�):\n");
    for(k=0;k<G.arcnum;k++)            /*����������*/
    {
        scanf("%s%s%*c%d",v1,v2,&w);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        /*jΪ��ͷiΪ��β�����ڽӱ�*/
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
        *(p->info)=w;
        /*��pָ��Ľ����뵽�߱���*/
        p->nextarc=G.vertex[i].firstarc;
        G.vertex[i].firstarc=p;
    }
    G.kind=DN;
}

void DisplayGraph(AdjGraph G)
/*�����ڽӾ���N�����*/
{
    int i;
    ArcNode *p;
    printf("��������%d�����㣺",G.vexnum);
    for(i=0;i<G.vexnum;i++)
        printf("%s ",G.vertex[i].data);
    printf("\n���й���%d����:\n",G.arcnum);
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
    for(i=0;i<G.vexnum;++i)        /*�ͷ����еı߱���*/
    {
        p=G.vertex[i].firstarc;    /*pָ��߱�ĵ�һ�����*/
        if(p!=NULL)                 /*����߱�Ϊ�գ����ͷű߱�Ľ��*/
        {
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    G.vexnum=0;                  /*����������Ϊ0*/
    G.arcnum=0;                  /*���ߵ���Ŀ��Ϊ0*/
}

/*----------------------------------------ͼ���ڽӱ�����-------------------------------------------*/

int ve[MaxSize];                /*ȫ�ֱ���ve����¼����緢��ʱ��*/
Status TopologicalOrder(AdjGraph G,Sqstack &T){
/*�����ڽӱ�洢�ṹ��������G���������򣬲���������Ӧ�¼������緢��ʱ��ve(ȫ�ֱ���)*/
/*TΪ�������ж���ջ��SΪ����ȶ���ջ*/
/*���G�޻�·��������ջT����G��һ����������,�Һ���ֵΪOK������ΪERROR*/
    int i,k,count=0;
    Sqstack S;
    ArcNode *p;
    int indegree[MaxSize];      /*����indegree�洢����������*/
    /*��ͼ�и��������ȱ���������indegree��*/
    for(i=0;i<G.vexnum;i++)     /*������indegree����ֵ*/
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
    InitStack(S);              /*��ʼ��ջS*/
    printf("�������У�");
    for(i=0;i<G.vexnum;i++)
        if(!indegree[i])        /*�����Ϊ��Ķ�����ջ*/
            Push(S,i);
        InitStack(T);           /*��ʼ���������ж���ջ*/
        for(i=0;i<G.vexnum;i++) /*��ʼ��ve*/
            ve[i]=0;
        while(!StackEmpty(S))   /*���ջS��Ϊ��*/
        {
            Pop(S,i);    /*��ջS������������Ķ���j����*/
            printf("%s ",G.vertex[i].data);
            Push(T,i);     		/*j�Ŷ���������������ջT*/
            count++;            /*����ջT�Ķ������*/
            for(p=G.vertex[i].firstarc;p;p=p->nextarc)  /*������Ϊi�Ķ����ÿ���ڽӵ�*/
            {
                k=p->adjvex;            /*�������Ϊk*/
                if(--indegree[k]==0)    /*���k����ȼ�1���Ϊ0����k��ջS*/
                    Push(S,k);
                if(ve[i]+*(p->info)>ve[k]) /*���㶥��k��Ӧ���¼������緢��ʱ��*/
                    ve[k]=ve[i]+*(p->info);
            }
        }
        if(count<G.vexnum)
        {
            printf("���������л�·\n");
            return ERROR;
        }
        else
            return OK;
}

Status CriticalPath(AdjGraph G){/*���G�Ĺؼ�·��*/
    int vl[MaxSize];                /*�¼�������ʱ��*/
    Sqstack T;
    int i,j,k,e,l,dut,value,count,e1[MaxSize],e2[MaxSize];
    ArcNode *p;
    if(!TopologicalOrder(G,T))     /*����л����ڣ��򷵻�ERROR*/
        return ERROR;
    value=ve[0];
    for(i=1;i<G.vexnum;i++)
        if(ve[i]>value)
            value=ve[i];            /*valueΪ�¼������緢��ʱ������ֵ*/
        for(i=0;i<G.vexnum;i++)     /*�������¼���������ʱ���ʼ��*/
            vl[i]=value;
        while(!StackEmpty(T))       /*��������������������vlֵ*/
            for(Pop(T,j),p=G.vertex[j].firstarc;p;p=p->nextarc){ /*����ջT��Ԫ��,����j,pָ��j�ĺ���¼�k*/
                k=p->adjvex;
                dut=*(p->info);     /*dutΪ��<j,k>��Ȩֵ*/
                if(vl[k]-dut<vl[j]) /*�����¼�j����ٷ���ʱ��*/
                    vl[j]=vl[k]-dut;
            }
        printf("\n�¼������緢��ʱ���������ʱ��\ni ve[i] vl[i]\n");
        for(i=0;i<G.vexnum;i++)     /*��������Ӧ���¼������緢��ʱ��������ʱ��*/
            printf("%d   %d     %d\n",i,ve[i],vl[i]);
        printf("�ؼ�·��Ϊ��(");
        for(i=0;i<G.vexnum;i++)     /*����ؼ�·�������Ķ���*/
            if(ve[i]==vl[i])
                printf("%s ",G.vertex[i].data);
        printf(")\n");
        count=0;
        printf("����翪ʼʱ�������ʼʱ��\n   ��    e   l   l-e\n");
        for(j=0;j<G.vexnum;j++)     /*�������翪ʼʱ��e������ʼʱ��l*/
            for(p=G.vertex[j].firstarc;p;p=p->nextarc)
            {
                k=p->adjvex;
                dut=*(p->info);     /*dutΪ��<j,k>��Ȩֵ*/
                e=ve[j];            /*e���ǻ<j,k>�����翪ʼʱ��*/
                l=vl[k]-dut;        /*l���ǻ<j,k>������ʼʱ��*/
                printf("%s��%s %3d %3d %3d\n",G.vertex[j].data,G.vertex[k].data,e,l,l-e);
                if(e==l)            /*���ؼ��������������*/
                {
                    e1[count]=j;
                    e2[count]=k;
                    count++;
                }
            }
        printf("�ؼ��Ϊ��");
        for(k=0;k<count;k++)        /*����ؼ�·��*/
        {
            i=e1[k];
            j=e2[k];
            printf("(%s��%s) ",G.vertex[i].data,G.vertex[j].data);
        }
        printf("\n");
    return OK;
}


int main(int argc,char **argv){
    AdjGraph G;
    CreateGraph(G);        /*�����ڽӱ�洢�ṹ����������G*/
    DisplayGraph(G);        /*���������G*/
    CriticalPath(G);        /*����G�Ĺؼ�·��*/
    DestroyGraph(G);       /*������G*/
    return 0;
}


