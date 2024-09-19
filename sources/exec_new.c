#include "../includes/minishell.h"

int last_herdoc(t_red *lst)
{
    t_red *tmp;
    // t_red *tmp2;
    if (lst)
    {
        tmp = lst->next;
        while(tmp)
        {
            if (tmp->type == HERDOC)
                return(0);
            tmp = tmp->next;
        }
    }
    return(1);
}

void her_doc_bro(t_red *redirect,int *in,int *out)
{
    // (void)redirect;
    // (void)in;
    // (void)out;
    char *str;
    int p[2];


    // pipe(p);
    // if (0 == fork())
    // {
        // while(1)
        // {
        //     str = readline(">");
        //     if (ft_strcmp(str, redirect->file))
        //         break;
        //     ft_putstr_fd(str, p[1]);
        //     ft_putstr_fd("\n", p[1]);
        // }
        // close(p[1]);
        // close(p[0]);
    // }
    // wait(0);
    // close(p[1]);
    *in = p[0];
    return;
}

int open_file(t_red *redirect,int *in,int *out, int *herdoc_pipe)
{
    int status;
    status = 0;

    if (HERDOC==redirect->type)
    {
        if (*in != -1 && last_herdoc(redirect))
        {
            // dprintf(2,"<<about to close %d\n", *in);
            close(*in);
        }
        if (last_herdoc(redirect))
        {
            *in = *herdoc_pipe;
        }
        // her_doc_bro(redirect, in, out);
    }
    else
    {
        if (*out != -1 && (77 == redirect->mode || 7== redirect->mode))
        {
            // dprintf(2,">>>about to close %d\n", *out);
            close(*out);
        }
        if (*in != -1 && 4 == redirect->mode)
            close(*in);
        if (77 == redirect->mode)
            *out = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
        else if (7== redirect->mode)
            *out = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        else if (4== redirect->mode)
        {
            *in = open(redirect->file, O_RDONLY);
            if (*in < 0)
                panic("minishell: No such file or directory!\n");
        }
        if (*out < 0 && 4 != redirect->mode)
            panic("minishell: Permission denied\n");
    }
    return(status);
}

int exec_red(t_red *redirect, int *in, int *out, int *herdoc_pipe)
{
    int status;
    t_red *tmp;
    int fd;

    status = 0;
    tmp = redirect->next;
    while(redirect)
    {
        tmp = redirect->next;
        status = open_file(redirect, in, out, herdoc_pipe);
        redirect = tmp;
    }
    return(status);
}

int exec_new_cmd(t_cmd *cmd)
{
    struct new_cmd *p;
    int status;
    char **str;
    char **str1;
    char **cur_env;
    char *command;

    status = 0;
    p = (struct new_cmd *)cmd;

    if (NULL != p->redirect)
    {
        status = exec_red(p->redirect, &(p->fd_in), &(p->fd_out), &(p->herdoc_pipe));
    }
    if (p->fd_in != -1 || p->fd_out != -1)
    {
        // printf("fd_out :%d fd_in:%d\n", p->fd_out, p->fd_in);
        if (p->fd_out != -1)
        {
            dup2(p->fd_out, 1);
            close(p->fd_out);
        }
        if(p->fd_in != -1)
        {
            dup2(p->fd_in, 0);
            // dprintf(2,"closing this FD:%d\n", p->fd_in);

            close(p->fd_in);
        }
    }
    str = ft_split(p->argv, 32);
    str1 = str;
    cur_env = lstoarry(p->myenv);
    if(dstr_len(str))
    {
        command = ft_strjoin("/usr/bin/",str[0]);
        if (-1 == execve(command, str ++, cur_env))
        {
            printf("minishell: %s:command not found\n", str1[0]);
            panic("");
        }
    }
    exit(0);
    free_mynigga(str);
    free_mynigga(str1);
    free(command);
    return (status);  
}

int new_exec(t_cmd *cmd)
{
    int status;

    status = 0;
    if (NEW_CMD == cmd->type)
        status = exec_new_cmd(cmd);
    else if (PIPE == cmd->type)
        execute_pipe(cmd);
    return (status);
}