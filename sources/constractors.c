#include "../includes/minishell.h"

char **new_str(char **old_str)
{
    int i, old_len;
    char **res;

    i = 0;
    old_len = dstr_len(old_str);
    res = (char **)malloc(sizeof(char *) * (old_len + 2));
    if (NULL == res)
        return (NULL);
    if (old_str)
    {
        while (i < old_len)
        {
            res[i] = ft_strdup(old_str[i]);
            i++;
        }
    }
    res[i] = NULL;
    free_mynigga(old_str);
    return (res);
}

t_cmd *init_pipe(t_cmd *left, t_cmd *right)
{
    t_pipe  *res;

    res = malloc(sizeof(*res));
    if (!res)
        panic("init_pipe\n");
    res->type = PIPE;
    res->pipe_fd = -1;
    res->left = left;
    res->right = right;
    return ((t_cmd *)res);
}

t_cmd *init_and(t_cmd *left, t_cmd *right)
{
    t_and  *res;

    res = malloc(sizeof(*res));
    if (!res)
        panic("init_and\n");
    res->type = AND;
    res->status = 0;
    res->left = left;
    res->right = right;
    return ((t_cmd *)res);
}

t_cmd *init_or(t_cmd *left, t_cmd *right)
{
    t_or *res;

    res = malloc(sizeof(*res));
    if (!res)
        panic("init_or\n");
    res->type = OR;
    res->status = 0;
    res->left = left;
    res->right = right;
    return ((t_cmd *)res);
}

t_cmd *init_new_cmd(char **argv, t_env **myenv,t_red *redirect, t_herdoc *herdoc1)
{
    t_cmd_exec  *res;

    res = (t_cmd_exec  *)malloc(sizeof(*res));
    if (NULL == res)
        return (NULL);
    res->type = NEW_CMD;
    res->argv = argv;
    res->myenv = myenv;
    res->fd_in = -1;
    res->fd_out = -1;
    res->std_in = -1;
    res->std_out = -1;
    res->redirect = redirect;
    res->last_pipe_cmd = -1;
    res->herdoc = herdoc1;
    return ((t_cmd *)res);
}

t_cmd *init_sub(t_cmd *root_sub, t_env **myenv, t_red *redirect, t_herdoc * herdoc)
{
    t_sub_sh  *res;

    res = (t_sub_sh  *)malloc(sizeof(t_sub_sh ));
    if (!res)
        return (NULL);
    res->type = SUB_SH;
    res->fd_in = -1;
    res->fd_out = -1;
    res->redirect = redirect;
    res->myenv = myenv;
    res->last_pipe_cmd = -1;
    res->herdoc = herdoc;
    res->sub_root = root_sub;
    return ((t_cmd *)res);
} 

t_red *creat_red_lst(char **tokens, int i)
{
    t_red *res;

    res = (t_red *)malloc(sizeof (t_red ));
    if (!res)
        return (NULL);
    res->type = get_type(tokens, i);
    res->mode = get_mode(tokens, i);
    if (res->mode == 4 || res->type == HERDOC)
        res->fd = 0;
    else
        res->fd = 1;
    i++;
    res->file = ft_strdup(tokens[i]);
    res->next = NULL;
    return res;
}

void add_to_lst(t_red *red_lst, char **tokens, int i)
{
    t_red *new_red;
    t_red *tmp;


    new_red = NULL;
    tmp = red_lst;
    new_red = creat_red_lst(tokens, i);
    if (NULL == new_red)
        return;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_red;
}
