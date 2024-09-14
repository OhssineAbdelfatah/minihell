#include "../includes/minishell.h"

int is_pipe_next(char **tok, int i)
{
    while (tok[i])
    {
        if(ft_strcmp(tok[i], "|"))
            return (1);
        i++;
    }
    return (0);
}
void pipe_try(char **tok)
{
    int i;
    int p[2];

    pipe(p);


    return;
}

void execute(char *s)
{
    char *cmd;

    cmd = ft_strjoin("/usr/bin/",s);
    execve(cmd, NULL, NULL);
    exit(0);
}

// int main(int ac , char **av)
// {
//     int p[2];
//     int pid;
//     char *str;
//     char **tok;
//     char buff[5];


//     // pid = fork();
//     // close (2);
   
//     printf("fd[0]:%d, fd[1]:%d\n", p[0], p[1]);
//     while (1)
//     {
//         str = readline(">");
//         tok = ft_split(str, 32);
//         if (dstr_len(tok) > 1)
//             pipe_try(tok);
//         else
//         {
//             if (fork() == 0)
//                 execute(tok[0]);
//             wait(0);
//         }
//         free_mynigga(tok);
//         free(str);
//     }
// }









// int main (int ac , char **av, char **env)
// {
//     int p[2];
//     int p1[2];
//     char buff[100];
//     int pid1, pid2;
//     char **arg;
    
//     (void)ac;
//     arg[0] = ft_strdup("-l");
//     arg[1] = NULL;
//     pipe(p);
//     // pipe(p1);
//     // if (0 == fork())
//     // {
//     //     close(1);
//     //     exit(0);
//     // }
//     pid1 = fork();
//     if (0 ==pid1)
//     {
//         close(1);
//         dup(p[1]);
//         // dup2(1,p[1]);
//         close(p[0]);
//         close(p[1]);

    
//         // printf("p[0]:%d , p[1] = %d\n", p[0], p[1]);
//         // write(p[1], "second child", 14);
//         execve("/usr/bin/ls", NULL, env);
//         exit(0);
//     }
//     // wait(pid1);
//     pid2 == fork();
//     if (pid2 == 0)
//     {
//         close(0);
//         dup(p[0]);
//         // dup2(p[0], 0);
//         // read(p[0],buff, 14);
//         // buff[14] = 0;

//         execve("/usr/bin/cat", NULL, env);
//         // close(p[0]);
//         // close(p[1]);
//         // printf("%s\n", buff);
//         close(1);
//         dup(p1[1]);
//         // printf("%s", buff);
//         exit(0);
//     }
//     // wait(pid2);
//     printf("last child\n");

//     if (0 == fork())
//     {
//         close(0);
//         dup(p1[0]);
//         // dup2(p1[0], 0);
//         // read(p1[0],buff, 14);
//         // buff[14] = 0;
//         // printf("%s\n", buff);
//         // close(1);
//         // dup(p1[1]);
//         execve("/usr/bin/rev", arg, NULL);
//         printf("last child\n");
//         // printf("%s says last child\n", buff);
//         exit(0);
//     }
//     // wait(0);
// //     printf("p1[0]:%d, p1[1]:%d\n", p1[0], p1[1]);
// }



// int main()
// {
//     int x = 77;
//     // close(0);
//     dup2(2,x);
//     printf("new:%d\n", x);
//     // if (0 == fork())
//     // {

//     // }
//     close(2);
//     close(1);
//     close(0);
//     dprintf(x, "alo\n");
// }