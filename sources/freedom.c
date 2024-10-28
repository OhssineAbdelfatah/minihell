#include "../includes/minishell.h"

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
    t_cmd_exec  *p;

    p = (t_cmd_exec  *)cmd;
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

void free_sub(t_sub_sh  *cmd)
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
    t_pipe  *p;

    p = (t_pipe  *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}

void free_or(t_cmd *cmd)
{
    t_or *p;

    p = (t_or *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}
void free_and(t_cmd *cmd)
{
    t_and  *p;

    p = (t_and  *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}

void free_tree2(t_cmd *cmd)
{
    t_sub_sh  *tmp;
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
        tmp = (t_sub_sh  *)cmd;
        free_tree2(tmp->sub_root);
        free_sub(tmp);
    }
}

