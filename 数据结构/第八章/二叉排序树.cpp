#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW -2
#define FALSE 0
#define TRUE 1
typedef int Status;
//�ؼ���Ϊ����
typedef int KeyType;	

//����Ԫ������
typedef struct	
{
   KeyType key; 	//�ؼ�����
   //... 	        //������
}ElemType;

typedef struct Node /*���������������Ͷ���*/
{
    ElemType data;
    struct Node *lchild,*rchild;
}BiTNode,*BiTree;

//�������ؼ��ֱȽ�Լ��Ϊ���µĺ궨��
#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

Status SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p)
{
	//��ָ��T��ָ�Ķ����������еݹ�ز��������ؼ��ֵ���key������Ԫ�أ������ҳɹ���
	//��ָ��pָ�������Ԫ�صĽڵ㣬������TRUE������ָ��pָ�����·�����ʵ�
	//���һ����㲢����FALSE��ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
	if(!T){
		p=f;
		return FALSE;				//���Ҳ��ɹ� 
	} 
	else if EQ(key,T->data.key)
	{
		p=T;
		return TRUE;				//���ҳɹ� 
	}
	else if LT(key,T->data.key)
	{
		return SearchBST(T->lchild,key,T,p);	//���������м������� 
	}
	else
		return SearchBST(T->rchild,key,T,p); 
}

Status InsertBST(BiTree &T,ElemType e)
{
	//��������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������TRUE
	//���򷵻�FALSE
	BiTree p,s;
	if(!SearchBST(T,e.key,NULL,p))
	{				//���Ҳ��ɹ� 
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data.key=e.key;
		s->lchild=s->rchild=NULL;
		if(!p)
			T=s;								//��������*s��Ϊ�µĸ����
		else if LT(e.key,p->data.key)
			p->lchild=s;						//��������*s��Ϊ����
		else 
			p->rchild=s;						//��������*sΪ�Һ���
		return TRUE; 
	}
	else
		return FALSE; 							//�������йؼ�����ͬ�Ľ�㣬�������� 
} 

Status CreateBST(BiTree &T,int n)
{
	ElemType e;
	printf("����������������Ĺؼ���(Ԫ��֮���ÿո����)\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&e.key);
		InsertBST(T,e);
	}
	return TRUE;
}

//������� 
void InOrderTraverse(BiTree T)
/*������������������ĵݹ�ʵ��*/
{
    if(T)                               /*���������������Ϊ��*/
    {
        InOrderTraverse(T->lchild);     /*�������������*/
        printf("%4d",T->data.key);          /*���ʸ����*/
        InOrderTraverse(T->rchild);         /*�������������*/
    }
}

Status Delete(BiTree &p){
	//�Ӷ�����������ɾ�����p�����ؽ��������������
	BiTree q,s;
	if(!p->rchild){				//ֻ���ؽ����������� 
		q=p;
		p=p->lchild;
		free(q);
	} 
	else if(!p->lchild){		//ֻ���ؽ����������� 
		q=p;
		p=p->rchild;
		free(q);
	}
	else{						//�������������� 
		q=p;
		s=p->lchild; 
		while(s->rchild){		//ת��Ȼ�����ҵ���ͷ 
			q=s;
			s=s->rchild;
		}
		p->data=s->data;		//sָ��ɾ���ġ�ǰ����
		if(q!=p)
			q->lchild=s->rchild;	//�ؽ�*q�ĵ������� 
		else
			q->rchild=s->lchild; 	//�ؽ�*q�ĵ������� 
		delete s; 
	}
	return TRUE; 
} 

Status DeleteBST(BiTree &T,KeyType key)
{
	//��������������ڹؼ��ֵ���key������Ԫ��ʱ����ɾ����Ԫ�ؽڵ�
	//������TRUE���򷵻�FALSE
	if(!T)
	{
		return FALSE;
	} 
	else
	{
		if(EQ(key,T->data.key))
		{
			return Delete(T);
		}
		else if(LT(key,T->data.key))
		{
			DeleteBST(T->lchild,key);
		}
		else
		{
			DeleteBST(T->rchild,key);
		}
	}
}
Status DestroyBST( BiTree &T )
{
	if (T!=NULL)
	{
		if (T->lchild)
		{
			DestroyBST( T->lchild );
		}
		if (T->lchild)
		{
			DestroyBST( T->rchild );
		}
		free(T);
		T=NULL;
	}
	return TRUE;
}

void Menu(void)
{
printf("\t\t   ================��̬���ұ����===========\n");
printf("\t\t   =                                       =\n");
printf("\t\t   =         ��ѡ����Ĳ�����              =\n");
printf("\t\t   =         [1]��������������             =\n");
printf("\t\t   =         [2]��������������             =\n");
printf("\t\t   =         [3]����������ɾ��             =\n");
printf("\t\t   =         [4]��������������             =\n");
printf("\t\t   =         [5]�������������             =\n");
printf("\t\t   =         [6]���ٶ���������             =\n");
printf("\t\t   =         [7]�˳�                       =\n");
printf("\t\t   =========================================\n");

printf("\n");
printf("\n");
printf("��ѡ����Ҫ���еĲ���:\n");
}

int main(int argc,char **argv)
{
	Menu();
	int i,n;
	BiTree T=NULL,p,q;
	ElemType e;
	KeyType key;
	scanf("%d",&i);
	while(i!=7){
		switch(i){
			case 1:
				printf("����������������Ĺؼ��ָ�����\n");
				scanf("%d",&n);
				if(CreateBST(T,n))
				{
					printf("�����ɹ���\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("��������Ҫ�����Ԫ�أ�\n");
				scanf("%d",&e.key);
				if(!InsertBST(T,e))
				{
					printf("����ʧ�ܣ��ö��������������иùؼ���!\n"); 
				}
				Menu();
			    break;
			case 3:
				printf("������Ҫɾ���Ķ������Ĺؼ��֣�\n");
				scanf("%d",&key);
				DeleteBST(T,key);
				Menu();
			    break;
			case 4:
				printf("������Ҫ���ҵĹؼ���");
				scanf("%d",&key); 
				if(SearchBST(T,key,NULL,q)) 
				{
					printf("���ҳɹ���\n�ؼ���Ϊ��%d",q->data.key);
				}
				Menu();
				break; 
			case 5:
				printf("����������Ϊ��\n");
				InOrderTraverse(T); 
				Menu();
				break; 
			case 6:
				if(DestroyBST(T)==1)
				{
					printf("���ٳɹ���\n");
				}
				Menu();
				break;
		    default:
				printf("��������,����������!\n");
				Menu();
					break;
		}
		scanf("%d",&i);
	}
	return 0;
}

