#include "../includes/minishell.h"

int get_next_quote(char *s,int i)
{
    if (s[i] == '"')
    {
        i++;
        while(s[i] && s[i] != '"')
            i++;
    }
    else
    {
        i++;
        while(s[i] && s[i] != '\'')
            i++;
    }
    return i;
}

int which_one(char *s)
{
    t_typenode i;
    if (!s)
        return -1;
    i = EXEC;
    if (ft_strlen(s) == 1 && s[0] == '|')
        return(PIPE);
    if (ft_strlen(s) == 1 && s[0] == 40)
        return(S_SUB);
    if (ft_strlen(s) == 1 && s[0] == 41)
        return(END_SUB);
    if (ft_strlen(s) == 2)
    {
        if (ft_strcmp(s, "<<"))
            return (HERDOC);
        if (ft_strcmp(s,">>"))
            return (RED);
        if (ft_strcmp(s, "&&"))
            return (AND);
        if (ft_strcmp(s, "||"))
            return (OR);
    }
    if (s[1] == '\0' && (s[0] == '>' || s[0] == '<'))
        return(RED);
    return(i);
}

int is_special(char s)
{
    int i;
    char *symbols = "|<>&()";

    i = 0;
    if(s)
    {
        while(symbols[i])
        {
            if(symbols[i] == s)
                return (i);
            i++;
        }
    }
    return(-1);
}


int next_nonspecial(char *s, int i)
{
    while(s[i] && 0 <= is_special(s[i]))
        i++;
    return (i);
}

int get_start(char *s, int i)
{
    if (s)
    {
        if (s[i] == 32 || (s[i] <= 13 && s[i] >= 9))
            return(skip_spaces(s, i));
        else 
            return (i);
    }
   return(i);
}


int get_end(char *s, int i)
{
    if (s[i] == '|')
        return i + 1;
    if (is_special(s[i]))
        return(next_nonspecial(s, i));
    else
    {
        while (s[i] && !is_special(s[i]))
        {
            if (s[i] == '\''|| s[i] == '"')
                i = get_next_quote(s, i);
            i++;
            if (is_special(s[i]) && (s[i - 1] == 32 || (s[i - 1] <= 13 && s[i - 1] >= 9)))
            {
                i--;
                while ( i > 0 && (s[i] == 32 || (s[i]<= 13 && s[i] >= 9)))
                    i--;
                i++;
                return(i);
            }
        }
    }
    return(i);
}

int check_dtr_for_and(char *s)
{
    int i;

    i = 0;
    if (s[i] == '&' && s[i + 1] != '&')
        return (1);
    while (s[i])
    {
        if (i > 0)
        {
            if (s[i] == '&' && s[i + 1] != '&' && s[i -1] != '&')
                return (1);
        }
        i++;
    }
    return 0;
}

int _check_str(char *s)
{
    int i = 0;
    if (!s)
        return (1);
    if (check_qoutes(s))
        return(error(s, 10), 1);
    if (is_full_white_str(s))
        return(1);
    if (check_dtr_for_and(s))
        return(error(s, AND), 1);
    while(s[i])
    {
        if (s[i] == '|' && s[i + 1] == '|' && s[i + 2] == '|')
            return(error(s, PIPE), 1);
        if (s[i] == '&' && s[i + 1] == '&' && s[i + 2] == '&')
            return(error(s, AND), 1);
        if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<')
            return(error(s, RED), 1);
        if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>')
            return(error(s, RED), 1);
        // if (s[i] == ')' && s[i + 1] == ')' )
        //     return(error(NULL, s[i]), 1);
        else
            i++;
    }
    return(0);
}
