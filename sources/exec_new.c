#include "../includes/minishell.h"



void her_doc_bro(t_red *redirect,int *in,int *out)
{
    (void)redirect;
    (void)in;
    (void)out;
    return;
}
int open_file(t_red *redirect,int *in,int *out)
{
    int status;
    status = 0;

    if (HERDOC==redirect->type)
        her_doc_bro(redirect, in, out);
    else
    {
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
    }
    return(status);
}

int exec_red(t_red *redirect, int *in, int *out)
{
    int status;
    t_red *tmp;
    int fd;

    status = 0;
    tmp = redirect->next;
    while(redirect)
    {
        tmp = redirect->next;
        fd = open_file(redirect, in, out);
        redirect = tmp;
    }
    fd-=1;
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
        status = exec_red(p->redirect, &(p->fd_in), &(p->fd_out));
        if (p->fd_out != 1)
        {
            close(1);
            dup(p->fd_out);
        }
        if(p->fd_in != 0)
        {
            close(0);
            dup(p->fd_in);
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