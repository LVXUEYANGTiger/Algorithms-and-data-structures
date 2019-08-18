#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTEX_NUM 20   //最大顶点数
#define MAX MAX_VERTEX_NUM
 
#define INFINITY INT_MAX  //用无穷表示顶点之间无关系
 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int Status;
 
/*----------------用到的数据结构---队-------------------*/
typedef char QElemType;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct  
{
	QueuePtr front;  //队头
	QueuePtr rear;  //队尾
}LinkQueue;
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
 
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}
 
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)
		return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}
 
int EmptyQueue(LinkQueue &Q)
{
	if(Q.front == Q.rear )
		return TRUE;
	return FALSE;
}
 
/*---------------------数据结构--队-----------------*/
 
 
 
typedef int VRType;//顶点关系类型
typedef int InfoType;  
typedef char VertexType; //顶点值类型
typedef enum{DG, DN, UDG, UDN}GraphKind;  //{有向图，有向网，无向图，无向网}
typedef struct ArcCell
{
	VRType adj;  //VRType是顶点关系类型，对无权图，用1或0表示相邻否
				//对带权图，则为权值类型
	InfoType *info;  //该弧相关信息的指针
}ArcCell, AdjMatric[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 
typedef struct  
{
	VertexType vexs[MAX_VERTEX_NUM];  //顶点向量
	AdjMatric arcs;  //邻接矩阵
	int vexnum, arcnum;  //图的当前顶点数与弧数
	GraphKind kind;  //图的种类标志
}MGraph;
 
bool visited[MAX];  //访问标志数组
Status (*VisitFunc)(MGraph &G,int v);  //函数变量
 
int LocateVex(const MGraph &G, VertexType u)
{
	//初始条件：图G存在，u与G中顶点有相同特征
	//操作结果：若G中存在顶点u，则返回该顶点在图中位置，否则返回-1
	for(int i=0; i < G.vexnum; ++i)
	{
		if(u == (G.vexs[i]))
			return i;
	}
	return -1;
}
 
Status CreateDG(MGraph &G)//构造有向图
{
	//采用数组（邻接矩阵）表示法，构造有向图G
	printf("请输入有向图的顶点数与边数:\n");
	scanf("%d%d",&G.vexnum, &G.arcnum);  
	int i,j;
	printf("请输入%d个顶点的值:\n",G.vexnum);
	getchar();//取出输入流中的回车符
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%c",&G.vexs[i]);
	}
	//scanf("%*c"); //跳过输入流中的回车符
	//char buffer = getchar(); //取出输入流中的回车符
	for(i=0; i<G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;  //表示图
			G.arcs[i][j].info = NULL;  //表示无边的相关信息
		}
	}
	int k;
	VertexType v1, v2;//顶点的临时存储变量
	for(k=0; k<G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点:\n", k+1);
		getchar(); //取出输入流中的回车符
		scanf("%c%c",&v1, &v2); //%*c  跳过回车符
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //无此顶点，构造失败，返回出错信息
		G.arcs[i][j].adj = 1;
		//因为边没有其他的相关信息，G.arcs[i][j].info== NULL，保持不变
	}
	G.kind = DG;  //有向图
	return OK;
}
 
Status CreateDN(MGraph &G)
{
	//采用数组（邻接矩阵）表示法，构造有向网G
	printf("请输入有向网的顶点数与边数：\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	getchar();//取出输入流中的回车符
	int i,j;
	printf("请输入%d个顶点的值:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)//构造顶点向量
	{
		scanf("%c",&G.vexs[i]);
	}
	for(i=0; i<G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;  
			G.arcs[i][j].info = NULL;  //表示无边的相关信息
		}
	}
	
	int k;
	VertexType v1, v2;//顶点的临时存储变量
	VRType w;  //顶点关系，此时代表权值
	for(k=0; k<G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点及权值:\n", k+1);
		getchar();//取出输入流中的回车符
		scanf("%c%c%d",&v1, &v2, &w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //无此顶点，构造失败，返回出错信息
		G.arcs[i][j].adj = w;
		//因为边没有其他的相关信息，G.arcs[i][j].info== NULL，保持不变
	}
	G.kind = DN;  //有向网
	return OK;
}
 
Status CreateUDG(MGraph &G)//构造无向图
{
	//采用数组（邻接矩阵）表示法，构造无向图G
	printf("请输入无向图的顶点数与边数:\n");
	scanf("%d%d",&G.vexnum, &G.arcnum);  
	int i,j;
	printf("请输入%d个顶点的值:\n",G.vexnum);
	getchar();//取出输入流中的回车符
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%c",&G.vexs[i]);
	}
	//scanf("%*c"); //跳过输入流中的回车符
	//char buffer = getchar(); //取出输入流中的回车符
	for(i=0; i<G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;  //表示图
			G.arcs[i][j].info = NULL;  //表示无边的相关信息
		}
	}
	int k;
	VertexType v1, v2;//顶点的临时存储变量
	for(k=0; k<G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点:\n", k+1);
		getchar(); //取出输入流中的回车符
		scanf("%c%c",&v1, &v2); //%*c  跳过回车符
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //无此顶点，构造失败，返回出错信息
		G.arcs[i][j].adj = 1;
		G.arcs[j][i].adj = G.arcs[i][j].adj;  //对称弧的信息
		//因为边没有其他的相关信息，G.arcs[i][j].info== NULL，保持不变
	}
	G.kind = UDG;  //无向图
	return OK;
}
 
 
Status CreateUDN(MGraph &G)
{
	//采用数组（邻接矩阵）表示法，构造无向网G
	printf("请输入无向网的顶点数与边数：\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	getchar();//取出输入流中的回车符
	int i,j;
	printf("请输入%d个顶点的值:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)//构造顶点向量
	{
		scanf("%c",&G.vexs[i]);
	}
	for(i=0; i<G.vexnum; ++i)  //初始化邻接矩阵
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;  
			G.arcs[i][j].info = NULL;  //表示无边的相关信息
		}
	}
 
	int k;
	VertexType v1, v2;//顶点的临时存储变量
	VRType w;  //顶点关系，此时代表权值
	for(k=0; k<G.arcnum; ++k) //构造邻接矩阵
	{
		printf("请输入第%d条边依附的顶点及权值:\n", k+1);
		getchar();//取出输入流中的回车符
		scanf("%c%c%d",&v1, &v2, &w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //无此顶点，构造失败，返回出错信息
		G.arcs[i][j].adj = w;
		//因为边没有其他的相关信息，G.arcs[i][j].info== NULL，保持不变
		G.arcs[j][i].adj = G.arcs[i][j].adj;  //置<v1,v2>的对称弧<v2,v1>;
	}
	G.kind = UDN;  //无向网
	return OK;
}
 
Status CreateGraph(MGraph &G)
{
	//构造图G
	printf("请输入构造的类型：(0:有向图,1:有向网，2:无向图，3:无向网):");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
	case DG:return CreateDG(G);  //构造有向图
	case DN:return CreateDN(G);  //构造有向网
	case UDG:return CreateUDG(G);  //构造无向图
	case UDN:return CreateUDN(G);  //构造无向网
	default:return ERROR;
	}
}
VertexType GetVex(MGraph &G, int v)
{
	//初始条件：图G存在，v是G中某个顶点的序号
	//操作结果：若存在，则返回其值,否则返回空
	if(v >= G.vexnum || v < 0)
		return NULL;
	return G.vexs[v];
}
 
Status PutVex(MGraph &G,int v, VertexType value)
{
	//初始条件：图G存在，v是G中某个顶点的序号
	//操作结果：对v赋值value
	if(v >= G.vexnum || v < 0)
		return ERROR;
	G.vexs[v] = value;
	return OK;
}
 
int FirstAdjVex(MGraph &G, VertexType v)
{
	//初始条件：图G存在，v是G中某个顶点
	//操作结果：返回v的第一个邻接顶点，若顶点在G中没有邻接顶点，则返回"空"
	int k = LocateVex(G,v);
	if(k == -1)//无此顶点
		return -1;
	int adjValue = 0; 
	if(G.kind == DN || G.kind == UDN)
		adjValue = INFINITY;
	
	for(int i=0; i < G.vexnum; ++i)
	{
		if(G.arcs[k][i].adj != adjValue)
			return i;
	}
	return -1;
}
 
int NextAdjVex(MGraph &G, VertexType v, VertexType w)
{
	//初始条件：图G存在，v是G中某个顶点，w是v的邻接顶点
	//操作结果：返回v的（相对于w的）下一个邻接顶点。若w是v的最后一个邻接点，则返回“空”
	int k1=LocateVex(G,v);
	int k2=LocateVex(G,w);
 
	if(k1 == -1 || k2 == -1)//无此顶点
	{
		return -1;
	}
	int adjValue = 0; 
	if(G.kind == DN || G.kind == UDN)
		adjValue = INFINITY;
	for(int i=k2+1; i < G.vexnum; ++i)
	{
		if(G.arcs[k1][i].adj != adjValue)
		{
			return i;
		}
	}
	return -1;
 
}
 
Status InsertVex(MGraph &G, VertexType v)
{
	//初始条件：图G存在，v和图G某个顶点有相同的特征
	//操作结果：在图G中增添新顶点v（此时不增加关系）
	Status i=0;
	G.vexs[G.vexnum] = v;  //赋于顶点值
	for(i=0; i <=G.vexnum; ++i)
	{
		if(G.kind%2==0)//图
		{
			G.arcs[G.vexnum][i].adj = 0;
			G.arcs[i][G.vexnum].adj = 0;
		}
		else  //网
		{
			G.arcs[G.vexnum][i].adj = INFINITY;
			G.arcs[i][G.vexnum].adj = INFINITY;
		}
	}
	G.arcs[G.vexnum][i].info = NULL; //初始化该弧的相关信息
	G.arcs[i][G.vexnum].info = NULL; //初始化该弧的相关信息
	G.vexnum++;
	
	return OK;
}
 
Status DeleteVex(MGraph &G, VertexType v)
{
	//初始条件：图G存在，v是G中某个顶点
	//操作结果：删除G中顶点v及其相关的弧
	int k = LocateVex(G,v);
	if(k == -1)
		return ERROR; //无此结点
	//1.从顶点向量中删除该顶点
	int i,j;
	for(i=k; i < G.vexnum-1; ++i)
	{
		G.vexs[i] = G.vexs[i+1];
	}
 
	//2.删除边的关系
	for(i=k; i < G.vexnum-1; ++i)
	{
		for(j=0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = G.arcs[i+1][j].adj;
			//因为没有设弧的相关信息，就不考虑G.arcs[][].info了
		}
	}
	for(j=k; j < G.vexnum-1; ++j)
	{
		for(i=0; i < G.vexnum; ++i)
		{
			G.arcs[i][j].adj = G.arcs[i][j+1].adj;
			//因为没有设弧的相关信息，就不考虑G.arcs[][].info了
		}
	}
 
	--G.arcnum;  //边数减1
	--G.vexnum;  //顶点数减1
	return OK;
}
 
Status InsertArc(MGraph &G, VertexType v, VertexType w)
{
	//初始条件：图G存在，v和w是G中两个顶点
	//操作结果：在G中增添弧<v,w>，若是无向的，则还增添对称弧
	int k1= LocateVex(G,v);
	int k2= LocateVex(G,w);
	if(k1==-1 || k2==-1)
		return ERROR;  //图中不存在v或w
	if(G.kind%2 == 1)//网
	{
		printf("请输入该弧的权值:");
		scanf("%d",&G.arcs[k1][k2].adj);
	}
	else // 图
	{
		G.arcs[k1][k2].adj = 1;
	}
 
	if(G.kind > 1) //无向
	{
		G.arcs[k2][k1].adj = G.arcs[k1][k2].adj;
	}
	++G.arcnum;  //弧数加1
	return OK;
	
}
 
Status DeleteArc(MGraph &G, VertexType v, VertexType w)
{
	//初始条件：图G存在，v和w是G中两个顶点
	//操作结果：在G中删除弧<v,w>，若是无向的，则还删除对称弧
	int k1= LocateVex(G,v);
	int k2= LocateVex(G,w);
	if(k1==-1 || k2==-1)
		return ERROR;  //图中不存在v或w
	if(G.kind%2 == 1)//网
	{
		G.arcs[k1][k2].adj = INFINITY;
	}
	else // 图
	{
		G.arcs[k1][k2].adj = 0;
	}
	
	if(G.kind > 1) //无向
	{
		G.arcs[k2][k1].adj = G.arcs[k1][k2].adj;
	}
	--G.arcnum;  //弧数加1
	return OK;
 
}
 
void DFS(MGraph G, int v)
{
	//从第v个顶点出发递归地深度优先遍历图G
	visited[v] = TRUE;
	VisitFunc(G,v);  //访问第v个顶点
	for(int w = FirstAdjVex(G,GetVex(G,v)); w >= 0; w = NextAdjVex(G,GetVex(G,v),GetVex(G,w)))
		if(!visited[w])
			DFS(G,w);  //对v的尚未访问的邻接顶点w递归调用DFS
}
 
void DFSTraverse(MGraph G, Status(*Visit)(MGraph &G,int v))//对图作深度优先遍历
{
	VisitFunc = Visit;  //使用全局变量VisitFunc，使DFS不必设函数指针参数
	Status v=0;
	for(v=0; v < G.vexnum; ++v)
	{
		visited[v] = FALSE;  //访问标志数组初始化
	}
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visited[v])
			DFS(G,v);  //对尚未访问的顶点调用DFS
	}
}
 
void BFSTraverse(MGraph G, Status(*Visit)(MGraph &G,int v))//对图作广度优先遍历
{
	int BFSvisited[MAX],i;
	for(i = 0; i<G.vexnum; ++i)
	{
		BFSvisited[i] = FALSE;//初始化辅助访问数组,开始顶点均为未访问的标志
	}
	LinkQueue Q;
	InitQueue(Q); //初始化辅助队列Q
	for(i=0; i < G.vexnum; ++i)
	{
		if(!BFSvisited[i])//序号为i的顶点未访问
		{
			BFSvisited[i] = TRUE;
			Visit(G,i);
			EnQueue(Q,GetVex(G,i));//序号为i的顶点入队
			while(!EmptyQueue(Q))
			{
				QElemType u;
				DeQueue(Q,u);
				for(int w=FirstAdjVex(G,u); w >=0; w=NextAdjVex(G,u,GetVex(G,w)))
				{
					if(!BFSvisited[w])
					{
						BFSvisited[w] = TRUE;
						Visit(G,w);
						EnQueue(Q,GetVex(G,w));
					}
				}
			}
		}
	}
}
 
Status VisitVex(MGraph &G,int v)
{
	//访问序号为v的顶点
	printf("%3c",G.vexs[v]);
	return OK;
}
void DisplayVexValue(const MGraph &G)//显示所有的顶点
{
	printf("顶点为：");
	for(int i=0; i < G.vexnum; ++i)
		printf("%c\t",G.vexs[i]);
	printf("\n");
}
 
void DisplayAdjMatrix(const MGraph &G)
{
	//输出邻接矩阵
	printf("\n邻接矩阵为：\n");
	for(int i=0; i<G.vexnum; ++i)
	{
		for(int j=0; j<G.vexnum; ++j)
		{
			printf("%d\t",G.arcs[i][j].adj);
		}
		printf("\n");
	}
}
 
void Panel()
{
	//操作菜单
	printf("-------------------------------------------------\n");
	printf("---------------图的邻接矩阵操作------------------\n");
	printf(" \t\t0-创建图						 \n");
	printf("\t\t1-查看顶点信息 					 \n");
	printf("\t\t2-更改指定顶点的值				 \n");
	printf("\t\t3-插入顶点						 \n");
	printf("\t\t4-删除顶点						 \n");
	printf("\t\t5-插入弧 						 \n");	
	printf("\t\t6-删除弧 	        			 \n");
	printf("\t\t7-深度优先遍历图	             \n");			
	printf("\t\t8-广度优先遍历图	             \n");
	printf("\t\t9-查看图的邻接矩阵	    		 \n");
	printf("\t\t10-退出							 \n");
	printf("-------------------------------------------------\n");
}
 
int main()
{
	MGraph G;
	int n;
	int i;
	VertexType v,w;
	while(1)
	{
		Panel();
		printf("请输入操作号:");
		scanf("%d",&n);
		getchar();
		switch(n)
		{
		case 0://创建图
			if(CreateGraph(G))
				printf("创建成功\n");
			else
				printf("创建失败\n");
			system("pause");
			break;
		case 1://查看顶点信息
			DisplayVexValue(G);
			system("pause");
			break;
		case 2://更改指定顶点的值
			printf("请输入更改顶点的序号：");
			scanf("%d",&i);
			getchar();
			printf("请输入顶点的新值：");
			scanf("%c",&v);
			getchar();
			PutVex(G,i,v);
			system("pause");
			break;
		case 3://插入顶点
			printf("请输入你所要插入顶点的值：");
			scanf("%c",&v);
			getchar();
			InsertVex(G,v);
			system("pause");
			break;
		case 4://删除顶点
			printf("请输入你所要删除的顶点的值：");
			scanf("%c",&v);
			getchar();
			DeleteVex(G,v);
			system("pause");
			break;
		case 5://插入弧
			printf("插入：请输入弧依赋的两个顶点的值：");
			scanf("%c%c",&v,&w);
			getchar();
			InsertArc(G,v,w);
			system("pause");
			break;
		case 6://删除弧 
			printf("删除：请输入弧依赋的两个顶点的值：");
			scanf("%c%c",&v,&w);
			getchar();
			DeleteArc(G,v,w);
			system("pause");
			break;
		case 7://深度优先遍历图
			printf("深度优先遍历的结果为：\n");
			DFSTraverse(G,VisitVex);
			printf("\n");
			system("pause");
			break;
		case 8://广度优先遍历图
			printf("广度优先遍历的结果为：\n");
			BFSTraverse(G,VisitVex);
			printf("\n");
			system("pause");
			break;
		case 9://查看图的邻接矩阵
			DisplayAdjMatrix(G);
			system("pause");
			break;
		case 10://退出
			exit(OVERFLOW);
			break;
		default:
			printf("无此操作\n");
			system("pause");
			
		}
 
	}
	return 0;
}

