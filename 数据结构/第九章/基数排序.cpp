#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
 
typedef int Status;
typedef int ElemType;
 
#define MAX_NUM_OF_KEY 8 //�ؼ����������ֵ
#define RADIX 10 //�ؼ��ֻ�������ʱ��ʮ���������Ļ���
#define MAX_SPACE 100 //����Ϊ10000
#define ord(ch) ((ch)-'0')
#define succ(x) ((x)+1)
typedef char KeyType;
typedef struct
{
  KeyType keys[MAX_NUM_OF_KEY]; //�ؼ���
  int next;
}SLCell;  //��̬����Ľ������
 
typedef struct
{
  SLCell r[MAX_SPACE]; //��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
  int keynum; //��¼��ǰ�ؼ��ָ���
  int recnum; //��̬����ĵ�ǰ����
}SLList;  //��̬��������
typedef int ArrType[RADIX]; //ָ����������
 
/*******************************��������****************************************/
 
 
 
/*******************************��������****************************************/
void Distribute(SLCell r[],int i,ArrType f,ArrType e)
{
  int j,p;
 
  for(j = 0;j<RADIX;++j){
    f[j] = 0;
    e[j] = 0;
  }
 
  for(p = r[0].next; p ;p = r[p].next){
    j = ord(r[p].keys[i]);
    if(!f[j])
      f[j] = p;
    else
      r[e[j]].next = p;
    e[j] = p;
  }
}
 
void Collect(SLCell r[],int i,ArrType f,ArrType e)
{
  int j,t;
 
  for(j = 0; j<RADIX&&!f[j] ; j = succ(j)); //�ҵ���һ���ǿ��ӱ�succΪ���̺���
  if(j<RADIX){
    r[0].next = f[j];
    t = e[j];
    while(j<RADIX){
      for(j = succ(j) ; j<RADIX-1 && !f[j]; j = succ(j));
        if(f[j] && j<=RADIX-1){
          r[t].next = f[j];
          t = e[j];
        }
    }
    r[t].next = 0;
  }
 
}
 
void RadixSort(SLList *L)
{
  int i;
  ArrType f,e;
 
  for(i = 0;i<L->keynum;i++){
    Distribute(L->r,i,f,e);
    Collect(L->r,i,f,e);
  }
}
 
void CreateSLL(SLList *L)
{
  char s[100];
  int i,n,ct;
  L->recnum = 0;
 
 printf("������ؼ��ָ�����\n");
  scanf("%d",&L->keynum);
  printf("�����������ȣ�\n");
  scanf("%d",&n);

  
  
  for(ct = 0;ct<n;ct++)
  {
    printf("������ؼ��֣�\n");
 
    scanf("%s",&s);
    L->recnum++;
    for(i = 0;i<L->keynum;++i)
      L->r[L->recnum].keys[L->keynum-1-i] = s[i];
  }
  for(i = 0;i<L->recnum;++i)
    L->r[i].next = i+1;
  L->r[L->recnum].next = 0;
}
 
void TraverseSLL(SLList L)
{
  int i,j;
  for(i = L.r[0].next; i ;i = L.r[i].next){
    for(j = L.keynum-1;j>=0;j--)
      printf("%c",L.r[i].keys[j]);
    printf(" ");
  }
  printf("\n");
}
/*******************************����������**************************************/
int main()
{
  SLList L;
  printf("������̬����\n");
  CreateSLL(&L);
  printf("������ɣ�\n");
  TraverseSLL(L);
 
  printf("\n��������\n");
  RadixSort(&L);
  TraverseSLL(L);
  return 0;
}
