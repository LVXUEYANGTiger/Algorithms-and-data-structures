#include <iostream>
#include <string.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
using namespace std;
//哈希函数的构造方法:除留取余法
//处理冲突机制:链地址法
typedef struct _NODE{
	int key;
	struct _NODE* next;
}_NODE; 

typedef struct Hash_Table{
	_NODE* pChainHash[13];
}Hash_Table;
//初始化哈希表
Hash_Table* InitHashTable()
{
	Hash_Table* pHashTable =(Hash_Table*)malloc(sizeof(Hash_Table));
	int i;
	memset(pHashTable,0,sizeof(Hash_Table));
	return pHashTable;
} 
//在哈希表中查找元素
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
//在哈希表中删除元素
int DeleteDataInHash(Hash_Table* pHashTable,int key)
{
	if(!pHashTable)
	{
		return FALSE;
	}
	_NODE* pNode=NULL;
	if(!(pNode=pHashTable->pChainHash[key%13]))//无此数据 
	{
		return FALSE;
	}
	if(pNode->key==key)//直接定址的数据 
	{
		pHashTable->pChainHash[key%13]=pNode->next;
		delete pNode;
		return TRUE;
	}
	
	_NODE* pPreNode=pNode;//数据冲突则在同一线性链表中查找
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
	
	printf("请输入元素个数:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&e); 
		InsertDataToHash(pHashTable,e);
	}
	printf("请输入查找的元素:\n");
	scanf("%d",&e);
	p=FindDataInHash(pHashTable,e);
	printf("查找元素为%d已找到\n",p->key);
	printf("请输入删除的元素:\n");
	scanf("%d",&e);
	if(DeleteDataInHash(pHashTable,e)==0)
	{
		printf("删除成功!!!\n");
	}
	printf("请输入查找的元素:\n");
	scanf("%d",&e);
	p=FindDataInHash(pHashTable,e);
	if(p==NULL)
	{
		printf("该哈希表中没有这个元素\n");
	}
	
	return 0;
}
