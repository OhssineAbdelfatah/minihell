#include "../includes/minishell.h"

int signals;

void do_nothing2(int signal)
{
    return;
}

void handle_it(int signal)
{
    // Handle SIGINT in the parent process
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


void doc()
{
    char *str;
    int pid;
    pid = fork(); 
    int is;
    if (pid == 0)  // Child process (HEREDOC)
    {
        signal(SIGINT, NULL);  // Child handles SIGINT
        while (1)
        {
            str = readline("> ");
            is = strcmp(str, "doc2");
            if (is == 0)
            {
                printf("del:%s\n", str);
                free(str);
                break;
            }
            free(str);  // Free memory for each input
        }
        exit(0);
    }
//     else if (pid > 0)  // Parent process
//     {
//         waitpid(pid, NULL)
//     }
}



// int main()
// {
//     char *str;

//     signal(SIGINT, handle_it);  // Parent process handles SIGINT

//     while (1)
//     {
//         signals = -1;
//         str = readline("shell> ");
//         if (strcmp(str, "exit") == 0)  // Exit the shell
//         {
//             free(str);
//             exit(0);
//         }
//         if (strcmp(str, "doc") == 0)  // Start HEREDOC
//         {
//             doc();  // Handle doc logic in a separate function
//         }
//         printf("your command is %s\n", str);
//         free(str);  // Free the memory for readline input
//     }
//     return 0;
// }
 