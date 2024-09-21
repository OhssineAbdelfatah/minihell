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

char *getEnvValue(t_env *env, char *key)
{
    while(env != NULL)
    {
        if(ft_strcmp(env->key, key))
            return env->value;
        env = env->next;
    }
    return NULL;
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

int check_is_abs(char *cmd)
{
    int i = -1;
    int j = 0;

    while(cmd[++i])
    {
        if(cmd[i] == '\\')
            j++;
    }
    if(j > 0)
        if(access(cmd, X_OK) != 0)
            return 1;
    return 0;
}

char *cmd_abs_path(char *path,char *cmd)
{
    char **path_2d;
    char *cmd_abs_path;
    int i = -1;
    int j = -1 ;

    path_2d = ft_split(path, ':');
    cmd_abs_path = cmd;

	while(path_2d[++j])
		path_2d[j] = ft_strjoin(path_2d[j], "/");
    while(path_2d[++i])
    {
        if(access(ft_strjoin( path_2d[i], cmd_abs_path), X_OK) == 0)
        {
            cmd_abs_path = ft_strjoin( path_2d[i], cmd_abs_path);
            // free var(path2d)
            return cmd_abs_path;
        }
    }
    return NULL;
}

int exec_new_cmd(t_cmd *cmd)
{
    struct new_cmd *p;
    int status;
    char *abs_path1, *abs_path;
    char **cmd_args;
    char **cur_env;

    status = 0;
    p = (struct new_cmd *)cmd;
    // cmd_args = ft_split(p->argv , ' ');
    cmd_args = p->argv;
    if(!cmd_args || check_is_abs(cmd_args[0]))
        panic("no");
    if (NULL != p->redirect)
        status = exec_red(p->redirect, &(p->fd_in), &(p->fd_out), &(p->herdoc_pipe));
    if (p->fd_in != -1 || p->fd_out != -1)
    {
        if (p->fd_out != -1)
        {
            dup2(p->fd_out, 1);
            close(p->fd_out);
        }
        if(p->fd_in != -1)
        {
            dup2(p->fd_in, 0);

            close(p->fd_in);
        }
    }
    cur_env = lstoarry(p->myenv);
    abs_path = getEnvValue(p->myenv, "PATH");
    if(!abs_path)
        exit( -1);
    abs_path = cmd_abs_path(abs_path, cmd_args[0]);
    if(!abs_path)
    {
        printf("minishell: %s:command not found\n", cmd_args[0]);
        exit( -1);
    }
    if(dstr_len(cmd_args))
    {
        if (-1 == execve(abs_path, cmd_args, cur_env))
        {
            printf("minishell: %s:command fr not found\n", cmd_args[0]);
            panic("");
        }
    }
    free_mynigga(cmd_args);
    free(abs_path);
    exit(0);
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