#include <iostream>
#include <stdlib.h>
using namespace std;
//����ṹ�壻
typedef struct Polynode
{
    int coef;
    int exp;
    struct Polynode *next;
}Polynode,*Polylist;
 
//�������ڶ���ʽ�ṹ��ĵ�������ϵ��0��������
Polylist Polycreate()
{
    Polynode *head,*rear,*s;
    int c,e;
    head=(Polynode *)malloc(sizeof(Polynode));//����ռ佨������ʽ��ͷ���
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
    }//β�巨����������
    rear->next=NULL;
    return(head);
}
 
//����ʽpolya��polyb��ӣ���������head��������
Polylist Polyadd(Polylist polya,Polylist polyb)
{
    Polynode *head,*p,*q,*tail,*s;//headΪ��Ӻ������ͷ��㣬tailΪβ�巨��β�ͽڵ�
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
 
//��ӡ����ʽ
void show(Polylist poly)
{
    Polynode *p;
    int c;
    int e;
    p=poly->next;
    while(p->next!=NULL)//�������һ��Ҳ���ּӺ�
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
    printf("�밴�����������ʽA,��ϵ��Ϊ0������\n");
    Polylist pa=Polycreate();
    printf("������Ķ���ʽΪ��\n");
    show(pa);
    printf("\n");
    printf("�밴�����������ʽB,��ϵ��Ϊ0������\n");
    Polylist pb=Polycreate();
    printf("������Ķ���ʽΪ��\n");
    show(pb);
    printf("\n");
    Polylist pc=Polyadd(pa,pb);
    printf("���֮��Ķ���ʽΪ��\n");
    show(pc);
    return 0;
}
