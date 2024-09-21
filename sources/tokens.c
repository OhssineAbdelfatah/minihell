#include "../includes/minishell.h"


int red_or_pipe(char c)
{
    if(0 == c)
        return (-1);
    if (c == '|')
        return (PIPE);
    if (c == '>' || c == '<')
        return (RED);
    return(-2);
}

int count_tokens_new(char *s)
{
    int res;
    int i; 
    int ref; 

    if (NULL == s)
        return 0;
    res = 0;
    i = 0;
    ref = NOTHING;
    while (s[i])
    {
        i = skip_spaces(s, i);
        if (s[i] == '|')
        {
            if (ref == NOTHING || ref == PIPE || ref == RED)
                return (-1);
            ref = PIPE;
            res ++;
            i++;
        }
        if (RED == red_or_pipe(s[i]))
        {
            if (RED == ref)
                return (-2); 
            ref = RED;
            res++;
            while (s[i] && (RED == red_or_pipe(s[i])))
                i++;
        }
        i = skip_spaces(s, i);
        if (s[i] == '\'' || s[i] == '"')
        {
            ref = STRING;
            res++;
            while(s[i] && (s[i] == '\'' || s[i] == '"'))
            {
                i = get_next_quote(s, i) + 1;
                while (s[i] && is_white(s[i]) && (0 == is_special(s[i])) && s[i] != '\'' && s[i] != '"' )
                    i++;
    
            }
            // printf("res1:%d>i :%d\n", res, i);
        }
        i = skip_spaces(s,i);
        if (s[i] && is_white(s[i]) && (0 == is_special(s[i])) && s[i] != '\'' && s[i] != '"' )
        {
            if (ref == RED)
                ref = FILE_NAME;
            else 
                ref = EXEC;
            res ++;
            while (s[i] && is_white(s[i]) && (0 == is_special(s[i])) && s[i] != '\'' && s[i] != '"' )
            {
                
                i++;
                 if (s[i] == '\'' || s[i] == '"')
                {
                     while(s[i] && (s[i] == '\'' || s[i] == '"'))
                    {
                         i = get_next_quote(s, i) +1;
                    }
                }
            }
            // printf("res2:%d, %d\n", res, i);

        }
        if (0 == s[i] && RED == ref)
            return(-2);
        if (0 == s[i] && PIPE == ref)
            return(-1);
    }
    return (res);
}


int get_starto(char *s, int x)
{
    // int i;
    // int res;

    if (s[x] == 0)
        return (x);
    if(0 == is_white(s[x]))
        return(skip_spaces(s, x));
    if (0 == x )
            return x;
    return (x);
}

int get_endo(char *s, int x)
{
    if (s[x] == 0)
        return x;
    if (s[x] == '|')
        return (x+1);
    if(is_special(s[x]))
    {
        while(s[x] && is_special(s[x]))
            x++;
        return(x);
    }
    if (0 == is_special(s[x]) && is_white(s[x]))
    {
        if (s[x] == '\'' || s[x] == '"')
        {
            //  return(get_next_quote(s, x) + 1);
            while (0 == is_special(s[x]) && is_white(s[x]) && (s[x] == '\'' || s[x] == '"'))
                x = get_next_quote(s, x) + 1;
        }
           
        while(s[x] && (0 ==is_special(s[x])) && is_white(s[x]))
        {
            if (s[x] == '\'' || s[x] == '"')
            {
                while (s[x] && (s[x] == '\'' || s[x] == '"'))
                   x = get_next_quote(s, x) + 1;
            }
            else 
                x++;
        }
    }
    return(x);
}

char **fr9_trb7(char *s)
{
    t_tfar9 var;

    if (NULL == s)
        return NULL;
    var.reslen = count_tokens_new(s);
    // printf(">>reslen:%d\n", var.reslen);
    // exit(0);
    if (var.reslen < 0)
        panic("minishell :syntax error:\n");
    if (0 == var.reslen)
        return(NULL);
    var.res = (char **)malloc(sizeof(char *) *( var.reslen + 1));
    if (NULL == var.res)
        return(NULL);
    var.i = 0;
    var.end = 0;
    while (var.i < var.reslen)
    {
        var.start = get_starto(s, var.end);
        var.end = get_endo(s, var.start);
        var.res[var.i] = ft_substr(s, var.start, var.end - var.start);
        if (NULL == (var.res[var.i]))
            panic("malloc failed !\n");
        var.i ++;
    }
    var.res[var.i] = NULL;
    return (var.res);
}

// int main(int ac , char **av)
// {
//     if (ac != 2)
//         return(printf("nada\n"), 0);
//     printf("string :%s\n", av[1]);
//     int start , nbr_tok;
//     int end , i;
//     i = 0;
//     nbr_tok =  count_tokens_new(av[1]); 
//     printf("tokens nbr :%d\n",nbr_tok);
//     end = 0;
//     char **res = fr9_trb7(av[1]);
//     while (i < nbr_tok)
//     {
//         // printf("token[%d] : %s\n", i, res[i]);
//         // i++;
//         start =  get_starto(av[1], end);
//         end = get_endo(av[1], start);
//         printf("token[%d] :start %d, end %d\n",i,  start , end);
//         i++;
//     }
// }
