#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 50
#define MAX 9999
typedef char VertexType ;
typedef int EdgeType ;
/*
 *定义图的存储结构
 */
typedef struct
{
    VertexType  vexs[MaxVertexNum][3] ; //定义顶点表
    EdgeType    edges[MaxVertexNum][MaxVertexNum] ; //定义边表
    int n , e ; //定义顶点数与边数
} MGraph ;
/*
 *构建图邻接矩阵
 */
void CreateMGraph(MGraph *G)
{
    int i , j , k , w ;
     printf("请输入定点数与边数（输入格式为：顶点数 边数）：") ;
     scanf("%d%d" , &G->n , &G->e) ;
     printf("请输入顶点信息（输入格式为：顶点号<CR>）：\n") ;
     for(i = 0 ; i < G->n ; i++)
     {
         scanf("%s" , G->vexs[i]) ;
     }
     //初始化邻接矩阵
     for(i = 0 ; i < G->n ; i++)
     {
         for(j = 0 ; j < G->n ; j++)
         {
             if(i == j)
            {
                  G->edges[i][j] = 0 ;
             }else
            {
             G->edges[i][j] = MAX ;
            }
         }
     }
     printf("请输入每条边对应的两个顶点序号以及权值（输入格式为：i,j,w）：\n") ;
     for(k = 0 ; k < G->e ; k++)
     {
         scanf("%d%d%d" , &i , &j , &w) ;
         G->edges[i][j] = w ;
     }
     for(i = 0 ; i < G->n ; i++)
     {
         for(j = 0 ; j < G->n ; j++)
         {
         	if(G->edges[i][j]==MAX)
			{
			 	printf("   ∞");
			} 
			else
			{
				printf("%4d" , G->edges[i][j]) ;
			} 
          
         }
         printf("\n") ;
     }
}
void ShortestPath_2(MGraph G , int P[MaxVertexNum][MaxVertexNum][MaxVertexNum] , int D[MaxVertexNum][MaxVertexNum])
{
 int i , u , v , w ;
 for(v = 0 ; v < G.n ; v++)
 {
     for(w = 0 ; w < G.n ; w++)
     {
         D[v][w] = G.edges[v][w] ;
         for(u = 0 ; u < G.n ; u++)
         {
             P[v][w][u] = 0 ; //进行路径的初始化
         }
         if(D[v][w] < MAX)
         {
             P[v][w][u] = 1 ;
         }
     }
 }
     for(u = 0 ; u < G.n ; u++)
     {
         for(v = 0 ; v < G.n ; v++)
         {
             for(w = 0 ; w < G.n ; w++)
             {
                 if(D[v][u] + D[u][w] < D[v][w]) //从v经u到w的一条路径更短
                 {
                     D[v][w] = D[v][u] + D[u][w] ;
                     for(i = 0 ; i < G.n ; i++)
                     {
                         P[v][w][i] = P[v][u][i] || P[u][w][i] ; //更新路径
                     }
                 }
             }
         }
     }
 }
/*
 *测试代码
 */
int main(void)
{
    MGraph *G ;
    int i , j  , v , w ;
    int  P[MaxVertexNum][MaxVertexNum][MaxVertexNum] , D[MaxVertexNum][MaxVertexNum] ;
    G = (MGraph*)malloc(sizeof(MGraph)) ;
    CreateMGraph(G) ;
    ShortestPath_2(*G , P , D) ;
    for(v = 0 ; v < G->n ; v++)
    {
        for(w = 0 ; w < G->n ; w++)
        {
            printf("%4d" , D[v][w]) ;
        }
        printf("\n") ;
    }
}

