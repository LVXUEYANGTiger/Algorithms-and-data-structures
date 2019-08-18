#include<stdio.h>
#include<stdlib.h>
#include<time.h> //ʱ�亯�� 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬��
typedef int Status;

//=================================  �ŶӶ��ж��忪ʼ================================
typedef struct{    
    int OccurTime;            //����ʱ��
    int Duration;            //������������ʱ��
}CustomerNode;

typedef CustomerNode ElemType;

//��㶨��
typedef struct QNode{
    ElemType data;                //���ݽڵ㣻
    struct QNode *next;            //����ָ����
}QNode;

//����������
typedef struct{
    QNode *front;                //��ͷָ��
    QNode *rare;                //��βָ��
}LinkQueue;

//��ʼ��һ���ն���
Status InitQueue(LinkQueue &Q){
    Q.front=Q.rare=(QNode *)malloc(sizeof(QNode));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next=NULL;
    return OK;
}

//�ж��Ƿ�Ϊ�ն���
Status QueueEmpty(LinkQueue &Q){
    if(Q.front==Q.rare)
        return TRUE;
    return FALSE;
}
 
//�жϳ���
Status QueueLength(LinkQueue &Q){
    if(Q.front==Q.rare)
        return 0;
    int i=0;
    QNode *q=Q.front;
    while(q->next){
        q=q->next;
        i++;
    }
    return i;
}


//�����β������Ԫ��e
Status EnQueue(LinkQueue &Q,ElemType e){
    //���� ���
    QNode *q;                        //ָ�������ɵĽ��
    q=(QNode *)malloc(sizeof(QNode));
    if(!q) exit(OVERFLOW);
    q->data=e;
    q->next=NULL;

    Q.rare->next=q;
    Q.rare=q;
    return OK;
}

//ɾ������ͷ��Ԫ�ز�����
Status DeQueue(LinkQueue &Q,ElemType &e){
    if(Q.front==Q.rare) return ERROR;
    QNode *q=Q.front->next;
    e=Q.front->next->data;
    Q.front->next=Q.front->next->next;
    if(!Q.front->next)
        Q.rare=Q.front;
    free(q);
    return OK;
}

void printV(LinkQueue &Q){
    if(Q.front==Q.rare) 
        printf("%s\n","�ն���");
    QNode *q=Q.front;
    while(q->next){
        printf("��ַ��%p",q->next);
        printf("ֵ��%d\n",q->next->data);
        q=q->next;
    }
}

//=================================  �ŶӶ��ж������ ================================




//=================================  �¼������忪ʼ ================================

typedef struct{
    int OccurTime;
    int NType;
    int dur;
}Event,EvElemType;

typedef struct LNode{
    EvElemType data;                //�������н���������
    struct LNode *next;                //����ָ����
}LNode,*LinkList;

typedef LinkList EventList;


void InitList(LinkList &L){
    L=(LinkList)malloc(sizeof(LNode));    //�����½ڵ�    
    if(!L) exit(OVERFLOW);
    L->next=NULL;
}

//�ڵ������У�ȡ�õ�i��λ�õ�ֵ�����ͷ��ʼ������Ϊÿ�����Ԫ�ص�λ����Ϣֻ��ͨ����ֱ��ǰ�̽��ȷ��
//��ȡL �е�i��Ԫ�ص�ֵ������ e ���ء�
Status GetElem_L(LinkList &L,int i,EvElemType &e){
    //�˴�LΪ����ͷ���ĵ�����
    LNode * q;
    q=L->next;                    //pָ���һ�����
    int j=1;
    while(q&&j<i){
        //�ƶ�ָ��Ĵ���д����q++; ��Ϊ����ʽ�洢�ṹ�д洢��ַ��һ����������
        q=q->next;
        j++;
    }    
    if(j!=i)
        return ERROR;
    e=q->data;
    return OK;
}//ʱ�临�Ӷ�Ϊ O��n��


//����Ԫ�أ���L�е�i��λ��֮ǰ�������� e
Status ListInsert_L(LinkList &L,int i,EvElemType e){
    //1.�ҵ�ָ�� �� i-1 ��Ԫ�ص�ָ��
    LNode * q;
    q=L;                                //    qָ��ͷ���
    int j=0;
    while(q&&j<(i-1)){
        q=q->next;                        //���ƽ��
        j++;
    }
    
    //��ȷj�Ŀ���ֵ��0��(i-1),  
    if(!q||i<1)                        //1.qΪNULL(i���ڱ�+1)  2.i����С��1
        return ERROR;
    LNode * s;
    s=(LinkList)malloc(sizeof(LNode));    //�����½ڵ�        
    s->data=e;                            //�½��������inti
    s->next=q->next; q->next=s;            //�����½��    
    return OK;
}//ʱ�临�Ӷ�Ϊ O��n��

//�����¼�������ʱ���˳�򣬽��¼��������¼����� ʱ����С��������
Status OrderInsert(LinkList &L,EvElemType e){
    LNode * q;
    q=L;                                //    qָ��ͷ���
    if(!q->next){
        ListInsert_L(L,1,e);
    }else{
        while(q->next&&e.OccurTime>=q->next->data.OccurTime){
            q=q->next;                        //����ָ��
        }

        LNode * s;
        s=(LinkList)malloc(sizeof(LNode));    //�����½ڵ�        
        s->data=e;                            //�½��������inti
        s->next=q->next; q->next=s;            //�����½��            
    }    
    return OK;
}


//ɾ��Ԫ�أ���L��ɾ��λ��Ϊi��Ԫ�أ����ý�����ֵ�洢��e�С�
Status ListDelete_L(LinkList &L,int i,EvElemType &e){
    //1.�ҵ�ָ�� �� i-1 ��Ԫ�ص�ָ��
    LNode * q;
    q=L;                                //    qָ��ͷ���
    int j=0;
    while(q&&j<(i-1)){
        q=q->next;                        //����ָ��
        j++;
    }
    if(!(q->next)||i<1)                        //1.q->next����ΪNULL(iλ�ò�����)  2.i����С��1
        return ERROR;
    e=q->next->data;                    //����ɾ����ֵ������e��
    LNode * tem=q->next;                //���� ����ɾ��Ԫ�ص�����λ��
    q->next=q->next->next;                //ɾ��Ԫ��
    free(tem);                            //�ͷű�ɾ��Ԫ��ռ�õ��ڴ�ռ�
    return OK;
}//ʱ�临�Ӷ�Ϊ O��n��


Status ListEmpty(LinkList &L){
    if(!L->next)
        return OK;
    return ERROR;
}

void printAllValues(LinkList &L){
    if(!L->next)
        printf("%s\n","�˱�Ϊ�յ�����");
    LNode *q;
    q=L;
    while(q->next){
        q=q->next;                        //ָ�����
        printf("��ַ��%p��",q);
        printf("OccurTime��%d��",q->data.OccurTime);
        printf("NType��%d\n",q->data.NType);
    }
}//ʱ�临�Ӷ�Ϊ O��n��


//=================================  �¼���������� ================================



//=================================  �����Ŷ�ҵ��ģ������忪ʼ ================================
EventList ev;                                //�¼�����
Event en;                                    //�¼����

CustomerNode cn;                                //�ͻ��ڵ�
LinkQueue q[5];                                //�ͻ�����
int CloseTime;                                //���н���ʱ��

int TotalTime,CustomerNum;                    //�ۼƶ���ʱ�� ���ۼƿͻ�����

void OpenDay(){
    TotalTime=0;
    CustomerNum=0;

    InitList(ev);                            //��ʼ���¼�����
    en.OccurTime=0;                            //���õ�һ���ͻ������¼�
    en.NType=0;

    //�����¼�
    OrderInsert(ev,en);    

    int i=1;
    //��ʼ���������
    for(i=1;i<5;i++){
        InitQueue(q[i]);
    }    
}


//Ѱ�Ҷ����������ٵĶ��С�
int MinQueue(){
    int len=QueueLength(q[1]);
    int cur=1;
    for(int i=2;i<5;i++){
        if(len>QueueLength(q[i])){
            len=QueueLength(q[i]);
            cur=i;
        }
    }
    return cur;
}

//�ͻ�����
void CustomerArrived(){
    ++CustomerNum;                                //���ӿͻ�����

    int durTime=rand()%31;                        //����0-30 ������������Ϊ����ͻ��ȴ���ʱ�䡣

    int interTime=rand()%6;                        //����0-5 ������������Ϊ����һ�ͻ�����ʱ���ʱ������
    
    int depT=en.OccurTime+durTime;
    int arrT=en.OccurTime+interTime;
    
    //��ʼ�Ŷӣ��ҵ���̶��飬��������顣
    int i=MinQueue();
    cn.OccurTime=en.OccurTime;
    cn.Duration=durTime;    
    EnQueue(q[i],cn);

    //�ѵ�ǰ�ͻ��뿪�¼��������¼��б�
    en.OccurTime=depT;
    en.NType=i;
    en.dur=durTime;
    OrderInsert(ev,en);

    //��һ�ͻ������¼��������¼��б�
    en.OccurTime=arrT;
    en.NType=0;
    en.dur=0;
    if(en.OccurTime<CloseTime)
        OrderInsert(ev,en);        
}

//�ͻ��뿪
void CustomerDepature(){    
    int i=en.NType;
    CustomerNode c;
    DeQueue(q[i],c);                                //ɾ������Ԫ�أ��ͻ��뿪��
    TotalTime+=c.Duration;                            //�ۼӿͻ�ҵ��ȴ�ʱ��
}

//����ƽ������ʱ��
void CloseDay(){
    printf("\n��ʱ�䣺%d\n",TotalTime);
    printf("�ͻ���������%d\n",CustomerNum);
    printf("ƽ������ʱ�䣺%d\n",TotalTime/CustomerNum);
}                                            

//�����Ŷ�ģ�����
void Bank_Simulation(int CloseTime){
    OpenDay();
    
    while(!ListEmpty(ev)){        
        ListDelete_L(ev,1,en);                

        if(en.NType==0){
            printf("ʱ��㣺%d���ͻ�����\n",en.OccurTime);    
            CustomerArrived();                    //�ͻ�����
        }else{
            printf("ʱ��㣺%d���ͻ��뿪��",en.OccurTime);    
            printf("���ڣ�%d��",en.NType);    
            printf("�ȴ�ʱ�䣺%d\n",en.dur);
            CustomerDepature();                    //�ͻ��뿪
        }
        
    }
    CloseDay();                                            //����ƽ������ʱ��
}


//=================================  �����Ŷ�ҵ��ģ���������� ================================



int main(void){
    CloseTime=30;
    srand((int)time(NULL));
    Bank_Simulation(CloseTime);    
    return 0;
}
