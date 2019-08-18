#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define OVERFLOW -2
typedef int Status;
typedef char ElemType; //����ֵ����Ϊ�ַ�
 
 
 
 
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstChild;  //��һ������
	struct CSNode *nextsbling;   //�ú��ӵĵ�һ���ֵ�
}CSNode, *CSTree;
 
 
/*------------�������õ��Ķ���------------------------------*/
 
typedef CSTree QElemType;//���е�Ԫ��
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;
 
typedef struct  
{
	QueuePtr front;  //��ͷָ��
	QueuePtr rear;  //��βָ��
}LinkQueue;
 
Status InitQueue(LinkQueue &Q)//����һ���ն���
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));//��ͷ���
	if(!Q.front)
		exit(OVERFLOW);
	Q.front ->next = NULL;
	return OK;
}
 
Status QueueEmpty(const LinkQueue &Q)//������Ϊ�գ��򷵻�TRUE�����򷵻�FALSE
{
	if(Q.rear == Q.front)
		return TRUE;
	return FALSE;
}
 
Status EnQueue(LinkQueue &Q, QElemType e) //����Ԫ��eΪQ���¶�βԪ��
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
 
Status DeQueue(LinkQueue &Q,QElemType &e) //�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK;
{
	if(Q.front == Q.rear)
	{
		return ERROR; //�ӿ�
	}
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}
 
/*--------------------------------------------------------------*/
 
 
/*-----------------����ʵ�ִ���---------------------------------*/
Status CreateTree(CSTree &T)  //����һ����
{
	
	LinkQueue Q;
	InitQueue(Q);//����һ���ն���
	char buffChild[10];  //���ڴ�ź����ǵĻ���
	memset(buffChild,0,10); //��ʼ���������飬��ΪNULL
	printf("���������ĸ���㣨�ַ�,��#����գ�:\n");
	scanf("%c",&buffChild[0]);
	if(buffChild[0] != '#')
	{
		
		T = (CSTree)malloc(sizeof(CSNode));//Ϊ����㿪��һ���ռ�
		if(!T)
			exit(OVERFLOW);  //����ʧ�ܣ���ֹ����
		T->data = buffChild[0];
		T->nextsbling = NULL;  //��������ֵ�
		EnQueue(Q,T);  //��������
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e); //������
			//CSTree p = e; //����ָ���ͷ���
			printf("�밴����˳��������%c�ĺ���(�ַ�,��#����):\n",e->data);
			fflush(stdin);  //���������������������
//			gets(buffChild);
			scanf("%s",buffChild);
			if(buffChild[0] != '#')//�к���
			{
				CSTree q;
				
				q = (CSTree)malloc(sizeof(CSNode));  //���ٺ��ӽ��ռ�
				if(!q)
					exit(OVERFLOW);
				q->data = buffChild[0];  //
				e->firstChild = q;  //ָ���һ������
				EnQueue(Q,q);  //��һ���������
				CSTree p = q;  //ָ�����ӵĺ���
				for(size_t i = 1; i < strlen(buffChild)-1; ++i) //���Ӵ����ֵ�
				{
					q = (CSTree)malloc(sizeof(CSNode));  //���ٺ��ӽ��ռ�
					if(!q)
						exit(OVERFLOW);
					q->data = buffChild[i];  //	
					p->nextsbling = q;
					EnQueue(Q,q);  
					p = q;  //ָ�����ӵĺ���
				}
				p->nextsbling = NULL;
			}
			else//�޺���
			{
				e->firstChild = NULL;
			}
		}
		
	}
	else
	{
		T = NULL;//����
	}
	return OK;
 
 
}
 
void DestroyTree(CSTree &T)
{
	//��T���ڣ�������T
	if(T)//������
	{
		if(T->firstChild)//���������ڣ��������Գ���Ϊ��������
			DestroyTree(T->firstChild);
		if(T->nextsbling)//���������ڣ����������ֵ�Ϊ��������
			DestroyTree(T->nextsbling);
		free(T); //�ͷŸ����
		T = NULL;
	}
}
 
void ClearTree(CSTree &T)
{
	//��T���ڣ�����T��Ϊ����,
	DestroyTree(T);
}
 
Status TreeEmpty(const CSTree &T)
{
	//��T���ڣ���������TRUE�����򷵻�FALSE
	if(T)
		return TRUE;
	else
		return FALSE;
}
 
int TreeDepth(const CSTree &T)
{
	//��T���ڣ������������
	if(!T)//����
	{
		return 0;
	}
	if(!T->firstChild)//�޳���
	{
		return 1;
	}
	CSTree p;
	int depth,max = 0;
	for(p=T->firstChild; p; )
	{
		depth = TreeDepth(p);
		if(depth > max)
			max = depth;
		p= p->nextsbling;
	}
	return max+1;//��ǰ�����һ��
}
 
ElemType Root(const CSTree &T)
{
	//��T���ڣ��������ĸ�
	if(T)
		return T->data;
	return 0;
}
 
CSNode* FindNode(const CSTree &T,ElemType cur_e)
{
	//��T���ڣ�����ֵΪcur_e�Ľ���ָ��
	LinkQueue Q;
	InitQueue(Q);  //����һ���ն���
	if(T)
	{
		EnQueue(Q,T);//�������
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			if(e->data == cur_e)
				return e;
			if(e->firstChild) //��ǰ����г��ӣ���ó������
			{
				EnQueue(Q,e->firstChild);
			}
			if(e->nextsbling)//��ǰ������ֵ�,����ֵ����
			{
				EnQueue(Q,e->nextsbling);
			}
		}
	}
	return NULL;
}
 
Status Assign(CSTree &T, ElemType cur_e, ElemType value)
{
	//��T���ڣ�cur_e�����д��ڵĽ�㣬�����������value��ֵ����cur_e�Ľ��
	if(!T)//����
		return ERROR;
	CSNode *node_cur_e = FindNode(T,cur_e);//����ֵΪcur_e�Ľ�㣬�����Ի�ȡ���ĵ�ַ
	if(!node_cur_e) //��ȡʧ�ܣ����س�����Ϣ
		return ERROR;
	node_cur_e->data = value;
	return OK;
 
}
 
CSNode * Parent(CSTree &T,ElemType cur_e)
{
	//��ʼ��������T���ڣ�cur_e��T��ĳ�����
	//�����������cur_e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ؿ�
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		if(T->data == cur_e)
			return NULL;//�������˫��,����������NULL
		EnQueue(Q,T);//��������
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			QElemType p = e;//��ʾ�ճ��ӵ�Ԫ�أ�
			if(e->firstChild)//�ý���к���
			{
				if(e->firstChild->data == cur_e)//��ú���������Ľ�㣬�򷵻�˫��
				{
					return p;
				}
				EnQueue(Q,e->firstChild);
				QElemType brotherPtr = e->firstChild->nextsbling;//ָ���ӵ��ֵܽ��
				while(brotherPtr) //�ú������ֵ�
				{
					if(brotherPtr->data == cur_e)//�ֵ�������Ľ�㣬�򷵻�˫��
					{
						return p;
					}
					EnQueue(Q,brotherPtr);//�ֵ����
					brotherPtr = brotherPtr->nextsbling;
				}
			}
		}
	}
	return NULL;
}
 
ElemType LeftChild(CSTree &T, ElemType cur_e)
{
	//��ʼ��������T���ڣ�cur_e��T��ĳ�����
	//�����������cur_e��T�ķ�Ҷ�ӽ�㣬�򷵻����������ӣ����򷵻ؿ�
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->firstChild)//��Ҷ�ӽ��
		{
			return node->firstChild->data; //���ؽ���ֵ
		}
	}
	return ERROR;
}
 
ElemType RightSibling(CSTree &T, ElemType cur_e)
{
	//��ʼ��������T���ڣ�cur_e��T�е�ĳ����㡣
	//�����������cur_e�����ֵܣ��򷵻��������ֵܣ����򷵻ؿ�
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->nextsbling)//�����ֵ�
		{
			return node->nextsbling->data;//�������ֵܵ�ֵ
		}
	}
	return ERROR;
}
 
Status LevelOrderTraverse(const CSTree &T)
{
	//���������
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		printf("%c",T->data);//���ʽ��
		EnQueue(Q,T);//������Ŷ�
		while(!QueueEmpty(Q))
		{
			QElemType e,p;
			DeQueue(Q,e);
			p = e->firstChild;
			while(p)
			{
				printf("%c",p->data);
				EnQueue(Q,p);
				p = p->nextsbling;
			}
		}
		return OK;
	}
	return ERROR;//����
}
/*-------------------------------------------------------*/
 
int main()
{
	CSTree T;
	CreateTree(T);
 
	printf("���������������");
	LevelOrderTraverse(T);
	printf("\n");
 
	printf("���ĸ�Ϊ%c\n",Root(T));
	ElemType e = 'D';
	CSNode *node = FindNode(T,e);
	if(node)
		printf("���ڽ��%c\n",node->data);
	printf("�������Ϊ��%d\n",TreeDepth(T));
 
	node = Parent(T,e);
	if(node)
	{
		printf("���%c��˫����%c\n",e,node->data);
	}
 
	printf("A��������%c\n",LeftChild(T,'A'));
	if(Assign(T,'D','S'))//���Ľ����D��ֵΪS
		printf("��ֵ�ɹ�\n");
	printf("���ĺ�...\nA��������%c\n",LeftChild(T,'A'));
 
	printf("���������������");
	LevelOrderTraverse(T);
	printf("\n");
 
	DestroyTree(T);
	return 0;
}

