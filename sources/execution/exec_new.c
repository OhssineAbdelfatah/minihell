#include "../../includes/minishell.h"

// new_exec1

int exec_simple_cmd(t_cmd_exec* p)
{

    char **cur_env;
    char *abs_path;
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
    free(abs_path);
    return 0;
}

int exec_new_cmd(t_cmd *cmd , int *last_status)
{
    t_cmd_exec  *p;
    int status;
    int ref;

    ref = NOT_SIMPLE;
    signal (SIGINT, NULL);
    signal(SIGQUIT, NULL);
    p = (t_cmd_exec  *)cmd;
    p->argv = expander( p->argv, *(p->myenv), last_status, CMD_EXPN);
    p->argv = wild_expand(p->argv);
    status = check_red(p, &ref);
    if( !(p->argv) || !(*(p->argv)) )
        exit(0);
    if(is_builtin(cmd, &status,last_status, NOT_SIMPLE))
        exit(status);
    else
        exec_simple_cmd(p);
    free_mynigga(p->argv);
    exit(0);
    return (status);  
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
        else if(is_builtin(cmd, &status ,last_status, SIMPLE))
            reset_fds(cmd);   
        else {
            pid = fork();
            if (pid == 0)
                exec_new_cmd(cmd, last_status);
            else
            {
                signal(SIGQUIT, do_nothing);
                signal(SIGINT, do_nothing);
                waitpid(pid, &status, 0);
                if (WTERMSIG(status) == SIGINT)
                    status = 130;
                if (WTERMSIG(status) == SIGQUIT)
                    status = 131;
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
        status = exec_pipe(cmd, last_status);
    return (status);
}
