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
        printf("栈满不能入栈\n");
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
    printf("迷宫如下‘■’代表墙,数字 或者‘☆’表示路径\n");
    int i, j;
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1)       printf("■");
            else if (maze[i][j] >= 3){
                printf("%2d", maze[i][j] - 2);
                 
            }    
            else  printf("  ");
            printf("\n");
        }
    printf("已到达出口...\n");
    printf("可见使用栈求出的路径并非最优路径，根据我依次探索的方向不同，结果也将不同\n");
}

void visit(mark p,int sign, PSeqStack S)
{
    Push_SeqStack(S,p);
    switch (sign)
    {
    case 1: p.col++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向右
    case 2: p.row++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向下
    case 3: p.col--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向左
    case 4: p.row--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向上
    }
}

int main()
{
    struct point p = { 1, 1 };
    maze[p.row][p.col] = 2;//遍历过的点设置为2
    PSeqStack S = Init_SeqStack();
    Push_SeqStack(S,p);
    while (!Empty_SeqStack(S))
    {
        Pop_SeqStack(S, &p);
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)
            break;
        if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0)//向右
        {    
            visit(p, 1, S);
            continue;
        }
        if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0)//向下
        {
            visit(p, 2, S);
            continue;
        }
        if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0)//向左
        {
            visit(p, 3, S);
            continue;
        }
        if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0)//向上
        {
            visit(p, 4, S);
            continue;
        }//以上是对迷宫的四个方向进行操作
    }
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//是否为出口
    {
        int count = GetLength_SeqStack(S)+3;//为了与迷宫0,1,2的区别所以基数要以3开始
        printf("成功找到出口，路径倒序输出：\n");
        printf("(%d,%d)\n", p.row, p.col);
        maze[p.row][p.col] = count;
        while (!Empty_SeqStack(S))//按照前驱进行查找
        {
            count--;
            Pop_SeqStack(S, &p);
            maze[p.row][p.col] = count;
            printf("(%d,%d)\n", p.row, p.col);            
        }
        printf("3秒后打印路径......");
        Sleep(3000);
        print_line();
    }
    else {
        printf("没有出路\n");
    }
    system("pause");
    return 0;
}
//end maze_stack.cpp
