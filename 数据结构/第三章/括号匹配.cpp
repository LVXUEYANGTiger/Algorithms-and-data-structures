#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>
#define true 1
#define false 0

typedef struct Node
{
    char data;
    struct Node *pNext;
}NODE, *PNODE;

typedef struct Stack
{
    PNODE pTop;
    PNODE pBottom;
}STACK, *PSTACK;
//’ªµƒ≥ı ºªØ
void init(PSTACK pS)
{
    pS->pTop = (PNODE)malloc(sizeof(NODE));
    pS->pBottom = pS->pTop;
    pS->pTop->pNext = NULL;
    return;
}
//≤Â»Î‘™ÀÿµΩ’ª∂•
void push(PSTACK pS, char val)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->data = val;
    pNew->pNext = pS->pTop;
    pS->pTop = pNew;
    return;
}
//≈–∂œ’ª «∑ÒŒ™ø’
int empty(PSTACK pS)
{
    if (pS->pTop == pS->pBottom)
    {
        return true;
    }
    else
        return false;
}

void deltop(PSTACK pS) {
    pS->pTop = pS->pTop->pNext;
    return;
}

int main(void)
{
    STACK S;
    PSTACK ps=&S;
    init(&S);
    char val;
    char str[100];
    scanf("%s", &str);
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']') {
            val = ps->pTop->data;
            
            if (str[i] == '(' || str[i] == '[')push(&S, str[i]);
            else if (val=='(' && str[i]==')'||val=='['&&str[i]==']')deltop(&S);
            else push(&S, str[i]);
        }
    }
    
    if (empty(&S))
    {
        printf("∆•≈‰≥…π¶\n");
    }
    else
    {
        printf("∆•≈‰ ß∞‹\n");
    }
    
    return 0;
}
