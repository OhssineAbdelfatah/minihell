#include "../includes/minishell.h"

int is_quoted(char *s)
{
    int i = 0;
    if (s)
    {
        while (s[i])
        {
            if (s[i] =='\'' || s[i] == '"' )
                return (1);
            i++;
        }
    }
    return(0); 
}

int get_reslen(char *s)
{
    int i, res, j;

    i = 0;
    res = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
        {
            j = i;
            i = get_next_quote(s,i);
            res = res + (i - (j +1));
        }
        else
            res ++;    
        i++;
    }
    return(res);
}

char *whithout_quotes(char *value)
{
    int res_len,i, j, end;
    char *res;

    i = 0;
    j = 0;
    end = -1;
    res_len = get_reslen(value);
    res = (char *)malloc(res_len + 1);
    if (!res)
        return(NULL);
    while (i < res_len)
    {
        if (end ==-1 && (value[j] == '\'' || value[j] == '"'))
        {
            end = get_next_quote(value, j);
            j++;
        }
        if(j != end)
        {
            res[i] = value[j];
            i++; 
            j++;
        }
        if (j == end)
        {
            end = -1;
            j++;
        } 
    }
    res[i] = 0;
    return(free(value),res);
}

t_del *first_del(t_del *node, char *value)
{
    t_del *res;

    res = NULL;
    
    if  (NULL==node)
    {  
        res = (t_del *)malloc(sizeof (t_del));
        if (!res)
            return (NULL);
        res->to_exp = 0;
        if (is_quoted(value))
        {
            res->to_exp = 1;
            res->del = whithout_quotes(value);
        }
        else
            res->del = value;
        res->next = NULL;
    }
    return (res);
}

t_del *add(t_del *node, char *value)
{
    t_del *res, *tmp;

    tmp = node;
    if (NULL == node)
        return(first_del(node, value));
    while (tmp->next)
        tmp = tmp->next;
    res = (t_del *)malloc(sizeof (t_del));
    if (is_quoted(value))
    {
        res->to_exp = 1;
        res->del = whithout_quotes(value);
    }
    else
        res->del = value;
    res->next = NULL;
    tmp->next = res;
    return (node);
}


void print_del(t_del *head)
{
    t_del * tmp;

    tmp = head;
    if (head == NULL)
    {
        printf("empty \n");
         return;
    }       
    while (tmp != NULL)
    {
        printf("del:%s\n", tmp->del);
        printf("to_exp:%d\n", tmp->to_exp);
        tmp = tmp->next;
    }
}

void free_delimiters(t_del *head)
{
    t_del* tmp;
    while (NULL != head)
    {
        tmp = head->next;
        free(head->del);
        head->del = NULL;
        free(head);
        head = NULL;
        head = tmp;
    }
}

int to_exp_doc(t_del *head)
{
    t_del *tmp;

    tmp = head;
    if (tmp == NULL)
        return 0;
    while(tmp->next)
    {
        tmp = tmp->next;
    }
    // if (tmp->del)
    return(0);
}


// int main()
// {
//     t_del *del;

//     del =NULL;
//     char *s = ft_strdup("eofdd");
//     del = first_del(del, s);
//     s = ft_strdup("eofdd2");
//     del = add(del, s);
//     s = ft_strdup("eofdd9");
//     del = add(del, s);
//     s = ft_strdup("eofdd4");
//     del = add(del, s);
//     print_del(del);
//     free_delimiters(del);
//     print_del(NULL);
//     // printf("%s\n", s);
//     // printf("%d\n", get_reslen(s));
//     //  printf("%s\n", whithout_quotes(s));

// }