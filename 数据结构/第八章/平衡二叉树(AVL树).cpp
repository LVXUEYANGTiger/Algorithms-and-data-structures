#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EH 0 //�ȸ�
#define LH 1 //���
#define RH -1 //�Ҹ�
typedef struct TNode
{
	int data;
	int bf;
	struct TNode* lchild;
	struct TNode* rchild;
}BiTree;
 
void L_Rotate( BiTree*& T )//����
{
	BiTree* p = T->rchild;
	T->rchild = p->lchild;
	p->lchild = T;
	T = p;
}
void R_Rotate( BiTree*& T )//����
{
	BiTree* p = T->lchild;
	T->lchild = p->rchild;
	p->rchild = T;
	T = p;
}
 
void LeafBalance( BiTree*& T )//��ƽ�⴦��
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
		L_Rotate( T->rchild ); //������
		R_Rotate( T );//������
		break;
	}
}
 
void RightBalance( BiTree*& T )//��ƽ�⴦��
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
		R_Rotate( T->rchild ); //������
		L_Rotate( T );//������
		break;
	}
}
 
 
int  InsertAVL( BiTree*& T, int key, int & taller )
{
	if ( !T )
	{
		//�����½�㣬�����ߣ���tallerΪtrue
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
			//�����Ѵ��ں�key��ͬ�ؼ��ֵĽ�����ٲ���
			taller = 0;
			return 0;
		}
		if ( key < T->data )
		{
			//������������������
			if ( !InsertAVL( T->lchild, key, taller ) )
				return 0;
			if ( taller )
			{
				//�Ѳ��뵽T����������������������
				switch( T->bf )
				{
				case EH://ԭ�����������ȸߣ��������������߶�������
					T->bf = LH;
					taller = 1;
					break;
				case RH://ԭ���������ߣ����ڵȸ���
					T->bf = EH;
					taller = 0;
					break;
				case LH://ԭ���������ߣ�����ʧȥƽ���ˣ�������ƽ�⴦��
					LeafBalance( T );
					taller = 0;
					break;
				}
			}
		}
		else
		{
			//������������������
			if ( !InsertAVL( T->rchild, key, taller ) )
				return 0;
			if ( taller )
			{
				//�Ѳ��뵽T����������������������
				switch( T->bf )
				{
				case EH://ԭ�����������ȸߣ��������������߶�������
					T->bf = RH;
					taller = 1;
					break;
				case LH://ԭ���������ߣ����ڵȸ���
					T->bf = EH;
					taller = 0;
					break;
				case RH://ԭ���������ߣ�����ʧȥƽ���ˣ�������ƽ�⴦��
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
	printf("�����������:\n");
	scanf("%d",&n);
	printf("��������Ԫ��:\n");
	for ( int i = 0; i < n; ++i )
	{
		scanf("%d",&e);
		InsertAVL( T, e, taller );
	}
 
	PrintBiTree( T );
	cout << endl;
 
	return 0;
}

