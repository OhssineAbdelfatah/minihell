#include"../../includes/minishell.h"

bool is_builtin(t_cmd *cmd)
{
    struct new_cmd *p ;
    p = (struct new_cmd *)cmd;
    if (p->argv == NULL)
        return false;
    // char **bcmds = ft_split("cd pwd export unset env exit echo", ' ');
    char **bcmds = ft_split("cd pwd export unset env exit", ' ');
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
    struct new_cmd* p ;
    p = (struct new_cmd*)cmd;
    if(ft_strcmp(p->argv[0], "cd")){
        cd(cmd);
        puts("dkhel");

    }
    else if(ft_strcmp(p->argv[0], "pwd"))
        pwd(cmd);
    else if(ft_strcmp(p->argv[0], "env")){
        print_env(p->myenv);
    }
    else if(ft_strcmp(p->argv[0], "unset")){
        if(ft_strslen(p->argv) > 1)
            unset_env(&(p->myenv), p->argv);
    }
    else if(ft_strcmp(p->argv[0], "export"))
        export(&(p->myenv), p->argv);
    return 0;
}
