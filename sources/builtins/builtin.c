#include"../../includes/minishell.h"

bool is_builtin(t_cmd *cmd)
{
    struct exec_cmd *p = (struct exec_cmd *)cmd;
    char *bcmds[] = {"cd","pwd", "export","unset","env","exit","echo"};
    char **cmd_arg = ft_split(p->argv, 32);
    int i = -1;
    while(++i < 7)
    {
        if(ft_strcmp(cmd_arg[0], bcmds[i]) == 0 )
        {
            free_split(cmd_arg);
            return true;
        }
    }
    return false;
}

// int exec_builtin(t_cmd *cmd)
// {
//     struct exec_cmd* p ;
//     p = (struct exec_cmd*)cmd;
//     char **cmd_arg;
//     cmd_arg = ft_split(p->argv, 32);
//     if(!cmd_arg || !(*cmd_arg))
//         return -1;
//     if(ft_strcmp(cmd_arg[0], "cd"))
//         cd(cmd);
//     else if(ft_strcmp(cmd_arg[0], "pwd"))
//         pwd(cmd);
//     else if(ft_strcmp(cmd_arg[0], "env")){
//         print_env(ennv);
//     }
//     else if(ft_strcmp(cmd_arg[0], "unset")){
//         if(cmd_arg[1] != NULL)
//         unset_env(&ennv, cmd_arg[1]);
//     }
//     free_split(cmd_arg);
//     return 0;
// }