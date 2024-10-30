#include<stdio.h>
#include<string.h>

int main(){
    char s1[] = "   abohssineab   ";
    char s2[] = "ab";
    printf("result %s\n", strtrim(s1 , s2));
}