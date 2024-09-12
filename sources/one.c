#include "../includes/minishell.h"

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
    int i;
    
    i = 0;
    if (str)
    {
   
        while (str[i])
        {
            free(str[i]);
            str[i] = NULL;
            i++;
        }
    }
    free(str);
    str = NULL;
}


void parse_nd_exec(char **my_tokens,char **env)
{
    t_cmd *res;
    t_env *dup_env;

    res = NULL;
    dup_env = init_env(env);
    if (ft_strcmp( my_tokens[0], "exit"))
        panic("BY!\n");
    res = root(my_tokens,dup_env);
    if (!res)
        return;
    print_tree(res);
    printf("\n");
    if (res->type == NEW_CMD)
    {
        if (0 == fork())
            new_exec(res);
        wait(0);
    }
    else
        new_exec(res);
    free_tree2(res);
}



int main(  int ac, char **av, char **env)
{
    char *str;
    char **my_tokens;

    (void)av;
    (void)ac;
    while(1)
    {
        str = readline("depechez-vous!> ");
        // printf("is white :%d, strlen:%d\n",is_white_str(str) , ft_strlen(str));
        // if (0 == is_white_str(str))
        add_history(str);
        my_tokens = NULL;
        if (0 !=_check_str(str))
            panic("error from the main\n");
        else if (ft_strlen(str))
        {
            my_tokens = fr9_trb7(str);
            if (my_tokens)
                parse_nd_exec(my_tokens, env);
            free_mynigga(my_tokens);
        }
        free(str);
    }
}
// GOAL EXEC THE REDIRECTION :