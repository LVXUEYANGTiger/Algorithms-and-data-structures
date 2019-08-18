#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW -2
#define FALSE 0
#define TRUE 1
typedef int Status;
//关键字为整型
typedef int KeyType;	

//数据元素类型
typedef struct	
{
   KeyType key; 	//关键字域
   //... 	        //其他域
}ElemType;

typedef struct Node /*二叉排序树的类型定义*/
{
    ElemType data;
    struct Node *lchild,*rchild;
}BiTNode,*BiTree;

//对两个关键字比较约定为如下的宏定义
#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

Status SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p)
{
	//在指针T所指的二叉排序树中递归地查找其他关键字等于key的数据元素，若查找成功，
	//则指针p指向该数据元素的节点，并返回TRUE，否则指针p指向查找路径访问的
	//最后一个结点并返回FALSE，指针f指向T的双亲，其初始调用值为NULL
	if(!T){
		p=f;
		return FALSE;				//查找不成功 
	} 
	else if EQ(key,T->data.key)
	{
		p=T;
		return TRUE;				//查找成功 
	}
	else if LT(key,T->data.key)
	{
		return SearchBST(T->lchild,key,T,p);	//在左子树中继续查找 
	}
	else
		return SearchBST(T->rchild,key,T,p); 
}

Status InsertBST(BiTree &T,ElemType e)
{
	//当二叉树T中不存在关键字等于e.key的数据元素时，插入e并返回TRUE
	//否则返回FALSE
	BiTree p,s;
	if(!SearchBST(T,e.key,NULL,p))
	{				//查找不成功 
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data.key=e.key;
		s->lchild=s->rchild=NULL;
		if(!p)
			T=s;								//被插入结点*s作为新的根结点
		else if LT(e.key,p->data.key)
			p->lchild=s;						//被插入结点*s作为左孩子
		else 
			p->rchild=s;						//被插入结点*s为右孩子
		return TRUE; 
	}
	else
		return FALSE; 							//树中已有关键字相同的结点，不在输入 
} 

Status CreateBST(BiTree &T,int n)
{
	ElemType e;
	printf("请输入二叉排序树的关键字(元素之间用空格隔开)\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&e.key);
		InsertBST(T,e);
	}
	return TRUE;
}

//中序遍历 
void InOrderTraverse(BiTree T)
/*中序遍历二叉排序树的递归实现*/
{
    if(T)                               /*如果二叉排序树不为空*/
    {
        InOrderTraverse(T->lchild);     /*中序遍历左子树*/
        printf("%4d",T->data.key);          /*访问根结点*/
        InOrderTraverse(T->rchild);         /*中序遍历右子树*/
    }
}

Status Delete(BiTree &p){
	//从二叉排序树中删除结点p，并重接它的左或右子树
	BiTree q,s;
	if(!p->rchild){				//只需重接它的左子树 
		q=p;
		p=p->lchild;
		free(q);
	} 
	else if(!p->lchild){		//只需重接它的右子树 
		q=p;
		p=p->rchild;
		free(q);
	}
	else{						//左右子树均不空 
		q=p;
		s=p->lchild; 
		while(s->rchild){		//转左，然后向右到尽头 
			q=s;
			s=s->rchild;
		}
		p->data=s->data;		//s指向被删结点的“前驱”
		if(q!=p)
			q->lchild=s->rchild;	//重接*q的的右子树 
		else
			q->rchild=s->lchild; 	//重接*q的的左子树 
		delete s; 
	}
	return TRUE; 
} 

Status DeleteBST(BiTree &T,KeyType key)
{
	//若排序二叉树存在关键字等于key的数据元素时，则删除该元素节点
	//并返回TRUE否则返回FALSE
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
printf("\t\t   ================动态查找表操作===========\n");
printf("\t\t   =                                       =\n");
printf("\t\t   =         请选择你的操作：              =\n");
printf("\t\t   =         [1]创建二叉排序树             =\n");
printf("\t\t   =         [2]二叉排序树插入             =\n");
printf("\t\t   =         [3]二叉排序树删除             =\n");
printf("\t\t   =         [4]二叉排序树查找             =\n");
printf("\t\t   =         [5]中序遍历二叉树             =\n");
printf("\t\t   =         [6]销毁二叉排序树             =\n");
printf("\t\t   =         [7]退出                       =\n");
printf("\t\t   =========================================\n");

printf("\n");
printf("\n");
printf("请选择你要进行的操作:\n");
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
				printf("请输入二叉排序树的关键字个数：\n");
				scanf("%d",&n);
				if(CreateBST(T,n))
				{
					printf("创建成功！\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("请输入你要插入的元素：\n");
				scanf("%d",&e.key);
				if(!InsertBST(T,e))
				{
					printf("插入失败，该二叉排序树中已有该关键字!\n"); 
				}
				Menu();
			    break;
			case 3:
				printf("请输入要删除的二叉树的关键字：\n");
				scanf("%d",&key);
				DeleteBST(T,key);
				Menu();
			    break;
			case 4:
				printf("请输入要查找的关键字");
				scanf("%d",&key); 
				if(SearchBST(T,key,NULL,q)) 
				{
					printf("查找成功！\n关键字为：%d",q->data.key);
				}
				Menu();
				break; 
			case 5:
				printf("中序遍历结果为：\n");
				InOrderTraverse(T); 
				Menu();
				break; 
			case 6:
				if(DestroyBST(T)==1)
				{
					printf("销毁成功！\n");
				}
				Menu();
				break;
		    default:
				printf("输入有误,请重新输入!\n");
				Menu();
					break;
		}
		scanf("%d",&i);
	}
	return 0;
}

