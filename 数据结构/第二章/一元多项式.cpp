#include <iostream>
#include <stdlib.h>
using namespace std;
//定义结构体；
typedef struct Polynode
{
    int coef;
    int exp;
    struct Polynode *next;
}Polynode,*Polylist;
 
//创建关于多项式结构体的单链表，以系数0结束输入
Polylist Polycreate()
{
    Polynode *head,*rear,*s;
    int c,e;
    head=(Polynode *)malloc(sizeof(Polynode));//申请空间建立多项式的头结点
    rear=head;
    scanf("%d %d",&c,&e);
    while(c!=0)
    {
        s=(Polynode *)malloc(sizeof(Polynode));
        s->coef=c;
        s->exp=e;
        rear->next=s;
        rear=s;
        scanf("%d %d",&c,&e);
    }//尾插法建立单链表
    rear->next=NULL;
    return(head);
}
 
//多项式polya和polyb相加，结果存放在head单链表中
Polylist Polyadd(Polylist polya,Polylist polyb)
{
    Polynode *head,*p,*q,*tail,*s;//head为相加后单链表的头结点，tail为尾插法的尾巴节点
    int sum;
    head=(Polynode *)malloc(sizeof(Polynode));
    p=polya->next;
    q=polyb->next;
    tail=head;
    while(p!=NULL&&q!=NULL)
    {
        s=(Polynode *)malloc(sizeof(Polynode));
        if(p->exp<q->exp)
        {
            s->coef=p->coef;
            s->exp=p->exp;
            tail->next=s;
            tail=s;
            p=p->next;
        }
        else if(p->exp==q->exp)
        {
            sum=p->coef+q->coef;
            if(sum!=0)
            {
                s->coef=sum;
                s->exp=p->exp;
                tail->next=s;
                tail=s;
                p=p->next;
                q=q->next;
            }
            else return(head);
        }
        else
        {
            s->coef=q->coef;
            s->exp=q->exp;
            tail->next=s;
            tail=s;
            q=q->next;
        }
    }
    if(p!=NULL)
        tail->next=p;
    else
        tail->next=q;
    return(head);
}
 
//打印多项式
void show(Polylist poly)
{
    Polynode *p;
    int c;
    int e;
    p=poly->next;
    while(p->next!=NULL)//避免最后一项也出现加号
    {
        c=p->coef;
        e=p->exp;
        printf("%dX^%d+",c,e);
        p=p->next;
    }
    c=p->coef;
    e=p->exp;
    printf("%dX^%d",c,e);
}
int main(void)
{
    printf("请按升幂输入多项式A,以系数为0结束：\n");
    Polylist pa=Polycreate();
    printf("你输入的多项式为：\n");
    show(pa);
    printf("\n");
    printf("请按升幂输入多项式B,以系数为0结束：\n");
    Polylist pb=Polycreate();
    printf("你输入的多项式为：\n");
    show(pb);
    printf("\n");
    Polylist pc=Polyadd(pa,pb);
    printf("相加之后的多项式为：\n");
    show(pc);
    return 0;
}
