#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    char *str="abcd";
    int m=strlen(str);
    printf("%d",m);
    str[0]='b';
    printf("%c",str[0]);
    int n=strlen(str);
    printf("%d",n);
    return;
}