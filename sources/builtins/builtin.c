#include"../../includes/minishell.h"

bool is_builtin(t_cmd *cmd)
{
    struct exec_cmd *p = (struct exec_cmd *)cmd;
    char **bcmds = ft_split("cd pwd export unset env exit echo", ' ');
    char **cmd_arg = ft_split(p->argv, 32);
    int i = -1;
    while(++i < 7)
    {
        if(ft_strcmp(cmd_arg[0], bcmds[i]))
        {
            free_split(cmd_arg);
            free_split(bcmds);
            return true;
        }
    }
    free_split(bcmds);
    return false;
}

int exec_builtin(t_cmd *cmd)
{
    struct new_cmd* p ;
    p = (struct new_cmd*)cmd;
    char **cmd_arg;
    cmd_arg = ft_split(p->argv, 32);
    if(!cmd_arg || !(*cmd_arg))
        return -1;
    if(ft_strcmp(cmd_arg[0], "cd"))
        cd(cmd);
    else if(ft_strcmp(cmd_arg[0], "pwd"))
        pwd(cmd);
    else if(ft_strcmp(cmd_arg[0], "env")){
        print_env(p->myenv);
    }
    else if(ft_strcmp(cmd_arg[0], "unset")){
        if(cmd_arg[1] != NULL)
        unset_env(&(p->myenv), cmd_arg[1]);
    }
    else if(ft_strcmp(cmd_arg[0], "export"))
        export(&(p->myenv), p->argv);
    free_split(cmd_arg);
    return 0;
}