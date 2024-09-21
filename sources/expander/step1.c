#include<stdio.h>

// tokenize env vars
//  each $var should its place referenced with 
// clean up the arg
// replace old arg(non-expanded) with expanded one

int findDqt(char *str)
{
    int i = -1;
    while(str[++i]){
        if(str[i] == '\"' )
            return i;
    }
    return -1;
}

int findSqt(char *str)
{
    int i = -1;
    while(str[++i]){
        if(str[i] == '\'' )
            return i;
    }
    return -1;
}

int superCountWord(char *bigcmd)
{
    int i = -1;
    int indice ;
    int count = 0;
    while(bigcmd[++i] && bigcmd[i] == ' ')
        i++;
    while(bigcmd[i])
    {
        if(bigcmd[i] == '\''){
            if( (indice = findSqt(bigcmd+i+1)) != -1)
                i += indice+2;
        }
        else if(bigcmd[i] == '\"'){
            if( (indice = findDqt(bigcmd+i+1)) != -1)
                i += indice+2;
        }
        else if(bigcmd[i] == ' '){
            i++;
            count++;
            while(bigcmd[i] && bigcmd[i] == ' ')
                i++;
        }else if(bigcmd[i] != ' ' &&  bigcmd[i] != '\"' && bigcmd[i] != '\'' )
            i++;
    }
    return count;
}

int main(int ac , char **av)
{

    printf("%d \n",superCountWord(av[1]) );

}