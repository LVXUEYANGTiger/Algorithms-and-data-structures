#include <iostream>
#include <ctime>
using namespace std;
#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12
#define NULLKEY 0xffffffff/2
typedef struct{
	int* elem;
	int count;
}HashTable;
typedef int Status;
//初始化哈希表
Status InitHashTable(HashTable* pHashTable)
{
	if(!pHashTable)
	{
		return UNSUCCESS;
	}
	pHashTable->count=0;
	pHashTable->elem=new int[HASHSIZE];
	for(int i=0;i<HASHSIZE;++i)
	{
		pHashTable->elem[i]=NULLKEY;
	}
	return SUCCESS;
} 
//销毁哈希表
Status ClearHashTable(HashTable* pHashTable)
{
	if(!pHashTable)
	{
		delete[] pHashTable;
	}
	return SUCCESS;
} 
//哈希函数
int Hash(int key)
{
	return key%HASHSIZE;
	//除留取余法，根据前辈们的经验，若哈希表长为M，则取余因子P为小于
    //或等于表长（最好接近M）的最小质数或不包含小于20质因子的合数 
} 
//插入关键字到哈希表
Status InsertHashTable(HashTable* pHashTable,int key)
{
	if(!pHashTable)
	{
		return UNSUCCESS;
	}
	int addr=Hash(key);//求哈希地址
	while(pHashTable->elem[addr]!=NULLKEY)//不为空则冲突了 
	{
		addr=(addr+1)%HASHSIZE;//开放定址法:线性探测 
	} 
	pHashTable->elem[addr]=key;
	pHashTable->count++;
	return SUCCESS; 
} 
//在哈希表中查找关键字记录
Status SearchHashTable(HashTable* pHashTable,int key,int *addr)
{
	if(!pHashTable)
	{
		return UNSUCCESS;
	}
	*addr=Hash(key);
	while(pHashTable->elem[*addr]!=key)
	{
		*addr=(*addr+1)%HASHSIZE;//开放定址法:线性探测
		if(pHashTable->elem[*addr]==NULLKEY||*addr==Hash(key))
		{
			return UNSUCCESS;
		} 
	}
	return SUCCESS;
} 
int main(int argc, char** argv) 
{
	HashTable _HashTable;
	InitHashTable( &_HashTable );
	int a,n;
	printf("请输入元素个数:\n");
	scanf("%d",&n);
	printf("请输入元素:\n");
	for ( int i = 0; i < n; ++i )
	{
		scanf("%d",&a);
		InsertHashTable( &_HashTable, a);
	}
 

	int addr;
	printf("请输入查找元素的值:\n");
	scanf("%d",&a);
	if ( !SearchHashTable( &_HashTable, a, &addr ) )
	{
			return 0;
	}
	printf("元素的索引为%d\n",addr);


	return 0;
}
