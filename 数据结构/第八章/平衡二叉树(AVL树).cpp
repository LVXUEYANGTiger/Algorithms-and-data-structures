#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EH 0 //等高
#define LH 1 //左高
#define RH -1 //右高
typedef struct TNode
{
	int data;
	int bf;
	struct TNode* lchild;
	struct TNode* rchild;
}BiTree;
 
void L_Rotate( BiTree*& T )//左旋
{
	BiTree* p = T->rchild;
	T->rchild = p->lchild;
	p->lchild = T;
	T = p;
}
void R_Rotate( BiTree*& T )//右旋
{
	BiTree* p = T->lchild;
	T->lchild = p->rchild;
	p->rchild = T;
	T = p;
}
 
void LeafBalance( BiTree*& T )//左平衡处理
{
	BiTree* L = T->lchild;
	switch( L->bf )
	{
	case LH:
		T->bf = EH;
		L->bf = EH;
		R_Rotate( T );
		break;
	case RH:
		BiTree* Lr = L->rchild;
		switch( Lr->bf )
		{
		case EH:
			T->bf = EH;
			L->bf = EH;
			break;
		case LH:
			T->bf = RH;
			L->bf = EH;
			break;
		case RH:
			T->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate( T->rchild ); //先左旋
		R_Rotate( T );//再右旋
		break;
	}
}
 
void RightBalance( BiTree*& T )//右平衡处理
{
	BiTree* L = T->rchild;
	switch( L->bf )
	{
	case RH:
		T->bf = EH;
		L->bf = EH;
		L_Rotate( T );
		break;
	case LH:
		BiTree* Ll = L->lchild;
		switch( Ll->bf )
		{
		case EH:
			T->bf = EH;
			L->bf = EH;
			break;
		case LH:
			T->bf = EH;
			L->bf = RH;
			break;
		case RH:
			T->bf = LH;
			L->bf = EH;
			break;
		}
		Ll->bf = EH;
		R_Rotate( T->rchild ); //先右旋
		L_Rotate( T );//再左旋
		break;
	}
}
 
 
int  InsertAVL( BiTree*& T, int key, int & taller )
{
	if ( !T )
	{
		//插入新结点，树长高，置taller为true
		T = new BiTree;
		memset( T, 0, sizeof(BiTree) );
		T->data = key;
		T->bf = EH;
		taller = 1;
	}
	else
	{
		if ( key == T->data )
		{
			//树中已存在和key相同关键字的结点则不再插入
			taller = 0;
			return 0;
		}
		if ( key < T->data )
		{
			//继续在左子树下搜索
			if ( !InsertAVL( T->lchild, key, taller ) )
				return 0;
			if ( taller )
			{
				//已插入到T的左子树中且左子树长高
				switch( T->bf )
				{
				case EH://原本左右子树等高，现因左子树长高而树升高
					T->bf = LH;
					taller = 1;
					break;
				case RH://原本右子树高，现在等高了
					T->bf = EH;
					taller = 0;
					break;
				case LH://原本左子树高，现在失去平衡了，需做左平衡处理
					LeafBalance( T );
					taller = 0;
					break;
				}
			}
		}
		else
		{
			//继续在右子树下搜索
			if ( !InsertAVL( T->rchild, key, taller ) )
				return 0;
			if ( taller )
			{
				//已插入到T的右子树中且右子树长高
				switch( T->bf )
				{
				case EH://原本左右子树等高，现因右子树长高而树升高
					T->bf = RH;
					taller = 1;
					break;
				case LH://原本左子树高，现在等高了
					T->bf = EH;
					taller = 0;
					break;
				case RH://原本右子树高，现在失去平衡了，需做右平衡处理
					RightBalance( T );
					taller = 0;
					break;
				}
			}
		}
	}
	return 1;
}
 
void PrintBiTree( const BiTree*const& T )
{
	if ( T )
	{
		PrintBiTree( T->lchild );
		cout << T->data << " ";
		PrintBiTree( T->rchild );
	}
}
 
int main()
{
	BiTree* T = NULL;
	int n,e;
	int  taller =0;
	printf("请输入结点个数:\n");
	scanf("%d",&n);
	printf("请输入结点元素:\n");
	for ( int i = 0; i < n; ++i )
	{
		scanf("%d",&e);
		InsertAVL( T, e, taller );
	}
 
	PrintBiTree( T );
	cout << endl;
 
	return 0;
}

