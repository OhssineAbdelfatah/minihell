#include"../../includes/minishell.h"


int findAnyQt(char *str)
{
    int i = -1;
    while(str[++i]){
        if(str[i] == '\"' || str[i] == '\'')
            return i;
    }
    return -1;
}

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
// tokenize env vars
//  each $var should its place referenced with 

int noQt(char *str)
{
    int i = -1;

    while(str[++i])
    {
        if(str[i] == '\'' || str[i] == '\"')
            return 0;
    }
    return 1;
}

// int getVarName(char *arg){
//     return arg[0]; // to do
// }

// char *expand(char *arg)
// {   
//     // expand many vars or one 
//     char **tmp;
//     if( !ft_strchr(arg, '$') )
//         return arg;
//     tmp = ft_split(arg , '$');
//     ft_strndup(ft_strchr(arg,'$'), 0);
// }



// char *splitExpandQts(char *scmd){// to do
//     if(noQt(scmd))
//         return scmd;
//     while(scmd)

// }

// 


// clean up the arg
// replace old arg(non-expanded) with expanded one



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



int _countWordPerArg(char *arg)
{
    int i ;
    int count ;
    int ref;
    ref = 0;
    i= -1;
    count = 0;
    // if(arg[i] != '\'' &&  arg[i] != '\"')
    //     count++;
    // i = findAnyQt(arg);
    // if(i == -1)
    //     return count;
    // if(arg[i] == '\'')
    //     ref = 1;
    // else if(arg[i] == '\"')
    //     ref = 2;
    // i++;
    while(arg[++i])
    {
        // if(ref % 2 == 1 || (ref == 0 && arg[i] == '\'')){
        //     i += findSqt(arg + i);
        //        printf("at %d found %c \n", i,arg[i]);
        //         exit(0);
        //     if(ref == 1 ){
        //         ref = 0;
        //         i++;
        //         count++;
        //     }
        //     else if ( ref == 0 )
        //         ref = 1;
        // }
        // else if( ref % 2 == 0 || (ref == 0 && arg[i] == '\"')){
        //     i += findDqt(arg + i) ;
        //     if(ref == 2 )
        //     {
        //         i++;
        //         ref = 0;
        //         count++;
        //     }
        //     else if ( ref == 0 )
        //         ref = 2;
        // }else 
        if(arg[i] != '\'' && arg[i] != '\"' && ref == 0)
        {
            printf("bef%d ", count);
            count++;
            printf("after%d \n", count);
            while(arg[i] && arg[i] != '\'' && arg[i] != '\"')
                i++;
        }else if(arg[i] == '\''){
            i += findSqt(arg+i+1) + 1;
            if(ref == 0)
                ref = 1;
            else if( ref == 1)
            {
                count++;
                ref = 0;
            }
        }else if(arg[i] == '\"'){
            i += findDqt(arg+i+1) +1;
            if(ref == 0)
                ref = 2;
            else if( ref == 1)
            {
                count++;
                ref = 0;
            }
        }

    }
    return count;
}


int countWordPerArg(char *arg) 
{
    int count = 0;
    bool in_single_quotes = false;
    bool in_double_quotes = false;
    bool in_word = false;

    while (*arg) {
        if (*arg == '"') {
            if (!in_single_quotes) {
                in_double_quotes = !in_double_quotes;
                if (in_double_quotes) {
                    count++;
                }
            }
        } else if (*arg == '\'') {
            if (!in_double_quotes) {
                in_single_quotes = !in_single_quotes;
                if (in_single_quotes) {
                    count++;
                }
            }
        } else if (!in_single_quotes && !in_double_quotes) {
            if (!in_word) {
                in_word = true;
                count++;
            }
        }
        arg++;
    }

    return count;
}



// abde
// "ohss"
// '"03"'
// hoo