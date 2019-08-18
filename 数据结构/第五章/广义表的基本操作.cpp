#include <stdio.h>  
#include <malloc.h>  
#include <stdlib.h>  
#include <string.h>  
#define MAXSTRLEN 40  
typedef char SString[MAXSTRLEN+1];   
typedef char AtomType;                     // 定义原子类型为字符型    
typedef enum{  
    ATOM, LIST                            // ATOM==0:原子 LIST==1:子表                       
} ElemTag;   
  
typedef struct GLNode  
{  
    ElemTag tag;                // 公共部分,用于区分原子结点和表结点   
    union                               // 原子结点和表结点的联合部分   
    {  
        AtomType atom;                      // atom是原子结点的值域, AtomType由用户定义   
        struct  
        {  
            struct GLNode *hp,*tp;  
        }ptr;                                // ptr是表结点的指针域,prt.hp和ptr.tp分别指向表头和表尾   
    }a;  
} *GList, GLNode;     
  
  
//初始化的广义表L  
int InitGList(GList *L)  
{   
    *L = NULL;  
    return 1;  
}  
  
//销毁广义表L  
void DestroyGList(GList *L)   
{   
    GList q1,q2;  
    if(*L)  
    {  
        if((*L)->tag == ATOM)  
        {  
            free(*L);                                 
            *L = NULL;  
        }  
        else      
        {  
            q1 = (*L)->a.ptr.hp;  
            q2 = (*L)->a.ptr.tp;  
            free(*L);  
            *L = NULL;  
            DestroyGList(&q1);  
            DestroyGList(&q2);                      // 递归删除表头和表尾结点  
          
        }  
    }  
}  
  
  
// 采用头尾链表存储结构,由广义表L复制得到广义表T。   
int CopyGList(GList *T,GList L)  
{  
    if(!L)  
        *T = NULL;  
    else  
    {  
        *T = (GList)malloc(sizeof(GLNode));   
        if(!*T)  
            exit(0);  
        (*T)->tag = L->tag;  
        if(L->tag == ATOM)  
            (*T)->a.atom = L->a.atom;                             // 复制单原子   
        else                                                // 是表结点，则依次复制表头和表尾  
        {  
            CopyGList(&((*T)->a.ptr.hp), L->a.ptr.hp);  
            CopyGList(&((*T)->a.ptr.tp), L->a.ptr.tp);  
                                                          
              
        }  
    }  
    return 1;  
}  
  
// 返回广义表的长度,即元素个数  
int GListLength(GList L)  
{  
    int len = 0;  
    if(!L)  
        return 0;  
    if(L->tag == ATOM)  
        return 1;  
    while(L)  
    {  
        L = L->a.ptr.tp;   
        len++;  
    }  
    return len;  
}  
  
  
// 采用头尾链表存储结构,求广义表L的深度。  
int GListDepth(GList L)  
{  
    int max, dep;  
    GList pp;  
      
    if(!L)  
        return 1;                                                                   // 空表深度为1  
    if(L->tag == ATOM)  
        return 0;                                                                           // 原子深度为0  
    for(max = 0, pp = L; pp; pp = pp->a.ptr.tp)  
    {  
                                                                                    // 递归求以pp->a.ptr.hp为头指针的子表深度   
        dep = GListDepth(pp->a.ptr.hp);  
        if(dep > max)  
            max = dep;  
    }  
    return max+1;                                                           // 非空表的深度是各元素的深度的最大值加1   
}  
  
// 判定广义表是否为空  
int GListEmpty(GList L)  
{  
    if(!L)  
        return 1;  
    else  
        return 0;  
}  
  
// 取广义表L的头  
GList GetHead(GList L)  
{  
    GList h,p;  
  
    if(!L)  
    {  
        printf("空表无表头!\n");  
        exit(0);  
    }  
    p = L->a.ptr.tp;   
    L->a.ptr.tp = NULL;  
    CopyGList(&h,L);  
    L->a.ptr.tp = p;  
    return h;  
}  
  
// 取广义表L的尾  
GList GetTail(GList L)  
{  
    GList t;  
    if(!L)  
    {  
        printf("空表无表尾!\n");  
        exit(0);  
    }  
    CopyGList(&t, L->a.ptr.tp);  
    return t;  
}  
  
  
  
// 插入元素e作为广义表L的第一元素(表头,也可能是子表)   
int InsertFirst_GL(GList *L,GList e)  
{  
    GList p = (GList)malloc(sizeof(GLNode));  
    if(!p)  
        exit(0);  
    p->tag = LIST;  
    p->a.ptr.hp = e;  
    p->a.ptr.tp = *L;  
    *L = p;  
    return 1;  
}  
  
  
  
// 删除广义表L的第一元素,并用e返回其值  
int DeleteFirst_GL(GList *L,GList *e)  
{   
    GList p;  
    *e = (*L)->a.ptr.hp;   
    p = *L;  
    *L = (*L)->a.ptr.tp;   
    free(p);  
    return 1;  
}  
  
  
  
// 利用递归算法遍历广义表L   
void Traverse_GL(GList L,void(*v)(AtomType))  
{  
    if(L)   
        if(L->tag == ATOM)  
            v(L->a.atom);  
        else  
        {  
            Traverse_GL(L->a.ptr.hp,v);  
            Traverse_GL(L->a.ptr.tp,v);  
        }  
}  
  
// 生成一个其值等于chars的串T  
int StrAssign(SString T,char *chars)  
{   
    int i;  
    if(strlen(chars) > MAXSTRLEN)  
        return 0;  
    else  
    {  
        T[0] = strlen(chars);  
         for(i = 1; i <= T[0]; i++)  
            T[i] = *(chars + i - 1);  
        return 1;  
    }  
}  
  
// 由串S复制得串T  
int StrCopy(SString T, SString S)  
{  
    int i;  
    for(i = 0; i <= S[0]; i++)  
        T[i] = S[i];  
    return 1;  
}  
  
  
// 若S为空串,则返回1,否则返回0   
int StrEmpty(SString S)  
{  
    if(S[0] == 0)  
        return 1;  
    else  
        return 0;  
}  
  
  
  
// 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0   
int StrCompare(SString S,SString T)  
{  
    int i;  
    for(i = 1; i <= S[0] && i <= T[0]; ++i)  
        if(S[i] != T[i])  
            return S[i] - T[i];  
    return S[0]-T[0];  
}  
  
// 返回串的元素个数  
int StrLength(SString S)  
{  
    return S[0];  
}  
  
// 将S清为空串  
int ClearString(SString S)  
{  
    S[0] = 0;   // 令串长为零  
    return 1;  
}  
  
  
// 用Sub返回串S的第pos个字符起长度为len的子串。  
int SubString(SString Sub,SString S,int pos,int len)  
{   
    int i;  
    if(pos < 1 || pos >S[0] || len < 0 || len > S[0]-pos+1)  
        return 0;  
    for(i = 1; i <= len; i++)  
        Sub[i]=S[pos+i-1];  
    Sub[0] = len;  
    return 1;  
}  
  
  
// 将非空串str分割成两部分:hsub为第一个','之前的子串,str为之后的子串   
void sever(SString str,SString hstr)   
{  
    int n,i, k; 
	char a[]={","};  
	char b[]={"("};
	char c[]={")"};
    SString ch,c1,c2,c3;  
    n = StrLength(str);  
    StrAssign(c1,a);  
    StrAssign(c2,b);  
    StrAssign(c3,c);  
    SubString(ch,str,1,1);  
    for(i = 1,k = 0;i <= n && StrCompare(ch,c1) || k != 0; ++i)  
    {   
        SubString(ch, str, i, 1);  
        if(!StrCompare(ch, c2))  
            ++k;  
        else if(!StrCompare(ch,c3))  
            --k;  
    }  
    if(i <= n)  
    {  
        SubString(hstr, str, 1, i-2);  
        SubString(str, str, i, n - i + 1);  
    }  
    else  
    {  
        StrCopy(hstr, str);  
        ClearString(str);  
    }  
}  
  
  
// 广义表L。设emp="()"   
int CreateGList(GList *L, SString S)  
{  
    SString sub,hsub,emp;  
    GList p,q;  
    char a[]={"()"};  
    StrAssign(emp,a);  
    if(!StrCompare(S, emp))  
        *L = NULL;  // 创建空表   
    else  
    {  
        *L = (GList)malloc(sizeof(GLNode));  
        if(!*L)     // 建表结点   
            exit(0);  
        if(StrLength(S) == 1)   // S为单原子   
        {  
            (*L)->tag = ATOM;  
            (*L)->a.atom = S[1]; // 创建单原子广义表   
        }  
        else  
        {  
            (*L)->tag = LIST;  
            p = *L;  
            SubString(sub, S, 2, StrLength(S)-2); // 脱外层括号   
            do  
            {   // 重复建n个子表   
                sever(sub, hsub); // 从sub中分离出表头串hsub   
                CreateGList(&p->a. ptr. hp, hsub);  
                q = p;  
                if(!StrEmpty(sub))  // 表尾不空   
                {  
                    p = (GLNode *)malloc(sizeof(GLNode));  
                    if(!p)  
                        exit(0);  
                    p->tag = LIST;  
                    q->a.ptr.tp = p;  
                }  
            }while(!StrEmpty(sub));  
            q->a.ptr.tp = NULL;  
        }  
    }  
    return 1;  
}  
  
// 打印原子   
void visit(AtomType e)  
{  
    printf("%c ", e);  
}  
  
int main()  
{  
    // 广义表的表示形式是，空表:(),单原子:a,表:(a,(b),c,(d,(e)))   
    char p[1000] = {"(a,(b),c,(d,(e)))"};  
    SString t;  
    GList L,m;  
      
    InitGList(&L);  
    InitGList(&m);  
    printf("空广义表L的深度 = %d\nL是否空？%d(1:是 0:否)\n\n",  
    GListDepth(L), GListEmpty(L));  
    StrAssign(t, p);  
    CreateGList(&L, t);                                         // 创建广义表   
    printf("\n广义表L的长度 = %d\n", GListLength(L));  
    printf("广义表L的深度 = %d \nL是否空？%d(1:是 0:否)\n",  
    GListDepth(L), GListEmpty(L));  
    printf("遍历广义表L：\n");  
    Traverse_GL(L, visit);  
    printf("\n\n复制广义表m = L\n");  
    CopyGList(&m, L);  
    printf("广义表m的长度 = %d\n", GListLength(m));  
    printf("广义表m的深度 = %d\n", GListDepth(m));  
    printf("遍历广义表m：\n");  
    Traverse_GL(m,visit);  
    DestroyGList(&m);  
    m = GetHead(L);  
    printf("\n\nm是L的表头，遍历广义表m：\n");  
    Traverse_GL(m, visit);  
    DestroyGList(&m);  
    m = GetTail(L);  
    printf("\n\nm是L的表尾，遍历广义表m：\n");  
    Traverse_GL(m,visit);  
    InsertFirst_GL(&m, L);  
    printf("\n\n插入L为m的表头，遍历广义表m：\n");  
    Traverse_GL(m,visit);  
    printf("\n\n删除m的表头，遍历广义表m：\n");  
    DestroyGList(&L);  
    DeleteFirst_GL(&m, &L);  
    Traverse_GL(m, visit);  
    printf("\n");  
    DestroyGList(&m);  
    return 0;  
}
