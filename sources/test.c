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
void handel_child(int signal)
{
    signals = 9982;
    printf("childe change it to:%d\n", signals);   
    exit(120);
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
    else if (pid > 0)  // Parent process
    {
        int status;
        signal(SIGINT, do_nothing2);
        waitpid(pid,&status, 0);
        signal(SIGINT, handle_it);
        // printf("%d\n", WTERMSIG(i));
         if (WTERMSIG(status) == SIGINT)
        {
            signals = 9898;
            // Child was interrupted by SIGINT, return to the prompt without printing anything further
            return;
        }
    }
}



// int main()
// {
//     char *str;

//     signal(SIGINT,handle_it);  // Parent process handles SIGINT

//     while (1)
//     {
//         signals = -1;
//         str = readline("shell> ");
//         if (ft_strcmp(str, "exit"))  // Exit the shell
//         {
//             free(str);
//             exit(0);
//         }
//         if (strcmp(str, "doc") == 0)  // Start HEREDOC
//         {
//             doc();  // Handle doc logic in a separate function
//         }
//         printf("sig:%d\n", signals);
//         if (signals == -1)
//             printf("your command is %s\n", str);
//         free(str);  // Free the memory for readline input
//     }
//     return 0;
// }
 

