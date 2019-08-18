#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;// 稀疏矩阵的十字链表存储表示 
typedef struct OLNode
{
    int i,j;    // 该非零元的行和列下标 
    ElemType e;    // 非零元素值 
    struct OLNode *right,*down; // 该非零元所在行表和列表的后继链域 
}OLNode, *OLink;
typedef struct// 行和列链表头指针向量基址,由CreatSMatrix_OL()分配
{
    OLink *rhead, *chead; 
    int mu, nu, tu;        // 稀疏矩阵的行数、列数和非零元个数 
}CrossList;
// 初始化M(CrossList类型的变量必须初始化,否则创建、复制矩阵将出错) 
int InitSMatrix(CrossList *M)
{
    (*M).rhead=(*M).chead=NULL;
    (*M).mu=(*M).nu=(*M).tu=0;
    return 1;
}
// 创建稀疏矩阵M,采用十字链表存储表示。
int CreateSMatrix(CrossList *M)
{ 
    int i,j,k,m,n,t;
    ElemType e;
    OLNode *p,*q;
    if((*M).rhead)
    {
    	free(M->rhead);
	}
    printf("请输入稀疏矩阵的行数 列数 非零元个数:\n ");
    scanf("%d%d%d",&m,&n,&t);
    (*M).mu=m;
    (*M).nu=n;
    (*M).tu=t;
    //初始化行链表头
    (*M).rhead=(OLink*)malloc((m+1)*sizeof(OLink));
    if(!(*M).rhead)
        exit(0);
    //初始化列链表头
    (*M).chead=(OLink*)malloc((n+1)*sizeof(OLink));
    if(!(*M).chead)
        exit(0);
    for(k=1;k<=m;k++) // 初始化行头指针向量;各行链表为空链表 
        (*M).rhead[k]=NULL;
    for(k=1;k<=n;k++) // 初始化列头指针向量;各列链表为空链表 
        (*M).chead[k]=NULL;
    printf("请按任意次序输入%d个非零元的行 列 元素值:\n",(*M).tu);
    for(k=0;k<t;k++)
    {
        scanf("%d%d%d",&i,&j,&e);
        p=(OLNode*)malloc(sizeof(OLNode));
        if(!p)
            exit(0);
        p->i=i; // 生成结点 
        p->j=j;
        p->e=e;
        if((*M).rhead[i]==NULL||(*M).rhead[i]->j>j)    
        {
            // p插在该行的第一个结点处
            p->right=(*M).rhead[i];
            (*M).rhead[i]=p;
        }
        else // 寻查在行表中的插入位置 
        {
            //从该行的行链表头开始，直到找到
            for(q=(*M).rhead[i]; q->right && q->right->j < j;q = q->right);
                
            p->right=q->right; // 完成行插入 
            q->right=p;
        }
        if((*M).chead[j] == NULL || (*M).chead[j]->i > i) 
        {
            // p插在该列的第一个结点处
            p->down = (*M).chead[j];
            (*M).chead[j] = p;
        }
        else // 寻查在列表中的插入位置 
        {
            for(q = (*M).chead[j];q->down && q->down->i < i;q = q->down)
                ;
            p->down=q->down; // 完成列插入 
            q->down=p;
        }
    }
    return 1;
}
// 按行或按列输出稀疏矩阵M
int PrintSMatrix(CrossList M)
{
    int i,j;
    OLink p;
    printf("%d行%d列%d个非零元素\n",M.mu,M.nu,M.tu);
    printf("请输入选择(1.按行输出 2.按列输出): ");
    scanf("%d",&i);
    switch(i)
    {
    case 1: 
        for(j=1;j<=M.mu;j++)
        {
            p=M.rhead[j];
            while(p)
            {
                printf("%d行%d列值为%d\n",p->i,p->j,p->e);
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
                printf("%d行%d列值为%d\n",p->i,p->j,p->e);
                p=p->down;
            }
        }
        break;
    }
    return 1;
}
// 求稀疏矩阵的和Q=M+N
int AddSMatrix(CrossList M,CrossList N,CrossList *Q)
{
    int i,k;
    OLink p,pq,pm,pn;
    OLink *col;
    
    if(M.mu!=N.mu||M.nu!=N.nu)
    {
        printf("两个矩阵不是同类型的,不能相加\n");
        exit(0);
    }
    (*Q).mu=M.mu; // 初始化Q矩阵 
    (*Q).nu=M.nu;
    (*Q).tu=0; // 元素个数的初值 
    (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
    if(!(*Q).rhead)
        exit(0);
    (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
    if(!(*Q).chead)
        exit(0);
    for(k=1;k<=(*Q).mu;k++) // 初始化Q的行头指针向量;各行链表为空链表 
        (*Q).rhead[k]=NULL;
    for(k=1;k<=(*Q).nu;k++) // 初始化Q的列头指针向量;各列链表为空链表 
        (*Q).chead[k]=NULL;
    // 生成指向列的最后结点的数组 
    col=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink)); 
    if(!col)
        exit(0);
    for(k=1;k<=(*Q).nu;k++) // 赋初值 
        col[k]=NULL;
    for(i=1;i<=M.mu;i++) // 按行的顺序相加 
    {
        pm=M.rhead[i];    // pm指向矩阵M的第i行的第1个结点 
        pn=N.rhead[i];    // pn指向矩阵N的第i行的第1个结点 
        while(pm&&pn)    // pm和pn均不空 
        {
            if(pm->j<pn->j) // 矩阵M当前结点的列小于矩阵N当前结点的列 
            {
                p=(OLink)malloc(sizeof(OLNode)); // 生成矩阵Q的结点 
                if(!p)
                    exit(0);
                (*Q).tu++;    // 非零元素数加1 
                p->i=i;        // 给结点赋值 
                p->j=pm->j;
                p->e=pm->e;
                p->right=NULL;
                pm=pm->right; // pm指针向右移 
            }
            else if(pm->j>pn->j)// 矩阵M当前结点的列大于矩阵N当前结点的列 
            {
                p=(OLink)malloc(sizeof(OLNode)); // 生成矩阵Q的结点 
                if(!p)
                    exit(0);
                (*Q).tu++;    // 非零元素数加1 
                p->i=i;        // 给结点赋值 
                p->j=pn->j;
                p->e=pn->e;
                p->right=NULL;
                pn=pn->right; // pn指针向右移 
            }
            // 矩阵M、N当前结点的列相等且两元素之和不为0
            else if(pm->e+pn->e) 
            {
                p=(OLink)malloc(sizeof(OLNode)); // 生成矩阵Q的结点 
                if(!p)
                    exit(0);
                (*Q).tu++; // 非零元素数加1 
                p->i=i; // 给结点赋值 
                p->j=pn->j;
                p->e=pm->e+pn->e;
                p->right=NULL;
                pm=pm->right; // pm指针向右移 
                pn=pn->right; // pn指针向右移 
            }
            else // 矩阵M、N当前结点的列相等且两元素之和为0 
            {
                pm=pm->right; // pm指针向右移 
                pn=pn->right; // pn指针向右移 
                continue;
            }
            if((*Q).rhead[i]==NULL) // p为该行的第1个结点
                // p插在该行的表头且pq指向p(该行的最后一个结点) 
                (*Q).rhead[i]=pq=p; 
            else // 插在pq所指结点之后 
            {
                pq->right=p; // 完成行插入 
                pq=pq->right; // pq指向该行的最后一个结点 
            }
            if((*Q).chead[p->j]==NULL) // p为该列的第1个结点
                 // p插在该列的表头且col[p->j]指向p  
                (*Q).chead[p->j]=col[p->j]=p;
            else // 插在col[p->]所指结点之后 
            {
                col[p->j]->down=p; // 完成列插入
                 // col[p->j]指向该列的最后一个结点 
                col[p->j]=col[p->j]->down;
            }
        }
        while(pm) // 将矩阵M该行的剩余元素插入矩阵Q 
        {
            p=(OLink)malloc(sizeof(OLNode)); // 生成矩阵Q的结点 
            if(!p)
                exit(0);
            (*Q).tu++; // 非零元素数加1 
            p->i=i; // 给结点赋值 
            p->j=pm->j;
            p->e=pm->e;
            p->right=NULL;
            pm=pm->right; // pm指针向右移 
            if((*Q).rhead[i] == NULL) // p为该行的第1个结点 
                // p插在该行的表头且pq指向p(该行的最后一个结点)
                (*Q).rhead[i] = pq = p;  
            else // 插在pq所指结点之后 
            {
                pq->right=p; // 完成行插入 
                pq=pq->right; // pq指向该行的最后一个结点 
            }
            if((*Q).chead[p->j] == NULL) // p为该列的第1个结点
                 // p插在该列的表头且col[p->j]指向p 
                (*Q).chead[p->j] = col[p->j] = p; 
            else // 插在col[p->j]所指结点之后 
            {
                col[p->j]->down=p; // 完成列插入
                // col[p->j]指向该列的最后一个结点 
                col[p->j]=col[p->j]->down;  
            }
        }
        while(pn) // 将矩阵N该行的剩余元素插入矩阵Q 
        {
            p=(OLink)malloc(sizeof(OLNode)); // 生成矩阵Q的结点 
            if(!p)
                exit(0);
            (*Q).tu++; // 非零元素数加1 
            p->i=i; // 给结点赋值 
            p->j=pn->j;
            p->e=pn->e;
            p->right=NULL;
            pn=pn->right; // pm指针向右移 
            if((*Q).rhead[i]==NULL) // p为该行的第1个结点 
                // p插在该行的表头且pq指向p(该行的最后一个结点)
                (*Q).rhead[i]=pq=p;  
            else // 插在pq所指结点之后 
            {
                pq->right=p; // 完成行插入 
                pq=pq->right; // pq指向该行的最后一个结点 
            }
            if((*Q).chead[p->j]==NULL) // p为该列的第1个结点
                // p插在该列的表头且col[p->j]指向p  
                (*Q).chead[p->j]=col[p->j]=p; 
            else // 插在col[p->j]所指结点之后 
            {
                col[p->j]->down=p; // 完成列插入
                // col[p->j]指向该列的最后一个结点 
                col[p->j]=col[p->j]->down;  
            }
        }
    }
    for(k=1;k<=(*Q).nu;k++)
        if(col[k]) // k列有结点 
            col[k]->down=NULL; //  令该列最后一个结点的down指针为空 
    free(col);
    return 1;
}
int main()
{
    CrossList A,B,C;
    InitSMatrix(&A); // CrossList类型的变量在初次使用之前必须初始化 
    InitSMatrix(&B);
    printf("创建矩阵A: ");
    CreateSMatrix(&A);
    PrintSMatrix(A);
    PrintSMatrix(B);
    printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",
        A.mu,A.nu);
    CreateSMatrix(&B);
    PrintSMatrix(B);
    printf("矩阵C1(A+B): ");
    AddSMatrix(A,B,&C);
    PrintSMatrix(C);
  
  
    return 0; 
}
