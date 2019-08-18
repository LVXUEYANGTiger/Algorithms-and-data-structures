#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 50
#define MAX 9999
typedef char VertexType ;
typedef int EdgeType ;
/*
 *����ͼ�Ĵ洢�ṹ
 */
typedef struct
{
    VertexType  vexs[MaxVertexNum][3] ; //���嶥���
    EdgeType    edges[MaxVertexNum][MaxVertexNum] ; //����߱�
    int n , e ; //���嶥���������
} MGraph ;
/*
 *����ͼ�ڽӾ���
 */
void CreateMGraph(MGraph *G)
{
    int i , j , k , w ;
     printf("�����붨����������������ʽΪ�������� ��������") ;
     scanf("%d%d" , &G->n , &G->e) ;
     printf("�����붥����Ϣ�������ʽΪ�������<CR>����\n") ;
     for(i = 0 ; i < G->n ; i++)
     {
         scanf("%s" , G->vexs[i]) ;
     }
     //��ʼ���ڽӾ���
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
     printf("������ÿ���߶�Ӧ��������������Լ�Ȩֵ�������ʽΪ��i,j,w����\n") ;
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
			 	printf("   ��");
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
             P[v][w][u] = 0 ; //����·���ĳ�ʼ��
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
                 if(D[v][u] + D[u][w] < D[v][w]) //��v��u��w��һ��·������
                 {
                     D[v][w] = D[v][u] + D[u][w] ;
                     for(i = 0 ; i < G.n ; i++)
                     {
                         P[v][w][i] = P[v][u][i] || P[u][w][i] ; //����·��
                     }
                 }
             }
         }
     }
 }
/*
 *���Դ���
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

