#include "../includes/minishell.h"

// int main(int ac, char **av , char **env)
// {
//     int fd, pid1, pid2;
//     int status;
//     (void)fd;
//     (void)ac;
//     // (void)av;
//     // fd = open("file.txt", O_RDWR);
//     // printf("fd : %d\n", fd);
//     // dup2(fd, 2);
//     pid1 = fork();
//     if (pid1 == 0)
//     {
//         pid2 = fork();
//         if (pid2 == 0)
//         {
//             if (-1 == execve("/bin/78", av, env))
//                 exit(127);
//             // ft_putstr_fd("7878\n", 2);
//             // exit (EXIT_FAILURE);
//         }
//         waitpid(pid2, &status, 0);
//         printf("Exit status : %d, %d\n", status, WEXITSTATUS(status));
//         exit (WEXITSTATUS(status));
//     }
//     waitpid(pid1, &status,0);
//     // close(fd);
//     printf("Exit status : %d\n", status);
// }