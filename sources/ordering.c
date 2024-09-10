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
        if (PIPE == j)
            break;
        if (ref == RED || ref == HERDOC )
           { ref = FILE_NAME;}
        else if (FILE_NAME == ref)
           { ref = EXEC;}
        if (j == RED || j == HERDOC)
          {  ref = j;}
        if (ref == EXEC)
        {
            // cmd = ft_strdup(tokens[i]);
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
// void get_content(t_red *red_lst)
// {
//     // while (red_lst)
//     // {
//     //     red_lst = red_lst->next;
//     // }
//     return;
// }


t_red *get_red(char **tokens, int i)
{
    t_red *red_lst;

    red_lst = NULL;
    while (tokens[i] && PIPE != which_one(tokens[i]))
    {
        if (which_one(tokens[i]) == RED || HERDOC == which_one(tokens[i]))
        {
            if (NULL == red_lst)
                red_lst = creat_red_lst(tokens, i);
            else
                add_to_lst(red_lst, tokens, i);
            if (!red_lst)
                return(NULL);
            // if (HERDOC == which_one(tokens[i]))
            //     get_content(red_lst);
            i++; 
        }
        i++;
    }
    return (red_lst);
}





// int main(int ac , char **av, char **env)
// {
//     struct new_cmd *cmd;
//     t_cmd *cmd1;
//     t_red *redirect;
//     char *cmd_lin_e;
//     int i = 0;
//     char **tok;
//     char *s ;

//     if (ac != 2)
//         return (printf("cmd pls\n"),1);
    
//     tok = fr9_trb7(av[1]);
//     redirect = get_red(tok, i);
//     cmd_lin_e = cmd_line(tok,&i);
//     cmd1 = init_new_cmd(cmd_lin_e, env,  redirect);
//     free_tree2(cmd1);
//     free_mynigga(tok);
// }