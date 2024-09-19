#include "../includes/minishell.h"


// void _cd(char *s)
// {
//     char **res = ft_split(s, 32);
// }

void check_builtIn(char *s)
{
    if (ft_strcmp(s, "exit"))
        panic("exit\n");
    // else if (ft_strcmp(s, "cd"))
    //     _cd(s);
}

// void exec_cmd(char **tokens, char **env)
// {
//     int i;
//     i= 0;
//     if (!tokens)
//         return;
//     while (tokens[i])
//     {
//         if (ft_strcmp(tokens[i], "exit"))
//         {
//             printf("it is exit command!\n");
//             exit(1);
//         }
//         else
//         {
//             pid_t  pid = fork();
//             if (pid == -1)
//             {
//                 printf("\nCOULD not execute command \n");
//                 return; 
//             }
//             else if(pid == 0)
//             {
//                 if (-1 == execve(ft_strjoin("/usr/bin/", tokens[i]), NULL, env))
//                     panic("minishell : command not found\n");
//             }
//             else
//                 wait(NULL);
//         }
//         i++;
//     }
// }
