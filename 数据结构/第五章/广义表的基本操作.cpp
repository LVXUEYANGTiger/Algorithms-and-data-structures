#include <stdio.h>  
#include <malloc.h>  
#include <stdlib.h>  
#include <string.h>  
#define MAXSTRLEN 40  
typedef char SString[MAXSTRLEN+1];   
typedef char AtomType;                     // ����ԭ������Ϊ�ַ���    
typedef enum{  
    ATOM, LIST                            // ATOM==0:ԭ�� LIST==1:�ӱ�                       
} ElemTag;   
  
typedef struct GLNode  
{  
    ElemTag tag;                // ��������,��������ԭ�ӽ��ͱ���   
    union                               // ԭ�ӽ��ͱ�������ϲ���   
    {  
        AtomType atom;                      // atom��ԭ�ӽ���ֵ��, AtomType���û�����   
        struct  
        {  
            struct GLNode *hp,*tp;  
        }ptr;                                // ptr�Ǳ����ָ����,prt.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β   
    }a;  
} *GList, GLNode;     
  
  
//��ʼ���Ĺ����L  
int InitGList(GList *L)  
{   
    *L = NULL;  
    return 1;  
}  
  
//���ٹ����L  
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
            DestroyGList(&q2);                      // �ݹ�ɾ����ͷ�ͱ�β���  
          
        }  
    }  
}  
  
  
// ����ͷβ����洢�ṹ,�ɹ����L���Ƶõ������T��   
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
            (*T)->a.atom = L->a.atom;                             // ���Ƶ�ԭ��   
        else                                                // �Ǳ��㣬�����θ��Ʊ�ͷ�ͱ�β  
        {  
            CopyGList(&((*T)->a.ptr.hp), L->a.ptr.hp);  
            CopyGList(&((*T)->a.ptr.tp), L->a.ptr.tp);  
                                                          
              
        }  
    }  
    return 1;  
}  
  
// ���ع����ĳ���,��Ԫ�ظ���  
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
  
  
// ����ͷβ����洢�ṹ,������L����ȡ�  
int GListDepth(GList L)  
{  
    int max, dep;  
    GList pp;  
      
    if(!L)  
        return 1;                                                                   // �ձ����Ϊ1  
    if(L->tag == ATOM)  
        return 0;                                                                           // ԭ�����Ϊ0  
    for(max = 0, pp = L; pp; pp = pp->a.ptr.tp)  
    {  
                                                                                    // �ݹ�����pp->a.ptr.hpΪͷָ����ӱ����   
        dep = GListDepth(pp->a.ptr.hp);  
        if(dep > max)  
            max = dep;  
    }  
    return max+1;                                                           // �ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ��1   
}  
  
// �ж�������Ƿ�Ϊ��  
int GListEmpty(GList L)  
{  
    if(!L)  
        return 1;  
    else  
        return 0;  
}  
  
// ȡ�����L��ͷ  
GList GetHead(GList L)  
{  
    GList h,p;  
  
    if(!L)  
    {  
        printf("�ձ��ޱ�ͷ!\n");  
        exit(0);  
    }  
    p = L->a.ptr.tp;   
    L->a.ptr.tp = NULL;  
    CopyGList(&h,L);  
    L->a.ptr.tp = p;  
    return h;  
}  
  
// ȡ�����L��β  
GList GetTail(GList L)  
{  
    GList t;  
    if(!L)  
    {  
        printf("�ձ��ޱ�β!\n");  
        exit(0);  
    }  
    CopyGList(&t, L->a.ptr.tp);  
    return t;  
}  
  
  
  
// ����Ԫ��e��Ϊ�����L�ĵ�һԪ��(��ͷ,Ҳ�������ӱ�)   
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
  
  
  
// ɾ�������L�ĵ�һԪ��,����e������ֵ  
int DeleteFirst_GL(GList *L,GList *e)  
{   
    GList p;  
    *e = (*L)->a.ptr.hp;   
    p = *L;  
    *L = (*L)->a.ptr.tp;   
    free(p);  
    return 1;  
}  
  
  
  
// ���õݹ��㷨���������L   
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
  
// ����һ����ֵ����chars�Ĵ�T  
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
  
// �ɴ�S���Ƶô�T  
int StrCopy(SString T, SString S)  
{  
    int i;  
    for(i = 0; i <= S[0]; i++)  
        T[i] = S[i];  
    return 1;  
}  
  
  
// ��SΪ�մ�,�򷵻�1,���򷵻�0   
int StrEmpty(SString S)  
{  
    if(S[0] == 0)  
        return 1;  
    else  
        return 0;  
}  
  
  
  
// ��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0   
int StrCompare(SString S,SString T)  
{  
    int i;  
    for(i = 1; i <= S[0] && i <= T[0]; ++i)  
        if(S[i] != T[i])  
            return S[i] - T[i];  
    return S[0]-T[0];  
}  
  
// ���ش���Ԫ�ظ���  
int StrLength(SString S)  
{  
    return S[0];  
}  
  
// ��S��Ϊ�մ�  
int ClearString(SString S)  
{  
    S[0] = 0;   // ���Ϊ��  
    return 1;  
}  
  
  
// ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���  
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
  
  
// ���ǿմ�str�ָ��������:hsubΪ��һ��','֮ǰ���Ӵ�,strΪ֮����Ӵ�   
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
  
  
// �����L����emp="()"   
int CreateGList(GList *L, SString S)  
{  
    SString sub,hsub,emp;  
    GList p,q;  
    char a[]={"()"};  
    StrAssign(emp,a);  
    if(!StrCompare(S, emp))  
        *L = NULL;  // �����ձ�   
    else  
    {  
        *L = (GList)malloc(sizeof(GLNode));  
        if(!*L)     // ������   
            exit(0);  
        if(StrLength(S) == 1)   // SΪ��ԭ��   
        {  
            (*L)->tag = ATOM;  
            (*L)->a.atom = S[1]; // ������ԭ�ӹ����   
        }  
        else  
        {  
            (*L)->tag = LIST;  
            p = *L;  
            SubString(sub, S, 2, StrLength(S)-2); // ���������   
            do  
            {   // �ظ���n���ӱ�   
                sever(sub, hsub); // ��sub�з������ͷ��hsub   
                CreateGList(&p->a. ptr. hp, hsub);  
                q = p;  
                if(!StrEmpty(sub))  // ��β����   
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
  
// ��ӡԭ��   
void visit(AtomType e)  
{  
    printf("%c ", e);  
}  
  
int main()  
{  
    // �����ı�ʾ��ʽ�ǣ��ձ�:(),��ԭ��:a,��:(a,(b),c,(d,(e)))   
    char p[1000] = {"(a,(b),c,(d,(e)))"};  
    SString t;  
    GList L,m;  
      
    InitGList(&L);  
    InitGList(&m);  
    printf("�չ����L����� = %d\nL�Ƿ�գ�%d(1:�� 0:��)\n\n",  
    GListDepth(L), GListEmpty(L));  
    StrAssign(t, p);  
    CreateGList(&L, t);                                         // ���������   
    printf("\n�����L�ĳ��� = %d\n", GListLength(L));  
    printf("�����L����� = %d \nL�Ƿ�գ�%d(1:�� 0:��)\n",  
    GListDepth(L), GListEmpty(L));  
    printf("���������L��\n");  
    Traverse_GL(L, visit);  
    printf("\n\n���ƹ����m = L\n");  
    CopyGList(&m, L);  
    printf("�����m�ĳ��� = %d\n", GListLength(m));  
    printf("�����m����� = %d\n", GListDepth(m));  
    printf("���������m��\n");  
    Traverse_GL(m,visit);  
    DestroyGList(&m);  
    m = GetHead(L);  
    printf("\n\nm��L�ı�ͷ�����������m��\n");  
    Traverse_GL(m, visit);  
    DestroyGList(&m);  
    m = GetTail(L);  
    printf("\n\nm��L�ı�β�����������m��\n");  
    Traverse_GL(m,visit);  
    InsertFirst_GL(&m, L);  
    printf("\n\n����LΪm�ı�ͷ�����������m��\n");  
    Traverse_GL(m,visit);  
    printf("\n\nɾ��m�ı�ͷ�����������m��\n");  
    DestroyGList(&L);  
    DeleteFirst_GL(&m, &L);  
    Traverse_GL(m, visit);  
    printf("\n");  
    DestroyGList(&m);  
    return 0;  
}
