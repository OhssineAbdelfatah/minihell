#include "../includes/minishell.h"
#include <readline/readline.h>

int signals;

void handle_herdoc(int signal)
{
    exit(130);  // Exit with code 130 on SIGINT in the child
}

void doc()
{
    char *str;
    int pid;
    pid = fork(); 
    int is;
    if (pid == 0)  
    {
        signal(SIGINT, handle_herdoc);  
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
            free(str); 
        }
        exit(0);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0); 
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            printf("\nChild was interrupted by SIGINT\n");
        }
    }
}

void handle_it(int signal)
{
    // Handle SIGINT in the parent process
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
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
//         free(str);  // Free the memory for readline input
//     }
//     return 0;
// }
