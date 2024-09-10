#include "../includes/minishell.h"

// int parse(char *str)
// {
//     int i = 0;
//     while (str[i])
//     {
//         i = skip_spaces(str, i);

//         i++;
//     }

// }



int check_qoutes(char *s)
{
    int i;
    enum ss j;

    i = 0;
    j = NONE;
    if (s)
    {
        while(s[i])
        {
            if(s[i] == '"'){

                if (j == SINGLE)
                    j = SINGLE;
                else if (j == DOUBLE)
                    j = NONE;
                else
                    j = DOUBLE;
            }
            if(s[i] == '\''){
                
                if (j == DOUBLE)
                    j = DOUBLE;
                else if (j == SINGLE)
                    j = NONE;
                else
                    j = SINGLE;
    
            }
            i++;
        }
    }
    return(j);
}

void panic(char *str)
{
    if (str)
        dprintf(2, "%s", str);
    exit(1);
}

void free_mynigga(char **str)
{
    int i = 0;
    // printf("i am abt to free\n");
    if (str)
    {
   
        while (str[i])
        {
            // printf("free%d\n",i);
            free(str[i]);
            str[i] = NULL;
            // ft_putnbr_fd(i,1);
            i++;
        }
    }
    free(str);
    str = NULL;
    // printf("done free\n");
}


int main( __unused int ac,__unused char **av, char **env)
{
    char *str;
    char **my_tokens;
    // struct exec_cmd *ex;
    t_cmd *res;
    int i = 0;

    res = NULL;
    while(1)
    {
        str = readline("depechez-vous!> ");
        // str = ft_strdup(str1);
        add_history(str);
        my_tokens = NULL;
        if (0 !=_check_str(str))
            panic("error from the main\n");
        else if (ft_strlen(str))
        {
            i = 0;
            my_tokens = fr9_trb7(str);
           
            if (ft_strcmp( my_tokens[0], "exit"))
                panic("BY!\n");
          
            i = 0;
            res = root(my_tokens,env);
            printf("res addr:%p\n", &(*res));

            print_tree(res);
            printf("\n");

            free_tree2(res);
            free_mynigga(my_tokens);
        }
        free(str);
    }
}
// GOAL EXEC THE REDIRECTION :