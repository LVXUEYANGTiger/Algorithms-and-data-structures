#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define MAX_ROW  12
#define MAX_COL  14
#define MAXSIZE 100

typedef struct point{
    int  row, col;
}mark;

typedef mark DataType;

typedef struct {
    DataType data[MAXSIZE];
    int top;
}SeqStack, * PSeqStack;

PSeqStack Init_SeqStack (void)
{
    PSeqStack S;
    S = (PSeqStack)malloc(sizeof(SeqStack));
    if (S)
        S->top = -1;
    else
        exit(-1);
    return S;
}

int Empty_SeqStack(PSeqStack S)
{
    //return (S->top==-1);
    if (S->top == -1)
        return 1;
    else
        return 0;
}

int Push_SeqStack(PSeqStack S,DataType x)
{
    if (S->top == MAXSIZE - 1)
    {
        printf("ջ��������ջ\n");
        return 0;
    }
    else 
    {
        S->top++;
        S->data[S->top] = x;
        return 1;
    }
}

int Pop_SeqStack(PSeqStack S,DataType *x)
{
    if(Empty_SeqStack(S))
        return 0;
    else
    {
        *x = S->data[S->top];
        S->top--;
        return 1;
    }
}

int GetTop_SeqStack(PSeqStack S ,DataType *x)
{
    if(Empty_SeqStack(S))
        return 0;
    else
    {
        *x = S->data[S->top];
        return 1;
    }
}
int GetLength_SeqStack(PSeqStack S)
{
    return S->top + 1;
}

void Distory_SeqStack(PSeqStack *S)
{
    if(*S)
        free(*S);
    *S = NULL;
}//end seqstack.h
int maze[12][14] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1 ,0 ,0, 0 ,0 ,1 ,0 ,1 ,1,
    1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void print_line()
{
    system("cls");
    printf("�Թ����¡���������ǽ,���� ���ߡ����ʾ·��\n");
    int i, j;
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1)       printf("��");
            else if (maze[i][j] >= 3){
                printf("%2d", maze[i][j] - 2);
                 
            }    
            else  printf("  ");
            printf("\n");
        }
    printf("�ѵ������...\n");
    printf("�ɼ�ʹ��ջ�����·����������·��������������̽���ķ���ͬ�����Ҳ����ͬ\n");
}

void visit(mark p,int sign, PSeqStack S)
{
    Push_SeqStack(S,p);
    switch (sign)
    {
    case 1: p.col++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//����
    case 2: p.row++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//����
    case 3: p.col--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//����
    case 4: p.row--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//����
    }
}

int main()
{
    struct point p = { 1, 1 };
    maze[p.row][p.col] = 2;//�������ĵ�����Ϊ2
    PSeqStack S = Init_SeqStack();
    Push_SeqStack(S,p);
    while (!Empty_SeqStack(S))
    {
        Pop_SeqStack(S, &p);
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)
            break;
        if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0)//����
        {    
            visit(p, 1, S);
            continue;
        }
        if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0)//����
        {
            visit(p, 2, S);
            continue;
        }
        if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0)//����
        {
            visit(p, 3, S);
            continue;
        }
        if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0)//����
        {
            visit(p, 4, S);
            continue;
        }//�����Ƕ��Թ����ĸ�������в���
    }
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//�Ƿ�Ϊ����
    {
        int count = GetLength_SeqStack(S)+3;//Ϊ�����Թ�0,1,2���������Ի���Ҫ��3��ʼ
        printf("�ɹ��ҵ����ڣ�·�����������\n");
        printf("(%d,%d)\n", p.row, p.col);
        maze[p.row][p.col] = count;
        while (!Empty_SeqStack(S))//����ǰ�����в���
        {
            count--;
            Pop_SeqStack(S, &p);
            maze[p.row][p.col] = count;
            printf("(%d,%d)\n", p.row, p.col);            
        }
        printf("3����ӡ·��......");
        Sleep(3000);
        print_line();
    }
    else {
        printf("û�г�·\n");
    }
    system("pause");
    return 0;
}
//end maze_stack.cpp
