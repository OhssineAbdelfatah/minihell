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

// void execute(char *s)
// {
//     char *cmd;

//     cmd = ft_strjoin("/usr/bin/",s);
//     execve(cmd, NULL, NULL);
//     exit(0);
// }


// int main()
// {
//     // int x = 77;
//     char *str;
//     int p[2];
//     char readed[50];
//     // close(0);
//     if (0 == fork())
//    { 
//         pipe(p);
//         // dup2(p[1],1);
//         // dprintf(2,"p[0]:%d, p[1]:%d\n", p[0], p[1]);
//         // p[0] = 0;
//         // dup2(0,p[0]);
//         // str = readline(">");
//         while (1)
//         {
//             str = readline(">");
//             // printf("%s\n", str);
//             if (ft_strcmp("eof", str))
//                 break;
//             str = ft_strjoin(str, "\n");
//             ft_putstr_fd(str, p[1]);
//         }
//         read(p[0], readed, 10);
//         dprintf(2,"%s\n", readed);
//    }
//    wait(0);
//    printf("Parent process!\n"); 
//    // dprintf(2,"%s\n", readed)
// }


// int main()
// {
//     int p[2];
//     pipe (p);
//     dup2( 1,p[1]);
//     // close(p[1]);
//     // close(1);
//     write(p[1],"alo\n", 5);
//     write(1,"alo2\n", 6);
//     printf("p[1]:%d\n", p[1]);
// }


// int main()
// {
//     int p[2];
//     int x;
    
//     x = 0;
//     // pipe(p);
//     // printf("p[0]:%d, p[1] : %d\n", p[0], p[1]);
//     // close(p[0]);
//     // close(p[1]);
//     // pipe(p);
//     // printf("p[0]:%d, p[1] : %d\n", p[0], p[1]);
//     // close(p[0]);
//     // close(p[1]);
//     if (0 == fork())
//     {
//         x = 9;
//         exit(0);
//     }
//     wait(0);
//     printf("x after : %d\n", x);
// }