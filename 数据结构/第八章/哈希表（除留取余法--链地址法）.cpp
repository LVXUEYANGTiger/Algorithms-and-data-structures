#include <iostream>
#include <string.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
using namespace std;
//��ϣ�����Ĺ��췽��:����ȡ�෨
//�����ͻ����:����ַ��
typedef struct _NODE{
	int key;
	struct _NODE* next;
}_NODE; 

typedef struct Hash_Table{
	_NODE* pChainHash[13];
}Hash_Table;
//��ʼ����ϣ��
Hash_Table* InitHashTable()
{
	Hash_Table* pHashTable =(Hash_Table*)malloc(sizeof(Hash_Table));
	int i;
	memset(pHashTable,0,sizeof(Hash_Table));
	return pHashTable;
} 
//�ڹ�ϣ���в���Ԫ��
_NODE* FindDataInHash(Hash_Table* pHashTable,int key)
{
	if(!pHashTable)
	{
		return NULL;
	}
	_NODE* pNode=NULL;
	if(!(pNode=pHashTable->pChainHash[key%13]))
	{
		return NULL;
	}
	while(pNode)
	{
		if(pNode->key==key)
		{
			return pNode;
		}
		pNode=pNode->next;
	}
	return NULL;
}
int  InsertDataToHash(Hash_Table* pHashTable,int key)
{
	if(!pHashTable)
	{
		return FALSE; 
	}
	if(NULL!=FindDataInHash(pHashTable,key))
	{
		return FALSE;
	}
	_NODE* pNewNode=(_NODE*)malloc(sizeof(_NODE));
	memset(pNewNode,0,sizeof(_NODE));
	pNewNode->key=key;
	
	_NODE* pNode=NULL;
	pNode=pHashTable->pChainHash[key%13];
	if(!pNode)
	{
		pHashTable->pChainHash[key%13]=pNewNode;
	}
	else
	{
		while(pNode->next)
		{
			pNode=pNode->next;
		}
		pNode->next=pNewNode;
	}
	return TRUE;
}
//�ڹ�ϣ����ɾ��Ԫ��
int DeleteDataInHash(Hash_Table* pHashTable,int key)
{
	if(!pHashTable)
	{
		return FALSE;
	}
	_NODE* pNode=NULL;
	if(!(pNode=pHashTable->pChainHash[key%13]))//�޴����� 
	{
		return FALSE;
	}
	if(pNode->key==key)//ֱ�Ӷ�ַ������ 
	{
		pHashTable->pChainHash[key%13]=pNode->next;
		delete pNode;
		return TRUE;
	}
	
	_NODE* pPreNode=pNode;//���ݳ�ͻ����ͬһ���������в���
	pNode=pNode->next;
	while(pNode)
	{
		if(pNode->key==key)
		{
			pPreNode->next=pNode->next;
			delete pNode;
			return TRUE;
		}
	}
	return FALSE; 
} 
int main(int argc, char** argv) 
{
	Hash_Table* pHashTable; 
	pHashTable=InitHashTable();
	int n,e,i;
	_NODE* p;
	
	printf("������Ԫ�ظ���:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&e); 
		InsertDataToHash(pHashTable,e);
	}
	printf("��������ҵ�Ԫ��:\n");
	scanf("%d",&e);
	p=FindDataInHash(pHashTable,e);
	printf("����Ԫ��Ϊ%d���ҵ�\n",p->key);
	printf("������ɾ����Ԫ��:\n");
	scanf("%d",&e);
	if(DeleteDataInHash(pHashTable,e)==0)
	{
		printf("ɾ���ɹ�!!!\n");
	}
	printf("��������ҵ�Ԫ��:\n");
	scanf("%d",&e);
	p=FindDataInHash(pHashTable,e);
	if(p==NULL)
	{
		printf("�ù�ϣ����û�����Ԫ��\n");
	}
	
	return 0;
}
