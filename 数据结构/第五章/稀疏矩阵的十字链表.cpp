#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;// ϡ������ʮ������洢��ʾ 
typedef struct OLNode
{
    int i,j;    // �÷���Ԫ���к����±� 
    ElemType e;    // ����Ԫ��ֵ 
    struct OLNode *right,*down; // �÷���Ԫ�����б���б�ĺ������ 
}OLNode, *OLink;
typedef struct// �к�������ͷָ��������ַ,��CreatSMatrix_OL()����
{
    OLink *rhead, *chead; 
    int mu, nu, tu;        // ϡ�����������������ͷ���Ԫ���� 
}CrossList;
// ��ʼ��M(CrossList���͵ı��������ʼ��,���򴴽������ƾ��󽫳���) 
int InitSMatrix(CrossList *M)
{
    (*M).rhead=(*M).chead=NULL;
    (*M).mu=(*M).nu=(*M).tu=0;
    return 1;
}
// ����ϡ�����M,����ʮ������洢��ʾ��
int CreateSMatrix(CrossList *M)
{ 
    int i,j,k,m,n,t;
    ElemType e;
    OLNode *p,*q;
    if((*M).rhead)
    {
    	free(M->rhead);
	}
    printf("������ϡ���������� ���� ����Ԫ����:\n ");
    scanf("%d%d%d",&m,&n,&t);
    (*M).mu=m;
    (*M).nu=n;
    (*M).tu=t;
    //��ʼ��������ͷ
    (*M).rhead=(OLink*)malloc((m+1)*sizeof(OLink));
    if(!(*M).rhead)
        exit(0);
    //��ʼ��������ͷ
    (*M).chead=(OLink*)malloc((n+1)*sizeof(OLink));
    if(!(*M).chead)
        exit(0);
    for(k=1;k<=m;k++) // ��ʼ����ͷָ������;��������Ϊ������ 
        (*M).rhead[k]=NULL;
    for(k=1;k<=n;k++) // ��ʼ����ͷָ������;��������Ϊ������ 
        (*M).chead[k]=NULL;
    printf("�밴�����������%d������Ԫ���� �� Ԫ��ֵ:\n",(*M).tu);
    for(k=0;k<t;k++)
    {
        scanf("%d%d%d",&i,&j,&e);
        p=(OLNode*)malloc(sizeof(OLNode));
        if(!p)
            exit(0);
        p->i=i; // ���ɽ�� 
        p->j=j;
        p->e=e;
        if((*M).rhead[i]==NULL||(*M).rhead[i]->j>j)    
        {
            // p���ڸ��еĵ�һ����㴦
            p->right=(*M).rhead[i];
            (*M).rhead[i]=p;
        }
        else // Ѱ�����б��еĲ���λ�� 
        {
            //�Ӹ��е�������ͷ��ʼ��ֱ���ҵ�
            for(q=(*M).rhead[i]; q->right && q->right->j < j;q = q->right);
                
            p->right=q->right; // ����в��� 
            q->right=p;
        }
        if((*M).chead[j] == NULL || (*M).chead[j]->i > i) 
        {
            // p���ڸ��еĵ�һ����㴦
            p->down = (*M).chead[j];
            (*M).chead[j] = p;
        }
        else // Ѱ�����б��еĲ���λ�� 
        {
            for(q = (*M).chead[j];q->down && q->down->i < i;q = q->down)
                ;
            p->down=q->down; // ����в��� 
            q->down=p;
        }
    }
    return 1;
}
// ���л������ϡ�����M
int PrintSMatrix(CrossList M)
{
    int i,j;
    OLink p;
    printf("%d��%d��%d������Ԫ��\n",M.mu,M.nu,M.tu);
    printf("������ѡ��(1.������� 2.�������): ");
    scanf("%d",&i);
    switch(i)
    {
    case 1: 
        for(j=1;j<=M.mu;j++)
        {
            p=M.rhead[j];
            while(p)
            {
                printf("%d��%d��ֵΪ%d\n",p->i,p->j,p->e);
                p=p->right;
            }
        }
        break;
    case 2: 
        for(j=1;j<=M.nu;j++)
        {
            p=M.chead[j];
            while(p)
            {
                printf("%d��%d��ֵΪ%d\n",p->i,p->j,p->e);
                p=p->down;
            }
        }
        break;
    }
    return 1;
}
// ��ϡ�����ĺ�Q=M+N
int AddSMatrix(CrossList M,CrossList N,CrossList *Q)
{
    int i,k;
    OLink p,pq,pm,pn;
    OLink *col;
    
    if(M.mu!=N.mu||M.nu!=N.nu)
    {
        printf("����������ͬ���͵�,�������\n");
        exit(0);
    }
    (*Q).mu=M.mu; // ��ʼ��Q���� 
    (*Q).nu=M.nu;
    (*Q).tu=0; // Ԫ�ظ����ĳ�ֵ 
    (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
    if(!(*Q).rhead)
        exit(0);
    (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
    if(!(*Q).chead)
        exit(0);
    for(k=1;k<=(*Q).mu;k++) // ��ʼ��Q����ͷָ������;��������Ϊ������ 
        (*Q).rhead[k]=NULL;
    for(k=1;k<=(*Q).nu;k++) // ��ʼ��Q����ͷָ������;��������Ϊ������ 
        (*Q).chead[k]=NULL;
    // ����ָ���е����������� 
    col=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink)); 
    if(!col)
        exit(0);
    for(k=1;k<=(*Q).nu;k++) // ����ֵ 
        col[k]=NULL;
    for(i=1;i<=M.mu;i++) // ���е�˳����� 
    {
        pm=M.rhead[i];    // pmָ�����M�ĵ�i�еĵ�1����� 
        pn=N.rhead[i];    // pnָ�����N�ĵ�i�еĵ�1����� 
        while(pm&&pn)    // pm��pn������ 
        {
            if(pm->j<pn->j) // ����M��ǰ������С�ھ���N��ǰ������ 
            {
                p=(OLink)malloc(sizeof(OLNode)); // ���ɾ���Q�Ľ�� 
                if(!p)
                    exit(0);
                (*Q).tu++;    // ����Ԫ������1 
                p->i=i;        // ����㸳ֵ 
                p->j=pm->j;
                p->e=pm->e;
                p->right=NULL;
                pm=pm->right; // pmָ�������� 
            }
            else if(pm->j>pn->j)// ����M��ǰ�����д��ھ���N��ǰ������ 
            {
                p=(OLink)malloc(sizeof(OLNode)); // ���ɾ���Q�Ľ�� 
                if(!p)
                    exit(0);
                (*Q).tu++;    // ����Ԫ������1 
                p->i=i;        // ����㸳ֵ 
                p->j=pn->j;
                p->e=pn->e;
                p->right=NULL;
                pn=pn->right; // pnָ�������� 
            }
            // ����M��N��ǰ�������������Ԫ��֮�Ͳ�Ϊ0
            else if(pm->e+pn->e) 
            {
                p=(OLink)malloc(sizeof(OLNode)); // ���ɾ���Q�Ľ�� 
                if(!p)
                    exit(0);
                (*Q).tu++; // ����Ԫ������1 
                p->i=i; // ����㸳ֵ 
                p->j=pn->j;
                p->e=pm->e+pn->e;
                p->right=NULL;
                pm=pm->right; // pmָ�������� 
                pn=pn->right; // pnָ�������� 
            }
            else // ����M��N��ǰ�������������Ԫ��֮��Ϊ0 
            {
                pm=pm->right; // pmָ�������� 
                pn=pn->right; // pnָ�������� 
                continue;
            }
            if((*Q).rhead[i]==NULL) // pΪ���еĵ�1�����
                // p���ڸ��еı�ͷ��pqָ��p(���е����һ�����) 
                (*Q).rhead[i]=pq=p; 
            else // ����pq��ָ���֮�� 
            {
                pq->right=p; // ����в��� 
                pq=pq->right; // pqָ����е����һ����� 
            }
            if((*Q).chead[p->j]==NULL) // pΪ���еĵ�1�����
                 // p���ڸ��еı�ͷ��col[p->j]ָ��p  
                (*Q).chead[p->j]=col[p->j]=p;
            else // ����col[p->]��ָ���֮�� 
            {
                col[p->j]->down=p; // ����в���
                 // col[p->j]ָ����е����һ����� 
                col[p->j]=col[p->j]->down;
            }
        }
        while(pm) // ������M���е�ʣ��Ԫ�ز������Q 
        {
            p=(OLink)malloc(sizeof(OLNode)); // ���ɾ���Q�Ľ�� 
            if(!p)
                exit(0);
            (*Q).tu++; // ����Ԫ������1 
            p->i=i; // ����㸳ֵ 
            p->j=pm->j;
            p->e=pm->e;
            p->right=NULL;
            pm=pm->right; // pmָ�������� 
            if((*Q).rhead[i] == NULL) // pΪ���еĵ�1����� 
                // p���ڸ��еı�ͷ��pqָ��p(���е����һ�����)
                (*Q).rhead[i] = pq = p;  
            else // ����pq��ָ���֮�� 
            {
                pq->right=p; // ����в��� 
                pq=pq->right; // pqָ����е����һ����� 
            }
            if((*Q).chead[p->j] == NULL) // pΪ���еĵ�1�����
                 // p���ڸ��еı�ͷ��col[p->j]ָ��p 
                (*Q).chead[p->j] = col[p->j] = p; 
            else // ����col[p->j]��ָ���֮�� 
            {
                col[p->j]->down=p; // ����в���
                // col[p->j]ָ����е����һ����� 
                col[p->j]=col[p->j]->down;  
            }
        }
        while(pn) // ������N���е�ʣ��Ԫ�ز������Q 
        {
            p=(OLink)malloc(sizeof(OLNode)); // ���ɾ���Q�Ľ�� 
            if(!p)
                exit(0);
            (*Q).tu++; // ����Ԫ������1 
            p->i=i; // ����㸳ֵ 
            p->j=pn->j;
            p->e=pn->e;
            p->right=NULL;
            pn=pn->right; // pmָ�������� 
            if((*Q).rhead[i]==NULL) // pΪ���еĵ�1����� 
                // p���ڸ��еı�ͷ��pqָ��p(���е����һ�����)
                (*Q).rhead[i]=pq=p;  
            else // ����pq��ָ���֮�� 
            {
                pq->right=p; // ����в��� 
                pq=pq->right; // pqָ����е����һ����� 
            }
            if((*Q).chead[p->j]==NULL) // pΪ���еĵ�1�����
                // p���ڸ��еı�ͷ��col[p->j]ָ��p  
                (*Q).chead[p->j]=col[p->j]=p; 
            else // ����col[p->j]��ָ���֮�� 
            {
                col[p->j]->down=p; // ����в���
                // col[p->j]ָ����е����һ����� 
                col[p->j]=col[p->j]->down;  
            }
        }
    }
    for(k=1;k<=(*Q).nu;k++)
        if(col[k]) // k���н�� 
            col[k]->down=NULL; //  ��������һ������downָ��Ϊ�� 
    free(col);
    return 1;
}
int main()
{
    CrossList A,B,C;
    InitSMatrix(&A); // CrossList���͵ı����ڳ���ʹ��֮ǰ�����ʼ�� 
    InitSMatrix(&B);
    printf("��������A: ");
    CreateSMatrix(&A);
    PrintSMatrix(A);
    PrintSMatrix(B);
    printf("��������B2:(�����A���С�������ͬ���С��зֱ�Ϊ%d,%d)\n",
        A.mu,A.nu);
    CreateSMatrix(&B);
    PrintSMatrix(B);
    printf("����C1(A+B): ");
    AddSMatrix(A,B,&C);
    PrintSMatrix(C);
  
  
    return 0; 
}
