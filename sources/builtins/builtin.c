#include"../../includes/minishell.h"

int blt_echo(t_env *env, char **argv)
{
    // argv = expnader(argv, env);
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
    p->argv = expander( p->argv ,*(p->myenv));
    if(ft_strcmp(p->argv[0], "cd")) // add oldpwd and change pwd
        return cd(cmd);
    else if(ft_strcmp(p->argv[0], "pwd")) // 
        return pwd(cmd);
    else if(ft_strcmp(p->argv[0], "env"))
        return print_env(*(p->myenv));
    else if(ft_strcmp(p->argv[0], "unset")){
        if(ft_strslen(p->argv) > 1)
            return unset_env(p->myenv, p->argv);
        return 0;
    }
    else if(ft_strcmp(p->argv[0], "export"))
        return export(p->myenv, p->argv);
    else if(ft_strcmp(p->argv[0], "echo"))
        return blt_echo(*(p->myenv), p->argv);
    return 0;
}
