#include "../../includes/minishell.h"

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

int open_file(t_red *redirect,int *std[2], t_herdoc *herdoc, t_env *env)
{
    int status;
    status = 0;
    char *file_name1 , *file_name;

    file_name1 = ft_strdup(redirect->file);
    file_name = whithout_quotes(file_name1);
    if (HERDOC==redirect->type)
    {
        if (*std[0] != -1 && last_herdoc(redirect))
            close(*std[0]);
        if (last_herdoc(redirect))
        {
            *std[0] = herdoc->herdoc_pipe;
            if(!herdoc->to_exp)
                *std[0] = herdoc_newfd( herdoc->herdoc_pipe, env);
        }
    }
    else
    {
        // printf(">%s<file name len :%ld\n",file_name,ft_strlen(redirect->file));
        if (ft_strlen(file_name) == 0)
            panic("minishell: no such file or directory!\n");
        //her to expand name of file 
        if (*std[1] != -1 && (77 == redirect->mode || 7== redirect->mode))
            close(*std[1]);
        if (*std[0] != -1 && 4 == redirect->mode)
            close(*std[0]);
        if (77 == redirect->mode){
            redirect->file = *expander(&(redirect->file), env,0, RED_EXPN);
            redirect->file = wild_expand_red(redirect->file);
            *std[1] = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
        }
        else if (7== redirect->mode){
            redirect->file = *expander(&(redirect->file), env,0 ,RED_EXPN);
            redirect->file = wild_expand_red(redirect->file );
            *std[1] = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        }
        else if (4== redirect->mode)
        {
            redirect->file = *expander(&(redirect->file), env, 0, RED_EXPN);
            redirect->file = wild_expand_red(redirect->file);
            *std[0] = open(redirect->file, O_RDONLY);
            if (*std[0] < 0)
            {
                dprintf(2,"minishell: %s:No such file or directory!\n", redirect->file);
                panic("");
            }
        }
        if (*std[1] < 0 && 4 != redirect->mode)
        {
            dprintf(2,"minishell: %s: Permission denied\n", redirect->file);
            free(redirect->file);
            panic("");
        }
    }
    free(file_name);
    return(status);
}

int     exec_red(t_red *redirect, int *std[2], t_herdoc *herdoc, t_env *env)
{
    int status;
    t_red *tmp;

    status = 0;
    tmp = redirect->next;
    while(redirect)
    {
        tmp = redirect->next;
        status = open_file(redirect, std, herdoc, env);
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

void append_slash(char **path_2d)
{
    int j = -1 ;
    char *tmp;

    while(path_2d[++j])
    {
        tmp = path_2d[j];
		path_2d[j] = ft_strjoin(tmp, "/");
        free(tmp);
        tmp = NULL;
    }
    return ;
}

char *cmd_abs_path(char *path,char *cmd)
{
    char **path_2d;
    char *tmp;
    char *cmd_abs_path;
    int i = -1;

    path_2d = ft_split(path, ':');
    cmd_abs_path = cmd;
    append_slash(path_2d);
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

int check_red(t_cmd_exec  *p , int ref)
{
    (void)ref;
    int status;
    int *std[2];

    status = 0;
    std[1] = &(p->fd_out);
    std[0] = &(p->fd_in);
    if (NULL != p->redirect)
        status = exec_red(p->redirect, std, p->herdoc ,*(p->myenv));
    if (p->fd_in != -1 || p->fd_out != -1)
    {
        if (p->fd_out != -1)
        {
            p->std_out = dup(1);
            dup2(*std[1], 1);
            close(*std[1]);
        }
        if(p->fd_in != -1)
        {
            p->std_in = dup(0);
            dup2(*std[0], 0);
            close(*std[0]);
        }
    }
    return (status);
}

int exec_new_cmd(t_cmd *cmd , int *last_status)
{
    t_cmd_exec  *p;
    int status;
    char *abs_path;
    char **cur_env;

    signal (SIGINT, NULL);
    p = (t_cmd_exec  *)cmd;
    p->argv = expander( p->argv, *(p->myenv), last_status, CMD_EXPN);
    p->argv = wild_expand(p->argv);
    status = check_red(p, NOT_SIMPLE);
    if( !(p->argv) || !(*(p->argv)) )
        exit(0);
    if(is_builtin(cmd, &status,last_status, NOT_SIMPLE))
        exit(status);
    else
    {
        cur_env = lstoarry(*(p->myenv));
        if(check_is_abs(p->argv[0]) == 0)
            abs_path = p->argv[0];
        else{
            abs_path = getEnvValue(*(p->myenv), "PATH");
            if(!abs_path)
                error_exec_new(p->argv[0], -1);
            abs_path = cmd_abs_path(abs_path, p->argv[0]);
            if(!abs_path )
                error_exec_new(p->argv[0], 127);
        }
        if(dstr_len(p->argv))
            if (-1 == execve(abs_path, p->argv, cur_env))
                error_exec_new(p->argv[0], 127);
    }
    free_mynigga(p->argv);
    free(abs_path);
    exit(0);
    return (status);  
}

int exec_sub_sh(t_cmd * cmd , int *last_status)
{
    t_sub_sh * p;
    int pid;
    int *std[2];
    int sub_status;

    p = (t_sub_sh  *)cmd;
    pid = fork();
    if (pid == 0)
    {
        std[0] = &(p->fd_in);
        std[1] = &(p->fd_out);
        if (p->redirect){
        
            exec_red(p->redirect, std,p->herdoc,*(p->myenv));
        }
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
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &sub_status, 0);
    *last_status = WEXITSTATUS(sub_status);
    return (*last_status);
}

int new_exec1(t_cmd *cmd, int ref, int *last_status)
{
    int status;
    int pid;
    t_cmd_exec  * p;

    status = 0;
    p = (t_cmd_exec  *)cmd;
    if (p)
    {   
        if (ref == PIPE)
            status = exec_new_cmd(cmd, last_status);
        else if(is_builtin(cmd, &status ,last_status, SINGLE))
            reset_fds(cmd);   
        else {
            pid = fork();
            if (pid == 0)
                exec_new_cmd(cmd, last_status);
            else
            {
                signal(SIGINT, do_nothing);
                waitpid(pid, &status, 0);
                if (WTERMSIG(status) == SIGINT)
                    status = 130;
                else
                    status = WEXITSTATUS(status);
            }
        }
    } 
    return status ;
}

int new_exec(t_cmd *cmd, int ref, int *last_status)
{
    int status;

    status = 0;
    if (NEW_CMD == cmd->type)
        status = new_exec1(cmd ,ref,last_status);
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
    return (status);
}
