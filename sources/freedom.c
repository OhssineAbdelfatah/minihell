#include "../includes/minishell.h"

// void free_cmd(t_cmd *cmd)
// {
//     struct exec_cmd *p;

//     p = (struct exec_cmd *)cmd;
//     free(p->argv);
//     p->argv = NULL;
//     free(p);
//     p = NULL;
// }

// void free_pipe(t_cmd *cmd)
// {
//     struct pipe *p;

//     p = (struct pipe *)cmd;
//     free_tree(p->left);
//     free_tree(p->right);
//     free(p);
//     p = NULL;
// }

// void free_red(t_cmd *cmd)
// {
//     struct red *p;

//     p = (struct red *)cmd;
//     free(p->file);
//     p->file = NULL;
//     free_tree(p->cmd);
//     free(p);
//     p = NULL;
// }

void free_mynigga(char **str)
{
    int i;
    
    i = 0;
    if (str)
    {
        while (str[i])
        {
            free(str[i]);
            str[i] = NULL;
            i++;
        }
    }
    free(str);
    str = NULL;
}

void free_red_lst(t_red **lst)
{
    t_red *tmp;

    tmp = (*lst)->next;
    while (NULL != *lst)
    {
        tmp = (*lst)->next;
        free((*lst)->file);
        (*lst)->file = NULL;
        free(*lst);
         *lst = NULL;
        *lst = tmp;
    }
    *lst = NULL;
}

void free_env_lst(t_env **lst)
{
    t_env *tmp;

    tmp = (*lst)->next;
    while (NULL != *lst)
    {
        tmp = (*lst)->next;
        free((*lst)->value);
        free((*lst)->key);
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}

void free_new_cmd(t_cmd *cmd)
{
    struct new_cmd *p;

    p = (struct new_cmd *)cmd;
    free_mynigga(p->argv);
    if (NULL != p->redirect)
        free_red_lst(& (p->redirect));
    if (NULL != p->herdoc)
    {
        if (p->herdoc->herdoc_pipe != -1)
            close(p->herdoc->herdoc_pipe);
        p->herdoc->herdoc_pipe = -1;
        free(p->herdoc);
    }
    p->herdoc = NULL;
    free(p);
}

void free_sub(struct sub_sh *cmd)
{
    if (NULL != cmd->redirect)
        free_red_lst(&(cmd->redirect));
    if (NULL != cmd->herdoc)
    {
        if (cmd->herdoc->herdoc_pipe != -1)
            close(cmd->herdoc->herdoc_pipe);
        cmd->herdoc->herdoc_pipe = -1;
        free(cmd->herdoc);
    }
    cmd->herdoc = NULL;
    free(cmd);
}


void free_pipe2(t_cmd *cmd)
{
    struct pipe *p;

    p = (struct pipe *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}

void free_or(t_cmd *cmd)
{
    struct or *p;

    p = (struct or *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}
void free_and(t_cmd *cmd)
{
    struct and *p;

    p = (struct and *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}

void free_tree2(t_cmd *cmd)
{
    struct sub_sh *tmp;
    if (!cmd)
        return;
    if (cmd->type == NEW_CMD)
        free_new_cmd(cmd);
    else if (cmd->type == PIPE)
        free_pipe2(cmd);
    else if (cmd->type == AND)
        free_and(cmd);
    else if (cmd->type == OR)
        free_or(cmd);
    else if (cmd->type == SUB_SH)
    {
        tmp = (struct sub_sh *)cmd;
        free_tree2(tmp->sub_root);
        free_sub(tmp);
    }
}

