#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
struct Arr{
	int *pBase;//�洢��������ĵ�һ��Ԫ�صĵ�ַ
	int len;//�����������ɵ����Ԫ�صĸ���
	int cnt;//������ЧԪ�صĸ��� 
}; 
//����ĳ�ʼ��������ʼ������һ���г��ȵ�����,���沢û��ֵ 
void init_arr(struct Arr *pArr,int len)
{
	pArr->pBase=(int *)malloc(sizeof(int)*len);
	if(pArr->pBase==NULL)
	{
		printf("�ڴ涯̬����ʧ��\n");
	}
	else
	{
		pArr->len=len;
		pArr->cnt=0; 
	}
} 
//�����鸳ֵ
void input_arr(struct Arr &pArr,int val)//valΪԪ�صĸ��� 
{
	int i=0;
	pArr.cnt=val;
	for(i=0;i<val;i++)
	{
		scanf("%d",&pArr.pBase[i]);
	}
} 
//�ж������Ƿ�Ϊ��
int is_empty(struct Arr* pArr)
{
	if(pArr->cnt==0)
	{
		return 0;//�� 
	}
	else
	{
		return 1;//�ǿ� 
	}
} 
//�������Ԫ��
void show_arr(struct Arr *pArr)
{
	int i=0;
	if(is_empty(pArr)==0)
	{
		printf("��ǰ������Ϊ��\n");
	}
	else
	{
		for(i=0;i<pArr->cnt;i++)
		{
			printf("%d ",pArr->pBase[i]);
		}
		printf("\n");
	}
} 
//�ж�Ԫ���Ƿ�����
int is_full(struct Arr *pArr)
{
	if(pArr->len==pArr->cnt)
	{
		return 0;//���� 
	}
	else
	{
		return 1;//δ�� 
	}
} 
//������λ��׷��Ԫ�� 
int append_arr(struct Arr *pArr,int val)
{
	if(is_full(pArr)==0)
	{
		return 0;
	}
	else
	{
		pArr->pBase[pArr->cnt]=val;
		pArr->cnt++;
		return 1; 
	} 
}
int insert_arr(struct Arr &pArr,int pos,int val)
{
	int i;
	if(is_full(&pArr)==0)
	{
		return 0;//0��ʾ��ǰ���������޷��ٽ��в��� 
	}
	if(pos<0||pos>(pArr.len))
	{
		return 1;//����λ�ò��Ϸ� 
	} 
	for(i=pArr.cnt-1;i>=pos-1;--i)
	{
		pArr.pBase[i+1]=pArr.pBase[i];
	}
	pArr.pBase[pos-1]=val;
	pArr.cnt++;
	return 2;//��ʾ����ɹ� 
}
int main(int argc, char** argv) 
{
	struct Arr pArr;
	int len,i,val,m,n; 
	
	printf("��������Ҫ�������鳤��:\n");
	scanf("%d",&len);
	init_arr(&pArr,len);
	printf("����������Ԫ�صĸ���:\n"); 
	scanf("%d",&val);
	input_arr(pArr,val);
	show_arr(&pArr);
	printf("�ж������Ƿ�Ϊ��(��Ϊ0����Ϊ1)%d\n",is_empty(&pArr));
	printf("�ж�����Ԫ���Ƿ�Ϊ��(��Ϊ0����Ϊ1)%d\n",is_full(&pArr)); 
	printf("����������Ҫ�����λ�ú�Ԫ��:\n");
	scanf("%d%d",&m,&n);
	insert_arr(pArr,m,n);
	show_arr(&pArr); 
	//�����һ��Ԫ��λ��֮��׷��һ��Ԫ��
	append_arr(&pArr,9); 
	show_arr(&pArr); 
	return 0;
}
