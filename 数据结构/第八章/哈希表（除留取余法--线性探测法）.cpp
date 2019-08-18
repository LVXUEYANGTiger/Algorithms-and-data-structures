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
//��ʼ����ϣ��
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
//���ٹ�ϣ��
Status ClearHashTable(HashTable* pHashTable)
{
	if(!pHashTable)
	{
		delete[] pHashTable;
	}
	return SUCCESS;
} 
//��ϣ����
int Hash(int key)
{
	return key%HASHSIZE;
	//����ȡ�෨������ǰ���ǵľ��飬����ϣ��ΪM����ȡ������PΪС��
    //����ڱ�����ýӽ�M������С�����򲻰���С��20�����ӵĺ��� 
} 
//����ؼ��ֵ���ϣ��
Status InsertHashTable(HashTable* pHashTable,int key)
{
	if(!pHashTable)
	{
		return UNSUCCESS;
	}
	int addr=Hash(key);//���ϣ��ַ
	while(pHashTable->elem[addr]!=NULLKEY)//��Ϊ�����ͻ�� 
	{
		addr=(addr+1)%HASHSIZE;//���Ŷ�ַ��:����̽�� 
	} 
	pHashTable->elem[addr]=key;
	pHashTable->count++;
	return SUCCESS; 
} 
//�ڹ�ϣ���в��ҹؼ��ּ�¼
Status SearchHashTable(HashTable* pHashTable,int key,int *addr)
{
	if(!pHashTable)
	{
		return UNSUCCESS;
	}
	*addr=Hash(key);
	while(pHashTable->elem[*addr]!=key)
	{
		*addr=(*addr+1)%HASHSIZE;//���Ŷ�ַ��:����̽��
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
	printf("������Ԫ�ظ���:\n");
	scanf("%d",&n);
	printf("������Ԫ��:\n");
	for ( int i = 0; i < n; ++i )
	{
		scanf("%d",&a);
		InsertHashTable( &_HashTable, a);
	}
 

	int addr;
	printf("���������Ԫ�ص�ֵ:\n");
	scanf("%d",&a);
	if ( !SearchHashTable( &_HashTable, a, &addr ) )
	{
			return 0;
	}
	printf("Ԫ�ص�����Ϊ%d\n",addr);


	return 0;
}
