#include"../../includes/minishell.h"

void reset_fds(t_cmd *p)
{
    t_new_cmd * cmd = (t_new_cmd *)p;
    if(cmd->std_in != -1){
        dup2(cmd->std_in, 0);
        close(cmd->fd_in);
    }
    if(cmd->fd_out != -1){
        dup2(cmd->std_out, 1);
        close(cmd->fd_out);
    }
    return ;
}

int blt_echo(t_env *env, char **argv)
{
    argv = expander(argv, env);
    argv++;
    while(*argv){
        printf("%s ",*argv);
        argv++;
    }
    printf("\n");
    return 0;
}


bool is_builtin(t_cmd *cmd)
{
    struct new_cmd *p ;
    p = (struct new_cmd *)cmd;
    if (p->argv == NULL)
        return false;
    // char **bcmds = ft_split("cd pwd export unset env exit echo", ' ');
    char **bcmds = ft_split("cd pwd export unset env exit echo", ' ');
    int i = -1;
    while(++i < 7)
    {
        if(ft_strcmp(p->argv[0], bcmds[i]))
        {
            free_split(bcmds);
            return true;
        }
    }
    free_mynigga(bcmds);
    return false;
}

int exec_builtin(t_cmd *cmd)
{
    int status ;
    struct new_cmd* p ;

    p = (struct new_cmd*)cmd;
    p->argv = expander(p->argv, *(p->myenv));
    status = check_red(p);

    if(ft_strcmp(p->argv[0], "cd")) // add oldpwd and change pwd
    {
        status = cd(cmd);
        free_mynigga(p->argv);
    }
    else if(ft_strcmp(p->argv[0], "pwd")) // 
    {
        status = pwd(cmd);
        free_mynigga(p->argv);
    }
    else if(ft_strcmp(p->argv[0], "env")){
        status = print_env(*(p->myenv));
        free_mynigga(p->argv);
    }
    else if(ft_strcmp(p->argv[0], "unset")){
        if(ft_strslen(p->argv) > 1)
            status = unset_env(p->myenv, p->argv);
        free_mynigga(p->argv);
    }
    else if(ft_strcmp(p->argv[0], "export")){
        status = export(p->myenv, p->argv);
        free_mynigga(p->argv);
    }
    else if(ft_strcmp(p->argv[0], "echo")){
        status = echo(p);
        free_mynigga(p->argv);
    }
    else if(ft_strcmp(p->argv[0], "exit"))
        status = exit_blt(p);
    return status;
}
