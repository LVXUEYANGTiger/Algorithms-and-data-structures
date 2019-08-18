#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MaxSize 20 
typedef char VertexType; 
typedef struct outNode 
{							//������ȵĽڵ�	
	VertexType data;	
	struct outNode *next;
}outNode; 
typedef struct Vertex {			
//���嶥��ṹ	
	int in;	
	VertexType data;	
	outNode *first;
}Vertex; 
//���ڽӱ�����AOV��
void CreateAOV( Vertex **g )
{	
	VertexType ver;	
	int i = 0;	
	int VertexNum;	
	outNode *p, *q; 	
	(*g) = (Vertex *)malloc(sizeof(Vertex)*MaxSize); 	
	printf("������AOV���Ķ���:\n");					
	while( '\n' != (ver=getchar()) ) 
	{		//�洢���Ķ�����Ϣ		
		(*g)[i].data = ver;		
		(*g)[i].first = NULL;		
		i++;	
	}	
	(*g)[i].data = '\0';	
	VertexNum = i;							//��¼������ 	
	printf("����������AOV����������:\n");	
	for( i=0; i<VertexNum; i++ )			//�洢����������Ϣ		
	scanf("%d", &(*g)[i].in); 	
	fflush(stdin);		
	printf("������AOV�������Ӧ�ڽӵ�:\n");	
	for( i=0; i<VertexNum; i++ ) 
	{			//�洢ÿ��������ڽӵ���Ϣ		
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
	//��ȡ������
int CalVerNum( Vertex *g )
{	
	int len = 0;	
	while( '\0' != (g++)->data ) 		
	len++;	
	return len;
}  
//��ӡAOV��
void PrintAOV( Vertex *g )
{	
	int VertexNum = CalVerNum( g );	
	outNode *p;	
	printf("AOV�Ķ��㡢����Լ��ڽӵ�Ϊ:\n");	
	for( int i=0; i<VertexNum; i++ ) 
	{								//��ӡ����		
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
//����������
void TopSort( Vertex *g )
{	
	int i, j, k;	
	outNode *p;	
	int VertexNum = CalVerNum( g );	
	printf("��������������Ϊ:\n");	
	for( i=0; i<VertexNum; i++ ) 
	{				
		//��ѭ��������������Ķ�����		
		for( j=0; j<VertexNum; j++ )			
		//��ѭ�������ҵ���һ�����Ϊ0�Ķ���			
		if( 0 == g[j].in ) 
		{				
			printf("%c ", g[j].data);				
			g[j].in = -1;				
			p = g[j].first;				
			while( NULL != p ) 
			{			
				//ɾ�����дӸö��㷢����ȫ�������,�����������ҵ��ö����ڽӵ㣬Ȼ�������-1					
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


