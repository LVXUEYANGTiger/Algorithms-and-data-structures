#include<stdio.h>
#include<stdlib.h>
#include<time.h> //时间函数 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status是函数的类型，其值是函数结果状态码
typedef int Status;

//=================================  排队队列定义开始================================
typedef struct{    
    int OccurTime;            //到达时间
    int Duration;            //办理事务所需时间
}CustomerNode;

typedef CustomerNode ElemType;

//结点定义
typedef struct QNode{
    ElemType data;                //数据节点；
    struct QNode *next;            //结点的指针域
}QNode;

//队列链定义
typedef struct{
    QNode *front;                //队头指针
    QNode *rare;                //队尾指针
}LinkQueue;

//初始化一个空队列
Status InitQueue(LinkQueue &Q){
    Q.front=Q.rare=(QNode *)malloc(sizeof(QNode));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next=NULL;
    return OK;
}

//判断是否为空队列
Status QueueEmpty(LinkQueue &Q){
    if(Q.front==Q.rare)
        return TRUE;
    return FALSE;
}
 
//判断长度
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


//向队列尾部插入元素e
Status EnQueue(LinkQueue &Q,ElemType e){
    //生成 结点
    QNode *q;                        //指向新生成的结点
    q=(QNode *)malloc(sizeof(QNode));
    if(!q) exit(OVERFLOW);
    q->data=e;
    q->next=NULL;

    Q.rare->next=q;
    Q.rare=q;
    return OK;
}

//删除队列头部元素并返回
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
        printf("%s\n","空队列");
    QNode *q=Q.front;
    while(q->next){
        printf("地址：%p",q->next);
        printf("值：%d\n",q->next->data);
        q=q->next;
    }
}

//=================================  排队队列定义结束 ================================




//=================================  事件链表定义开始 ================================

typedef struct{
    int OccurTime;
    int NType;
    int dur;
}Event,EvElemType;

typedef struct LNode{
    EvElemType data;                //单链表中结点的数据域
    struct LNode *next;                //结点的指针域
}LNode,*LinkList;

typedef LinkList EventList;


void InitList(LinkList &L){
    L=(LinkList)malloc(sizeof(LNode));    //生成新节点    
    if(!L) exit(OVERFLOW);
    L->next=NULL;
}

//在单链表中，取得第i个位置的值必须从头开始找起，因为每个结点元素的位置信息只能通过其直接前继结点确定
//获取L 中第i个元素的值，并用 e 返回。
Status GetElem_L(LinkList &L,int i,EvElemType &e){
    //此处L为带有头结点的单链表
    LNode * q;
    q=L->next;                    //p指向第一个结点
    int j=1;
    while(q&&j<i){
        //移动指针的错误写法：q++; 因为在链式存储结构中存储地址不一定是连续的
        q=q->next;
        j++;
    }    
    if(j!=i)
        return ERROR;
    e=q->data;
    return OK;
}//时间复杂度为 O（n）


//插入元素，在L中第i个位置之前插入数据 e
Status ListInsert_L(LinkList &L,int i,EvElemType e){
    //1.找到指向 第 i-1 处元素的指针
    LNode * q;
    q=L;                                //    q指向头结点
    int j=0;
    while(q&&j<(i-1)){
        q=q->next;                        //后移结点
        j++;
    }
    
    //正确j的可能值：0，(i-1),  
    if(!q||i<1)                        //1.q为NULL(i大于表长+1)  2.i不能小于1
        return ERROR;
    LNode * s;
    s=(LinkList)malloc(sizeof(LNode));    //生成新节点        
    s->data=e;                            //新结点数据域inti
    s->next=q->next; q->next=s;            //插入新结点    
    return OK;
}//时间复杂度为 O（n）

//按照事件发生的时间点顺序，将事件结点插入事件链表 时间点从小到大排序
Status OrderInsert(LinkList &L,EvElemType e){
    LNode * q;
    q=L;                                //    q指向头结点
    if(!q->next){
        ListInsert_L(L,1,e);
    }else{
        while(q->next&&e.OccurTime>=q->next->data.OccurTime){
            q=q->next;                        //后移指针
        }

        LNode * s;
        s=(LinkList)malloc(sizeof(LNode));    //生成新节点        
        s->data=e;                            //新结点数据域inti
        s->next=q->next; q->next=s;            //插入新结点            
    }    
    return OK;
}


//删除元素，在L中删除位置为i的元素，并用将返回值存储在e中。
Status ListDelete_L(LinkList &L,int i,EvElemType &e){
    //1.找到指向 第 i-1 处元素的指针
    LNode * q;
    q=L;                                //    q指向头结点
    int j=0;
    while(q&&j<(i-1)){
        q=q->next;                        //后移指针
        j++;
    }
    if(!(q->next)||i<1)                        //1.q->next不能为NULL(i位置不存在)  2.i不能小于1
        return ERROR;
    e=q->next->data;                    //将被删除的值保存在e中
    LNode * tem=q->next;                //保存 将被删除元素的坐在位置
    q->next=q->next->next;                //删除元素
    free(tem);                            //释放被删除元素占用的内存空间
    return OK;
}//时间复杂度为 O（n）


Status ListEmpty(LinkList &L){
    if(!L->next)
        return OK;
    return ERROR;
}

void printAllValues(LinkList &L){
    if(!L->next)
        printf("%s\n","此表为空但链表");
    LNode *q;
    q=L;
    while(q->next){
        q=q->next;                        //指针后移
        printf("地址：%p，",q);
        printf("OccurTime：%d，",q->data.OccurTime);
        printf("NType：%d\n",q->data.NType);
    }
}//时间复杂度为 O（n）


//=================================  事件链表定义结束 ================================



//=================================  银行排队业务模拟程序定义开始 ================================
EventList ev;                                //事件链表
Event en;                                    //事件结点

CustomerNode cn;                                //客户节点
LinkQueue q[5];                                //客户队列
int CloseTime;                                //银行结束时间

int TotalTime,CustomerNum;                    //累计逗留时间 ，累计客户数量

void OpenDay(){
    TotalTime=0;
    CustomerNum=0;

    InitList(ev);                            //初始化事件链表
    en.OccurTime=0;                            //设置第一个客户到达事件
    en.NType=0;

    //插入事件
    OrderInsert(ev,en);    

    int i=1;
    //初始化任务队列
    for(i=1;i<5;i++){
        InitQueue(q[i]);
    }    
}


//寻找队伍人数最少的队列。
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

//客户到达
void CustomerArrived(){
    ++CustomerNum;                                //增加客户数量

    int durTime=rand()%31;                        //产生0-30 间的随机整数，为到达客户等待的时间。

    int interTime=rand()%6;                        //产生0-5 间的随机整数，为与下一客户到达时间的时间间隔。
    
    int depT=en.OccurTime+durTime;
    int arrT=en.OccurTime+interTime;
    
    //开始排队，找到最短队伍，并加入队伍。
    int i=MinQueue();
    cn.OccurTime=en.OccurTime;
    cn.Duration=durTime;    
    EnQueue(q[i],cn);

    //把当前客户离开事件，加入事件列表
    en.OccurTime=depT;
    en.NType=i;
    en.dur=durTime;
    OrderInsert(ev,en);

    //下一客户到达事件，加入事件列表。
    en.OccurTime=arrT;
    en.NType=0;
    en.dur=0;
    if(en.OccurTime<CloseTime)
        OrderInsert(ev,en);        
}

//客户离开
void CustomerDepature(){    
    int i=en.NType;
    CustomerNode c;
    DeQueue(q[i],c);                                //删除队列元素（客户离开）
    TotalTime+=c.Duration;                            //累加客户业务等待时间
}

//计算平均逗留时间
void CloseDay(){
    printf("\n总时间：%d\n",TotalTime);
    printf("客户总数量：%d\n",CustomerNum);
    printf("平均逗留时间：%d\n",TotalTime/CustomerNum);
}                                            

//银行排队模拟程序
void Bank_Simulation(int CloseTime){
    OpenDay();
    
    while(!ListEmpty(ev)){        
        ListDelete_L(ev,1,en);                

        if(en.NType==0){
            printf("时间点：%d，客户到达\n",en.OccurTime);    
            CustomerArrived();                    //客户到来
        }else{
            printf("时间点：%d，客户离开，",en.OccurTime);    
            printf("窗口：%d，",en.NType);    
            printf("等待时间：%d\n",en.dur);
            CustomerDepature();                    //客户离开
        }
        
    }
    CloseDay();                                            //计算平均逗留时间
}


//=================================  银行排队业务模拟程序定义结束 ================================



int main(void){
    CloseTime=30;
    srand((int)time(NULL));
    Bank_Simulation(CloseTime);    
    return 0;
}
