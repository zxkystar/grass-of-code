#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char *str="abcde";
    char *stt="cccc";
    stt[1]=str[1];
    printf("%c",stt[0]);
    return 1;
}