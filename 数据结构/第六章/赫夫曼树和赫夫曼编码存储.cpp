#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define  UINT_MAX 100  //���������Ȩֵ���ᳬ��100
typedef struct
{
	unsigned int weight; //Ȩֵ
	unsigned int parent, lchild, rchild; 
}HTNode, *HuffmanTree;  //��̬��������洢�շ�����
 
typedef char **HuffmanCode;  //��̬��������洢�շ��������
 
int Min(HuffmanTree &HT,int i)
{
	//��HT[1...i]��ѡ��parentΪ0��Ȩֵ��С�Ľ��
	//���ظý����±�ֵ
	//�˺�����Select��������
	int j;
	unsigned int k = UINT_MAX;//���������Ȩֵ���ᳬ��UINT_MAX
	int flag;
	for(j = 1; j <= i; ++j)
	{
		if(HT[j].weight < k && HT[j].parent == 0)//�ø�����Ƿ�Ϊ0���жϴ˽���Ƿ��Ѿ���ѡ��
		{
			k = HT[j].weight;
			flag = j;
		}
	}
	HT[flag].parent = 1;//������ǣ�˵���Ѿ���ѡ���ˣ���Ϊ��Select������Ҫѡ��ȨֵС���������
	return flag;
}
 
void Select(HuffmanTree &HT, int i, int &s1, int &s2)
{
	//��HT[1...i]��ѡ��parentΪ0��Ȩֵ��С��������㣬����ŷֱ�Ϊs1,s2
	//s1 <= s2
	s1 = Min(HT,i);
	s2 = Min(HT,i);
}
 
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	//w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
	if(n <= 1)
		return ;
	int m = 2*n - 1; //�ϸ�Ķ������У���n��Ҷ�ӽ�㣬����2n - 1�����
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));  //0�ŵ�Ԫ����
	HuffmanTree p;
	int i;
	for(p = HT+1, i =1;i <= n; ++i, ++p, ++w)
	{
		//��ʼ��һ�úշ�����
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for(;i<=m;++i,++p)
	{
		(*p).weight = 0;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	
	int s1,s2,t;//����Ȩֵ��С�������������
	for(i=n+1; i <= m; ++i)//�����շ�����
	{
		Select(HT,i-1,s1,s2);
//		Ϊ��ͬ������һ���涨������С�������� 
		if(s1>s2)
		{
			t=s1;
			s1=s2;
			s2=t;
		}
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
 
	//--------��Ҷ�ӵ���������ÿ���ַ��ĺշ�������--------
	HC = (HuffmanCode)malloc((n+1)*sizeof(char**));  //����n���ַ������ͷָ������,0�ŵ�Ԫδ��
	char *cd = (char *)malloc(n*sizeof(char));  //���������Ĺ����ռ�
	cd[n-1] = '\0';  //���������
	int start;
	unsigned chld,father;
	for(i = 1; i <= n; ++i)  //����ַ���շ�������
	{
		start = n-1;  //�ӱ����������λ�ÿ�ʼ
		for(chld=i, father=HT[i].parent; father!=0; chld=father, father=HT[father].parent)//��Ҷ�ӵ������������
		{
			if(HT[father].lchild == chld)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n-start)*sizeof(char));  //Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);  //��cd���Ʊ��뵽HC
	}
	free(cd);  //�ͷŹ����ռ�
}
 
int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	printf("������Ȩֵ�ĸ���:\n");
	int n;
	scanf("%d",&n);
	int *w = (int*)malloc(n*sizeof(int));
	printf("��ֱ�����%d��Ȩֵ:\n",n);
	int i;
	for(i=0; i<n; ++i)
	{
		scanf("%d",w+i);
	}
 
	HuffmanCoding(HT, HC, w, n);
 
	printf("�շ�����Ϊ��\n");
	printf("NO\tweight\tparent\tlchild\trchild\n");
	for(i=1; i <= 2*n-1; ++i)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].parent,
								HT[i].lchild, HT[i].rchild);
	}
	printf("�շ�������Ϊ:\n");
	for(i = 1; i <= n; ++i)
		printf("%d|  |-->%s\n", i, HC[i]);
	return 0;
}

