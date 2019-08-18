#include "iostream"
#include "string.h"
#include "stdio.h"
int main()
{
    int i,j,k,l;
    j=0;
    char a[100],b[100];
    gets(a);
    k=strlen(a);
    for(i=k-1;i>=0;i--)
    {
        if(a[i]!=' ')
        {
            b[j] = a[i];
            j++;
        }
        else
        {
            for(l=j-1;l>=0;l--)
            {
                printf("%c",b[l]);
            }
            j=0;
            printf("%c",' ');
        }
    }
    for(l=j-1;l>=0;l--)
    {
        printf("%c",b[l]);
    }
    return 0;
}

