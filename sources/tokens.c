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

int get_starto(char *s, int x)
{
    if (s[x] == 0)
        return (x);
    if(0 == is_white(s[x]))
        return(skip_spaces(s, x));
    if (0 == x )
            return x;
    return (x);
}



void error(char *s, int er_num)
{
    if (er_num == 40)
        ft_putstr_fd("minishell: syntax error near unexpected token '('\n", 2);
    else if (er_num == 41)
        ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
    else if (10 == er_num)
        ft_putstr_fd("Quotes !\n", 2);
    else if (er_num == OR)
        ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
    else if (er_num == AND)
        ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
    else if (-1 ==er_num || er_num == PIPE)
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
    else if (-2 ==er_num  || er_num == RED || er_num == HERDOC)
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
    else if (s)
        ft_putstr_fd(s, 2);
}


int count_tokens_pro(char *s)
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
        if (s[i])
        if (s[i] == '|')
        {
            if (s[i + 1] == '|')
                ref = AND;
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
                        i = get_next_quote(s, i) +1;
                }
            }
        }
        if (0 == s[i] && RED == ref)
            return(-2);
        if (0 == s[i] && PIPE == ref)
            return(-1);
    }
    return (res);
}


int counts_and_or(char *s)
{
    int res;
    int i ;
    
    res = 0;
    i= 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
            i = get_next_quote(s, i);
        if (s[i] == '|' && s[i + 1] == '|')
            res++;
        if (s[i] == '&' && s[i + 1] == '&')
            res++;
        i++;
    }
    return (res);
}

int count_pipe_red(char *s)
{
    int i;
    int res;
    int ref;

    i = 0;
    ref = NOTHING;
    (void)ref;
    res = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
            i = get_next_quote(s, i);
        if ( s[i + 1] != '|'&& s[i] == '|')
        {
            res++;
            if (i>0 && s[i - 1] == '|')
                res--;
        }
        if (s[i]== '>')
        {
            if (s[i+1] == '>')
                i++;
            res++;
        }
         if (s[i]== '<')
        {
            if (s[i+1] == '<')
                i++;
            res++;
        }
        i++;
    }
    return (res);
}

int count_words(char *s)
{
    int i;
    int res;
    int ref;

    i = 0;
    res = 0;
    if (!s)
        return (0);
    ref = NOTHING;
    while (s[i])
    {
        if(s[i] == '"' || s[i] == '\'')
        {
            
            i = get_next_quote(s,i);
            if (ref != STRING)
                res++;
            ref = STRING;
        }
        if (0 == is_white(s[i]))
            ref = SPACES;
        if (0 <= is_special(s[i]))
            ref = SPECIAL;
        if ((s[i] != '"' || s[i] != '\'') && (is_white(s[i]) && -1 == is_special(s[i])))
        {
            if (ref != STRING)
            {
                ref = STRING;
                res++;
            }
        }
        i++;
    }
    return (res);
}

int total_sub(char *s)
{
    int res;
    int i;

    res =  0;
    i = 0;
    if (!s)
        return 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
            i = get_next_quote(s, i);
        if (s[i] == 40 || s[i] == 41)
            res++;
        i++;
    }
    return res;
}

int get_next_parenties(char *s, int i)
{
    int ref;

    ref = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
            i = get_next_quote(s, i);
        if (s[i] == ')' && ref == 0)
            return i;
        else if (s[i] == ')' && ref != 0)
            ref --;
        // printf(">>>ref:%d,  s[i]:%d\n",ref, i );
        i++;
        if (s[i] == '(')
            ref++;
       
    }
    error(NULL, 40);
    return(-1);
}

int get_next_parenties_d(char **s, int i)
{
    int ref;

    ref = 0;
    while (s[i])
    {
        if (which_one(s[i]) == END_SUB && ref == 0)
            return i;
        else if (which_one(s[i]) == END_SUB && ref != 0)
            ref --;
        i++;
        if (which_one(s[i])  == S_SUB)
            ref++;
       
    }
    error(NULL, 40);
    return(-1);
}

int  count_sub_sh(char *s)
{
    int i;
    int res, next_par;

    res = 0;
    i = 0;
    next_par = 0;
    while(s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
            i = get_next_quote(s, i);
        if (s[i] == ')' && res == 0)
        {
            // printf("rturning from here 1!\n");
            return (error(NULL, 41), -1);
        }
        if (s[i] == '(')
        {
            next_par = get_next_parenties(s, i);
            // printf("res:%d, s[i]:%d,nxt_P:%d\n",res, i, next_par);
            if (next_par < 0)
                return (-1);
            else
                res += 2;
        }
        i++;
    }
    if (res != total_sub(s))

        return (error(NULL, 41),-1);
    return (res);
}

int get_tok_len(char *s)
{
    int pipe_red;
    int and_or;
    int words;
    int sub_sh;
    int res;

    if (!s)
        return (0);
    and_or = counts_and_or(s);
    // if (and_or < 0)
    //     return (AND_ER);
    pipe_red = count_pipe_red(s);
    // if (pipe_red < 0)
    //     return (PIPE_ER);
    words = count_words(s);
    // if (words < 0)
    //     return (SYNTAX);
    sub_sh = count_sub_sh(s);
    if (sub_sh < 0)
        return(-1);
    res =  words + and_or + pipe_red + sub_sh;
    return (res);
}



int get_endo(char *s, int x)
{
    int j;
    if (s[x] == 0)
        return x;
    if(0 <= is_special(s[x]))
    {
        if (s[x] == 40 || s[x] == 41)
            return (x+1);
        j = is_special(s[x]);
        while(s[x] && j == is_special(s[x]))
            x++;
        return(x);
    }
    if (-1 == is_special(s[x]) && is_white(s[x]))
    {
        if (s[x] == '\'' || s[x] == '"')
        {
            //  return(get_next_quote(s, x) + 1);
            while (-1 == is_special(s[x]) && is_white(s[x]) && (s[x] == '\'' || s[x] == '"'))
                x = get_next_quote(s, x) + 1;
        }
           
        while(s[x] && (-1 ==is_special(s[x])) && is_white(s[x]))
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
    var.reslen = get_tok_len(s);
    if (var.reslen <= 0)
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

int _check_tokens(char **tokens)
{
    int ref, next_ref;
    // int tmp_ref;
    int i;

    i = 0;
    ref = EXEC;
    if (!tokens)
        return (0);
    ref = which_one(tokens[i]); 
    if (ref == AND || ref == PIPE || ref == OR)
        return (ref);
    ref = check_tok_sub(tokens);
    if (ref != 0)
        return (ref);
    while (tokens[i])
    {
        ref = which_one(tokens[i]);
        i++;
        next_ref =  which_one(tokens[i]);
        if (ref != EXEC && ref == next_ref)
        {
            if (ref != S_SUB && ref != END_SUB)
                return (ref);
        }
        if (ref == RED || ref == HERDOC)
        {
            if (next_ref != EXEC)
                return (ref);
        }
        if (ref == PIPE || ref == AND || ref == OR)
        {
            if (next_ref != EXEC && next_ref != RED && next_ref != HERDOC)
            {
                if (next_ref != S_SUB && next_ref != END_SUB)
                    return (ref);
            }
        }
    }
    if (ref == END_SUB)
        ref = SUB_SH;
    return (ref);
}