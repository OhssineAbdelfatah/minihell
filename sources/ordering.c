#include "../includes/minishell.h"

void ft_swap_str(char **s1,char **s2)
{
    char *tmp;

    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}


char *join_cmd(char *s1, char *s2)
{
    int i;
    int reslen;
    char *res;

    reslen = ft_strlen(s1) + ft_strlen(s2);
    if(NULL != s1)
        reslen += 1;
    res = (char *)malloc(reslen + 1);
    int l= ft_strlen(s1);
    i = 0;
    while(i < l)
    {
        res[i] = s1[i];
        i++;
    }
    if (l > 0)
        res[i] = 32;
    i++;
    l = 0;
    while ((size_t)l < ft_strlen(s2))
        res[i++] = s2[l++];
    res[i] = 0;
    free(s1);
    return (res);
    
}

char *cmd_line(char **tokens, int *x)
{
    int i, j;
    t_typenode ref;
    char *cmd;

    i = *x;
    ref = EXEC;
    cmd = NULL;
    while (tokens[i])
    {
        j = which_one(tokens[i]);
        if (PIPE == j || j == OR || j == AND || j == END_SUB || j == S_SUB)
        {
            // if (ref == END_SUB)
            //     i--;
            break;
        }
        if (ref == RED || ref == HERDOC )
           { ref = FILE_NAME;}
        else if (FILE_NAME == ref)
           { ref = EXEC;}
        if (j == RED || j == HERDOC)
          {  ref = j;}
        if (ref == EXEC)
        {
            if (NULL == cmd)
                cmd = ft_strdup(tokens[i]);
            else
                cmd = join_cmd(cmd , tokens[i]);
        }
        i++;
    }
    *x = i;
    return(cmd);
}

int get_mode(char **tokens, int i)
{
    if (ft_strcmp(tokens[i], "<"))
        return (4);
    if (ft_strcmp(tokens[i], ">>"))
        return(77);
    if (ft_strcmp(tokens[i], ">"))
        return(7);
    return (0);
}

int get_type(char **tokens, int i)
{
    if (ft_strcmp(tokens[i], "<<"))
        return (HERDOC);
    return (RED);
}

void assign_her_exp(t_del *lst, t_herdoc *herdoc)
{
    t_del *tmp;

    tmp = lst;
    if (!tmp)
        return ;
    while (tmp-> next)
    {
        tmp = tmp->next;
    }
    herdoc->to_exp = tmp->to_exp;
}

int herdoc_treat(t_del *lst, t_herdoc *herdoc)
{   
    int pid, status;
    int p[2];
    char *str;

    status = 0;
    if (NULL == lst)
        return 0;
    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        signal (SIGINT, NULL);
        while (lst != NULL)
        {
            while (1)
            {
                str = readline(">");
                if (!str)
                {
                    error("minishell: warning: here-document delimited by end-of-file\n", -9);
                    // sig = -99;
                    break;
                }
                if (ft_strcmp(str, lst->del))
                {
                    free(str);
                    break;
                }
                if (lst->next == NULL)
                {
                    ft_putstr_fd(str, p[1]);
                    ft_putstr_fd("\n", p[1]);
                }
                free(str);
            }
            lst =lst->next;
        }
        close(p[1]);
        close(p[0]);
        exit(0);
    }
    else if(pid > 0)
    {
        signal(SIGINT, do_nothing);
        waitpid(pid, &status,  0);
        signal(SIGINT, signal_handler);
        if (WTERMSIG(status)  == SIGINT)
        {
            sig = 130;
            status = 130;
        }
        else
            status = 0;
        if (sig == -1)
            herdoc->herdoc_pipe = p[0];
        else
            close (p[0]);
        close(p[1]);
    }
    return (status);
}

int get_herdoc(char **tokens,int i, t_herdoc *herdoc)
{
    t_del *str;
    int ref;
    char *delimiter;
    int status;
    
    status = 0;
    str = NULL;
    ref = which_one(tokens[i]);
    while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
    {
        if (ref == END_SUB || ref == S_SUB)
            break;
        ref = which_one(tokens[i]);
        if (ref == HERDOC)
        {
            i++;
            delimiter = ft_strdup(tokens[i]);
            if (NULL == str)
                str = first_del(str, delimiter);
            else
                str = add(str, delimiter);
        }
        i++;
    }
    assign_her_exp(str, herdoc);
    if (sig == -1)
        status = herdoc_treat(str, herdoc);
    free_delimiters(str);
    return status;
}

t_red *get_red(char **tokens, int i, t_herdoc *herdoc)
{
    t_red *red_lst;
    int ref;

    red_lst = NULL;
    ref = which_one(tokens[i]);
    (void)herdoc;
    while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
    {
        if (ref == END_SUB)
            break;
        ref = which_one(tokens[i]);
        if (ref == RED || HERDOC == ref)
        {
            if (NULL == red_lst)
                red_lst = creat_red_lst(tokens, i);
            else
                add_to_lst(red_lst, tokens, i);
            if (!red_lst)
                return(NULL);
            i++; 
        }
        i++;
    }
    return (red_lst);
}

t_red *get_red_for_sub(char **tokens, int i)
{
    t_red *red_lst;
    int ref;

    red_lst = NULL;
    ref =0;
    i = get_next_parenties_d(tokens, i) + 1;
    while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
    {
        ref = which_one(tokens[i]);
        if (ref == END_SUB)
            break;   
        if (ref == RED || HERDOC == ref)
        {
            if (NULL == red_lst)
                red_lst = creat_red_lst(tokens, i);
            else
                add_to_lst(red_lst, tokens, i);
            if (!red_lst)
                return(NULL);
            i++; 
        }
        i++; 
    }
    return (red_lst);
}

