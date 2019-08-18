#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MaxSize 20 
typedef char VertexType; 
typedef struct outNode 
{							//定义出度的节点	
	VertexType data;	
	struct outNode *next;
}outNode; 
typedef struct Vertex {			
//定义顶点结构	
	int in;	
	VertexType data;	
	outNode *first;
}Vertex; 
//用邻接表法创建AOV网
void CreateAOV( Vertex **g )
{	
	VertexType ver;	
	int i = 0;	
	int VertexNum;	
	outNode *p, *q; 	
	(*g) = (Vertex *)malloc(sizeof(Vertex)*MaxSize); 	
	printf("请输入AOV网的顶点:\n");					
	while( '\n' != (ver=getchar()) ) 
	{		//存储网的顶点信息		
		(*g)[i].data = ver;		
		(*g)[i].first = NULL;		
		i++;	
	}	
	(*g)[i].data = '\0';	
	VertexNum = i;							//记录顶点数 	
	printf("请依次输入AOV网顶点的入度:\n");	
	for( i=0; i<VertexNum; i++ )			//存储顶点的入度信息		
	scanf("%d", &(*g)[i].in); 	
	fflush(stdin);		
	printf("请输入AOV网顶点对应邻接点:\n");	
	for( i=0; i<VertexNum; i++ ) 
	{			//存储每个顶点的邻接点信息		
		printf("%c :", (*g)[i].data);		
		if( '\n' != (ver=getchar()) ) 
		{			
			p = (outNode *)malloc(sizeof(outNode));			
			p->data = ver;			
			(*g)[i].first = p;			
			p->next = NULL;			
			q = p;								
			while( '\n' != (ver=getchar()) ) 
			{				
				p = (outNode *)malloc(sizeof(outNode));				
				p->data = ver;				
				p->next = NULL;				
				q->next = p;				
				q = p;			
			}		
		}	
	}
} 
	//获取顶点数
int CalVerNum( Vertex *g )
{	
	int len = 0;	
	while( '\0' != (g++)->data ) 		
	len++;	
	return len;
}  
//打印AOV网
void PrintAOV( Vertex *g )
{	
	int VertexNum = CalVerNum( g );	
	outNode *p;	
	printf("AOV的顶点、入度以及邻接点为:\n");	
	for( int i=0; i<VertexNum; i++ ) 
	{								//打印顶点		
		printf("%c  %d  ", g[i].data, g[i].in);		
		p = g[i].first;		
		while( NULL != p ) 
		{			
			printf("%c ", p->data);			
			p = p->next;		
		}		
			printf("\n");	
	}
}
//拓扑排序函数
void TopSort( Vertex *g )
{	
	int i, j, k;	
	outNode *p;	
	int VertexNum = CalVerNum( g );	
	printf("拓扑排序后的序列为:\n");	
	for( i=0; i<VertexNum; i++ ) 
	{				
		//外循环用来控制输出的顶点数		
		for( j=0; j<VertexNum; j++ )			
		//内循环用来找到下一个入度为0的顶点			
		if( 0 == g[j].in ) 
		{				
			printf("%c ", g[j].data);				
			g[j].in = -1;				
			p = g[j].first;				
			while( NULL != p ) 
			{			
				//删除所有从该顶点发出的全部有向边,具体就是逐个找到该顶点邻接点，然后将其入度-1					
				for( k=0; k<VertexNum; k++ )						
				if( p->data == g[k].data ) 
				{							
					g[k].in--;							
					break;						
				}					
					p = p->next;				
			}				
			break;			
		}	
	}	
	printf("\n");
} 
int main()
{	
	Vertex *g;	
	CreateAOV( &g ); 	
	PrintAOV( g ); 	
	TopSort( g ); 	
	return 0;
}


