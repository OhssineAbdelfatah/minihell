#include "../includes/minishell.h"

int last_herdoc(t_red *lst)
{
    t_red *tmp;
 
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

int open_file(t_red *redirect,int *in,int *out, t_herdoc *herdoc)
{
    int status;
    status = 0;

    if (HERDOC==redirect->type)
    {
        if (*in != -1 && last_herdoc(redirect))
            close(*in);
        if (last_herdoc(redirect))
        {
            // here is the magic of expand herdoc
            *in = herdoc->herdoc_pipe; // assign new pipe[0]
        }
    }
    else
    {
        //her to expand name of file 
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
            {
                dprintf(2,"minishell: %s:No such file or directory!\n", redirect->file);
                panic("");
            }
        }
        if (*out < 0 && 4 != redirect->mode)
            panic("minishell: Permission denied\n");
    }
    return(status);
}

int exec_red(t_red *redirect, int *in, int *out, t_herdoc *herdoc)
{
    int status;
    t_red *tmp;

    status = 0;
    tmp = redirect->next;
    while(redirect)
    {
        tmp = redirect->next;
        status = open_file(redirect, in, out, herdoc);
        redirect = tmp;
    }
    return(status);
}

int check_is_abs(char *cmd)
{
    if(access(cmd, X_OK) == 0)
    {
        printf("%s is executable\n",cmd);
        return 0;
    }
    return 1;
}

char *cmd_abs_path(char *path,char *cmd)
{
    char **path_2d;
    char *tmp;
    char *cmd_abs_path;
    int i = -1;
    int j = -1 ;

    path_2d = ft_split(path, ':');
    cmd_abs_path = cmd;

	while(path_2d[++j])
    {
        tmp = path_2d[j];
		path_2d[j] = ft_strjoin(tmp, "/");
        free(tmp);
        tmp = NULL;
    }
    while(path_2d[++i])
    {
        tmp = ft_strjoin(path_2d[i], cmd_abs_path);
        if(access(tmp, X_OK) == 0)
        {
            cmd_abs_path = tmp;
            free_mynigga(path_2d);
            return cmd_abs_path;
        }
        free(tmp);
        tmp = NULL;
    }
    free_mynigga(path_2d);
    return NULL;
}

void pexit(char *s)
{
    printf("debug %s\n",s);
    exit(0);
}

int check_red(struct new_cmd *p)
{
    int status;

    status = 0;
    if (NULL != p->redirect)
        status = exec_red(p->redirect, &(p->fd_in), &(p->fd_out), p->herdoc);
    if (p->fd_in != -1 || p->fd_out != -1)
    {
        if (p->fd_out != -1)
        {
            p->std_out = dup(1);
            dup2(p->fd_out, 1);
            close(p->fd_out);
        }
        if(p->fd_in != -1)
        {
            p->std_in = dup(0);
            dup2(p->fd_in, 0);
            close(p->fd_in);
        }
    }
    if (p->argv)
        p->argv = expander( p->argv, *(p->myenv));
    return (status);
}

int exec_new_cmd(t_cmd *cmd , int *last_status)
{
    // (void)last_status;
    struct new_cmd *p;
    int status;
    char *abs_path;
    char **cur_env;

    p = (struct new_cmd *)cmd;
    /********************************************** */
    // THIS ONE JUST TO KNOW IF THE STATUS IS WORKING PROPERLY
    /********************************************** */
    if ( p->argv && ft_strcmp("echo", p->argv[0]) &&  ft_strcmp("$?", p->argv[1]))
    {
        printf("STATUS : %d\n", *last_status);
        exit (0);
    }
    /********************************************************** */
    status = check_red(p);
    if(is_builtin(cmd))
    {
        status = exec_builtin(cmd);
        exit(status);
    }
    cur_env = lstoarry(*(p->myenv));
    if (p->argv == NULL)
        exit(status);
    if(check_is_abs(p->argv[0]) == 0)
        abs_path = p->argv[0];
    else
    {
        abs_path = getEnvValue(*(p->myenv), "PATH");
        if(!abs_path)
        {
            // dprintf(2,"minishell: %s:command not found\n", p->argv[0]);
            printf("bash: %s: No such file or directory\n",p->argv[0]);
            exit(-1);
        }
        abs_path = cmd_abs_path(abs_path, p->argv[0]);
        if(!abs_path)
        {
            dprintf(2,"minishell: %s:command not found\n", p->argv[0]);
            exit(127);
        }
        if(dstr_len(p->argv))
        {
            // dprintf(2,"executing..\n");
            if (-1 == execve(abs_path, p->argv, cur_env))
            {
                dprintf(2,"minishell: %s:command not found\n", p->argv[0]);
                exit(127);
                // panic("");
            }
        }
    }
    // free_mynigga(p->argv);
    p->argv = NULL;
    free(abs_path);
    abs_path = NULL;
    exit(0);
    return (status);  

}

int exec_sub_sh(t_cmd * cmd , int *last_status)
{
    struct sub_sh* p;
    int pid;
    int sub_status;

    p = (struct sub_sh *)cmd;
    pid = fork();
    if (pid == 0)
    {
        if (p->redirect)
            exec_red(p->redirect, &(p->fd_in), &(p->fd_out),p->herdoc);
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
        sub_status = new_exec(p->sub_root, 0, last_status);
        exit(sub_status);
    }
    waitpid(pid, &sub_status, 0);
    *last_status = WEXITSTATUS(sub_status);
    return (*last_status);
}

int new_exec(t_cmd *cmd, int ref, int *last_status)
{
    int status, pid;
    struct new_cmd * p;

    status = 0;
    if (NEW_CMD == cmd->type)
    {
        p = (struct new_cmd *)cmd;
        if (p)
        {   
            /********************************************** */
            // THIS ONE JUST TO KNOW IF THE STATUS IS WORKING PROPERLY
            /********************************************** */
            if ( p->argv && ft_strcmp("echo", p->argv[0]) &&  ft_strcmp("$?", p->argv[1]))
            {
                printf("STATUS : %d\n", *last_status);
                return 0;
            }
            /********************************************** */
            if (ref == PIPE)
                status = exec_new_cmd(cmd, last_status);
            else if(is_builtin(cmd)){
                status = exec_builtin(cmd);
                reset_fds(cmd);
            }   
            else {
                pid = fork();
                if (pid == 0)
                    exec_new_cmd(cmd, last_status);
                else
                    waitpid(pid, &status, 0);
                status = WEXITSTATUS(status);
            }
        }
      
    }
    else if (AND == cmd->type)
        status = exec_and(cmd, last_status);
    else if (OR == cmd->type)
        status = exec_or(cmd, last_status);
    else if (SUB_SH == cmd->type)
        status = exec_sub_sh(cmd , last_status);
    else if (PIPE == cmd->type)
    {
        status = exec_pipe(cmd, last_status);
        status = WEXITSTATUS(status);
    }
    // else if (PIPE == cmd->type)
    //     status = execute_pipe(cmd);
    // else if (PIPE == cmd->type)
    //     status = recursion_pipe(cmd, 0);
    return (status);
}