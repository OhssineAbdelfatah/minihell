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
            if(s[i] == '"')
                if (j == SINGLE)
                    j = SINGLE;
                else if (j == DOUBLE)
                    j = NONE;
                else
                    j = DOUBLE;
            if(s[i] == '\'')
                if (j == DOUBLE)
                    j = DOUBLE;
                else if (j == SINGLE)
                    j = NONE;
                else
                    j = SINGLE;
    
            i++;
        }
    }
    return(j);
}

void panic(char *str)
{
    if (str);
        dprintf(2, str);
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


int main(int ac, char **av, char **env)
{
    char *str, *str1;
    char **my_tokens;
    struct exec_cmd *ex;
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
           
            // my_tokens = split_shit(str);
            // printf("tokens nbr :%d\n", count_tokens_new(str));
            my_tokens = fr9_trb7(str);
           
            if (ft_strcmp( my_tokens[0], "exit"))
                panic("BY!\n");
            // my_tokens = tokens(str);
            // if (_check_tokens(my_tokens) == 0)
            //     panic("syntax Error\n");
          
          
            i = 0;
            // while(my_tokens[i])
            // {
            //     // printf("adres of tok:%p, what it point to:%p\n", &my_tokens[i], &(*my_tokens[i]));
            //     printf("that's your token:%s\n", my_tokens[i++]);
            // }
            
            // struct red * pop;
            // struct exec_cmd* cmd;
            // t_cmd *ssd;
            // if (res->type == RED)
            // {
            //     pop = (struct red *)res;
            //     ssd = pop->cmd;
            //     cmd = (struct exec_cmd*)ssd;
            //     printf("%s >> %s", cmd, pop->file);
            // }
            // write(1, "main IN\n", 9);
            res = root(my_tokens,env);
            // printf("res addr:%p\n", &(*res));

            print_tree(res);
            printf("\n");
            
            // if (0 == fork())
            //     exec(res);
            // wait(0);
            //
            // while(my_tokens[i])
            // {
            //     // printf("adres of tok:%p, what it point to:%p\n", &my_tokens[i], &(*my_tokens[i]));
            //     printf("that's your token after:%s\n", my_tokens[i++]);
            // }

           //TEST CMD
            // i = 0;
            // str1 = cmd_line(my_tokens, &i);
            // printf("cmd :%s\n", str1);
            // free(str1);

           
            // free_tree2(res);
            free_mynigga(my_tokens);
            // write(1, "main OUT\n", 10);
        }
        free(str);
    }
}
// GOAL EXEC THE REDIRECTION :